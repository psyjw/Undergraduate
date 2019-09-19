package com.example.psyjw19.cw4;

import android.content.ContentValues;
import android.content.Intent;
import android.database.ContentObserver;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.Spinner;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    private ListView lv;
    private Spinner spinner;
    SimpleCursorAdapter dataAdapter;
    Handler handler = new Handler();
    private String[] projection = new String[] {
            MapProviderContract._ID,
            MapProviderContract.DATE,
            MapProviderContract.START,
            MapProviderContract.FINISH,
            MapProviderContract.DISTANCE,
            MapProviderContract.VELOCITY
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        spinner = (Spinner) findViewById(R.id.spinner);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.spinner_array, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);

        queryAll();
        getContentResolver().
                registerContentObserver(
                        MapProviderContract.ALL_URI,
                        true,
                        new ChangeObserver(handler));
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

    public void onStartClick(View v) {

        String date = new SimpleDateFormat("yyyy-MM-dd").format(new Date());
        String startTime = new SimpleDateFormat("HH:mm:ss").format(new Date());

        ContentValues newValues = new ContentValues();
        newValues.put(MapProviderContract.DATE, date);
        newValues.put(MapProviderContract.START, startTime);
        Uri result = getContentResolver().insert(MapProviderContract.ALL_URI, newValues);
        int id = Integer.parseInt(result.getLastPathSegment());

        Bundle bundle = new Bundle();
        bundle.putInt("selectedID", id);
        bundle.putString("startTime", startTime);

        Intent intent = new Intent(MainActivity.this, MapActivity.class );
        intent.putExtras(bundle);
        startActivity(intent);
    }

    public void queryAll() {
        Cursor cursor;
        cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection, null, null, null);

        displayRecord(cursor);
    }

    public void displayRecord(Cursor c) {
        String colsToDisplay [] = new String[] {
                MapProviderContract.DATE,
                MapProviderContract.START,
                MapProviderContract.FINISH,
                MapProviderContract.DISTANCE,
                MapProviderContract.VELOCITY

        };

        int[] colResIds = new int[] {
                R.id.textView,
                R.id.textView2,
                R.id.textView4,
                R.id.textView6,
                R.id.textView8
        };

        dataAdapter = new SimpleCursorAdapter(
                this,
                R.layout.record_lv,
                c,
                colsToDisplay,
                colResIds,
                0);

        lv = (ListView) findViewById(R.id.Record);
        lv.setAdapter(dataAdapter);
    }

    public void onAscendClick(View v) {
        String selected = spinner.getSelectedItem().toString();
        Cursor cursor;

        switch (selected) {
            case "Duration":
                cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection, null, null, "DURATION ASC");
                break;
            case "Speed":
                cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection, null, null, "VELOCITY ASC");
                break;
            case "Distance":
                cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection, null, null, "DISTANCE ASC");
                break;
            default:
                return;
        }

        displayRecord(cursor);
    }

    public void onDescendClick(View v) {
        String selected = spinner.getSelectedItem().toString();
        Cursor cursor;

        switch (selected) {
            case "Duration":
                cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection, null, null, "DURATION DESC");
                break;
            case "Speed":
                cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection, null, null, "VELOCITY DESC");
                break;
            case "Distance":
                cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection, null, null, "DISTANCE DESC");
                break;
            default:
                return;
        }

        displayRecord(cursor);
    }

    public void onViewClick(View v) {
        Intent intent = new Intent(MainActivity.this, AnalysisActivity.class);
        startActivity(intent);
    }

}
