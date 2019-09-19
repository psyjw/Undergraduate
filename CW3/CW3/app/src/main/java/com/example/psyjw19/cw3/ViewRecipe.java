package com.example.psyjw19.cw3;

import android.content.ContentValues;
import android.database.Cursor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class ViewRecipe extends AppCompatActivity {

    private int selectedID;
    private int newRate;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_recipe);

        Bundle bundle = getIntent().getExtras();
        selectedID = bundle.getInt("selectedID");

        querySingle();
    }

    public void querySingle() {
        String[] projection = new String[] {
                myProviderContract._ID,
                myProviderContract.TITLE,
                myProviderContract.INSTRUCTION,
                myProviderContract.RATING
        };

        Cursor cursor = getContentResolver().query(myProviderContract.ALL_URI, projection, myProviderContract._ID + "=" + selectedID , null, null);

        cursor.moveToFirst();
        String title = cursor.getString(cursor.getColumnIndex("title"));
        final TextView titleField = (TextView) findViewById(R.id.title);
        titleField.setText(title);

        String instruction = cursor.getString(cursor.getColumnIndex("instruction"));
        final TextView instructionField = (TextView) findViewById(R.id.instruction);
        instructionField.setText(instruction);
    }

    public void onRateClick(View v) {
        final EditText rateField = (EditText) findViewById(R.id.Rate);
        if (rateField.getText().toString().equals("")) {
            Toast.makeText(ViewRecipe.this, "Please enter a score between 1 and 5", Toast.LENGTH_SHORT).show();
            return;
        }
        newRate = Integer.parseInt(rateField.getText().toString());
        if (newRate > 5 || newRate < 0) {
            Toast.makeText(ViewRecipe.this, "Score should be between 1 and 5", Toast.LENGTH_SHORT).show();
            return;
        }
        updateSingle();
        finish();
    }

    public void onDeleteClick(View v) {
        deleteSingle();
        finish();
    }

    public void updateSingle() {
        ContentValues values = new ContentValues();
        values.put("rating", newRate);

        getContentResolver().update(myProviderContract.ALL_URI, values, myProviderContract._ID + "=" + selectedID,null);
    }

    public void deleteSingle() {
        getContentResolver().delete(myProviderContract.ALL_URI, myProviderContract._ID + "=" + selectedID, null);
    }
}
