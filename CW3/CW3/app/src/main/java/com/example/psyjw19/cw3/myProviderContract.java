package com.example.psyjw19.cw3;

import android.net.Uri;

public class myProviderContract {
    public static final String AUTHORITY = "com.example.psyjw19.cw3.myContentProvider";

    public static final Uri ALL_URI = Uri.parse("content://"+AUTHORITY+"/myRecipe");

    public static final String _ID = "_id";
    public static final String TITLE = "title";
    public static final String INSTRUCTION = "instruction";
    public static final String RATING = "rating";

    public static final String CONTENT_TYPE_SINGLE = "vnd.android.cursor.item/myContentProvider.data.text";
    public static final String CONTENT_TYPE_MULTIPLE = "vnd.android.cursor.dir/myContentProviderProvider.data.text";
}
