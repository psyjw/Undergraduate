package com.example.psyjw19.cw3;

import android.content.Intent;
import android.database.ContentObserver;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private Boolean sortByTitle = false;
    private Boolean sortByRating = false;
    private Boolean ascend = false;
    private Boolean descend = false;
    private ListView lv;
    private List<Integer> dbID = new ArrayList<Integer>();
    SimpleCursorAdapter dataAdapter;

    Handler h = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        queryAll();
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> myAdapter,
                                    View myView,
                                    int myItemInt,
                                    long mylng) {
                int idSelected = dbID.get(myItemInt);

                Bundle bundle = new Bundle();
                bundle.putInt("selectedID", idSelected);

                Intent intent = new Intent(MainActivity.this, ViewRecipe.class);
                intent.putExtras(bundle);
                startActivity(intent);
            }
        });

        getContentResolver().
                registerContentObserver(
                        myProviderContract.ALL_URI,
                        true,
                        new ChangeObserver(h));
    }

    class ChangeObserver extends ContentObserver {

        public ChangeObserver(Handler handler) {
            super(handler);
        }

        @Override
        public void onChange(boolean selfChange) {
            this.onChange(selfChange, null);
        }

        @Override
        public void onChange(boolean selfChange, Uri uri) {
            queryAll();
        }
    }

    public void queryAll() {
        String[] projection = new String[] {
                        myProviderContract._ID,
                        myProviderContract.TITLE,
                        myProviderContract.INSTRUCTION,
                        myProviderContract.RATING
        };

        String colsToDisplay [] = new String[] {
                myProviderContract.TITLE,
                myProviderContract.RATING
        };

        int[] colResIds = new int[] {
                android.R.id.text1,
                android.R.id.text2
        };

        Cursor cursor;
        if (sortByTitle == true) {
            if (descend == true ) {
                cursor = getContentResolver().query(myProviderContract.ALL_URI, projection, null, null, "TITLE DESC");
            }
            else {
                cursor = getContentResolver().query(myProviderContract.ALL_URI, projection, null, null, "TITLE ASC");
            }

        }
        else if (sortByRating == true) {
            if (descend == true ) {
                cursor = getContentResolver().query(myProviderContract.ALL_URI, projection, null, null, "RATING DESC");
            }
            else {
                cursor = getContentResolver().query(myProviderContract.ALL_URI, projection, null, null, "RATING ASC");
            }

        }
        else {
            cursor = getContentResolver().query(myProviderContract.ALL_URI, projection, null, null, null);
        }

        dataAdapter = new SimpleCursorAdapter(
                this,
                android.R.layout.simple_list_item_2,
                cursor,
                colsToDisplay,
                colResIds,
                0);

        updateIDList(cursor);

        lv = (ListView) findViewById(R.id.listView);
        lv.setAdapter(dataAdapter);
    }

    public void onAddClick (View v) {
        Intent intent = new Intent(MainActivity.this, AddRecipe.class);
        startActivity(intent);
    }

    public void onTitleSortClick (View v) {
        sortByRating = false;
        sortByTitle =true;
        if (ascend == false) {
            ascend = true;
            descend = false;
        }
        else {
            ascend = false;
            descend = true;
        }
        queryAll();
    }

    public void onRatingSortClick (View v) {
        sortByTitle = false;
        sortByRating =true;
        if (ascend == false) {
            ascend = true;
            descend = false;
        }
        else {
            ascend = false;
            descend = true;
        }
        queryAll();
    }

    public void updateIDList(Cursor c) {
        c.moveToFirst();
        dbID.clear();
        while (c.isAfterLast() == false) {
            dbID.add(c.getInt(c.getColumnIndex("_id")));
            c.moveToNext();
        }
    }

}
