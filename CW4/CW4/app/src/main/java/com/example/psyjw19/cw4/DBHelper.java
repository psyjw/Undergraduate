package com.example.psyjw19.cw4;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DBHelper extends SQLiteOpenHelper {
    public DBHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE runningRecord (" +
                "_id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                "date VARCHAR(128), " +
                "start VARCHAR(128), " +
                "finish VARCHAR(128), " +
                "distance INTEGER(8), " +
                "velocity FLOAT(8)," +
                "duration INTEGER(8)" +
                ");");

    }



    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion,
                          int newVersion) {

    }
}
