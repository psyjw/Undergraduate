package com.example.psyjw19.cw4;

import android.database.Cursor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.format.DateFormat;
import android.util.Log;
import android.widget.TextView;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class AnalysisActivity extends AppCompatActivity {

    private String[] projection = new String[] {
            MapProviderContract._ID,
            MapProviderContract.DATE,
            MapProviderContract.START,
            MapProviderContract.FINISH,
            MapProviderContract.DISTANCE,
            MapProviderContract.VELOCITY
    };
    private int monthlyRunTime = 0;
    private int monthlyDistance = 0;
    private int monthlyLongestDistance = 0;
    private float monthlySpeed = 0;
    private float monthlyBestSpeed = 0;
    private int dailyDistance = 0;
    private float dailyBestSpeed = 0;
    private TextView temp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_analysis);

        dailyAnalysis();
        monthlyAnalysis();
    }

    public void dailyAnalysis() {
        String date = new SimpleDateFormat("yyyy-MM-dd").format(new Date());
        Cursor cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection, MapProviderContract.DATE + "= '" + date +"'", null, null);

        cursor.moveToFirst();
        while (cursor.isAfterLast()==false) {
            dailyDistance = dailyDistance + cursor.getInt(cursor.getColumnIndex("distance"));
            if (cursor.getFloat(cursor.getColumnIndex("velocity")) > dailyBestSpeed) {
                dailyBestSpeed = cursor.getFloat(cursor.getColumnIndex("velocity"));
            }
            cursor.moveToNext();
        }

        temp = (TextView) findViewById(R.id.textView11);
        temp.setText(String.valueOf(dailyDistance));

        temp = (TextView) findViewById(R.id.textView13);
        temp.setText(String.valueOf(dailyBestSpeed));
    }

    public void monthlyAnalysis() {
        String date = new SimpleDateFormat("yyyy-MM").format(new Date());
        Log.d("cw4", MapProviderContract.DATE);
        Cursor cursor = getContentResolver().query(MapProviderContract.ALL_URI, projection,  MapProviderContract.DATE + " LIKE '" + date + "%'" , null, null);

        cursor.moveToFirst();
        while (cursor.isAfterLast()==false) {
            monthlyDistance = monthlyDistance + cursor.getInt(cursor.getColumnIndex("distance"));
            monthlySpeed = monthlySpeed + cursor.getFloat(cursor.getColumnIndex("velocity"));
            monthlyRunTime += 1;
            if (cursor.getFloat(cursor.getColumnIndex("distance")) > monthlyLongestDistance) {
                monthlyLongestDistance = cursor.getInt(cursor.getColumnIndex("distance"));
            }
            if (cursor.getFloat(cursor.getColumnIndex("velocity")) > monthlyBestSpeed) {
                monthlyBestSpeed = cursor.getFloat(cursor.getColumnIndex("velocity"));
            }
            cursor.moveToNext();
        }
        monthlySpeed = monthlySpeed/monthlyRunTime;

        temp = (TextView) findViewById(R.id.textView16);
        temp.setText(String.valueOf(monthlyRunTime));

        temp = (TextView) findViewById(R.id.textView18);
        temp.setText(String.valueOf(monthlyDistance));

        temp = (TextView) findViewById(R.id.textView20);
        temp.setText(String.valueOf(monthlyLongestDistance));

        temp = (TextView) findViewById(R.id.textView22);
        temp.setText(String.valueOf(monthlySpeed));

        temp = (TextView) findViewById(R.id.textView24);
        temp.setText(String.valueOf(monthlyBestSpeed));

    }
}
