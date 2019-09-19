package com.example.psyjw19.cw4;

import android.net.Uri;

public class MapProviderContract {
    public static final String AUTHORITY = "com.example.psyjw19.cw4.MapContentProvider";

    public static final Uri ALL_URI = Uri.parse("content://"+AUTHORITY+"/runningRecord");

    public static final String _ID = "_id";
    public static final String DATE = "date";
    public static final String START = "start";
    public static final String FINISH = "finish";
    public static final String DISTANCE = "distance";
    public static final String VELOCITY = "velocity";
    public static final String DURATION = "duration";

    public static final String CONTENT_TYPE_SINGLE = "vnd.android.cursor.item/MapContentProvider.data.text";
    public static final String CONTENT_TYPE_MULTIPLE = "vnd.android.cursor.dir/MapContentProviderProvider.data.text";
}
