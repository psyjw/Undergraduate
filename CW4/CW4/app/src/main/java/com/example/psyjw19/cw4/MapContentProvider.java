package com.example.psyjw19.cw4;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.os.ParcelFileDescriptor;

import java.io.FileNotFoundException;

public class MapContentProvider extends ContentProvider {
    private DBHelper dbHelper = null;

    private static final UriMatcher uriMatcher;
    static {
        uriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
        uriMatcher.addURI(MapProviderContract.AUTHORITY, "runningRecord", 1);
        uriMatcher.addURI(MapProviderContract.AUTHORITY, "runningRecord/#", 2);
    }

    @Override
    public boolean onCreate() {
        this.dbHelper = new DBHelper(this.getContext(), "CW4db", null, 1);
        return true;
    }

    @Override
    public String getType(Uri uri) {

        String contentType;

        if (uri.getLastPathSegment()==null) {
            contentType = MapProviderContract.CONTENT_TYPE_MULTIPLE;
        } else {
            contentType = MapProviderContract.CONTENT_TYPE_SINGLE;
        }

        return contentType;
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {

        SQLiteDatabase db = dbHelper.getWritableDatabase();
        String tableName = "runningRecord";

        long id = db.insert(tableName, null, values);
        db.close();
        Uri nu = ContentUris.withAppendedId(uri, id);

        getContext().getContentResolver().notifyChange(nu, null);

        return nu;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();

        switch(uriMatcher.match(uri)) {
            case 2:
                selection = "_ID = " + uri.getLastPathSegment();
            case 1:
                Cursor temp = db.query("runningRecord", projection, selection, selectionArgs, null, null, sortOrder);
                return temp;
            default:
                return null;
        }
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();

        int updateID = db.update("runningRecord", values, selection, selectionArgs);
        db.close();
        Uri nu = ContentUris.withAppendedId(uri, updateID);
        getContext().getContentResolver().notifyChange(nu, null);
        return updateID;
    }

    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();

        int deleteID = db.delete("runningRecord", selection, selectionArgs);
        db.close();
        Uri nu = ContentUris.withAppendedId(uri, deleteID);
        getContext().getContentResolver().notifyChange(nu, null);
        return deleteID;
    }

    @Override
    public ParcelFileDescriptor openFile(Uri uri, String mode) throws FileNotFoundException {
        throw new UnsupportedOperationException("not implemented");
    }
}
