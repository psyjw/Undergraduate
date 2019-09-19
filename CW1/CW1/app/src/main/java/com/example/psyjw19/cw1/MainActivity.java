package com.example.psyjw19.cw1;

import android.content.Intent;
import android.content.UriMatcher;
import android.content.res.Configuration;
import android.graphics.Color;
import android.graphics.Paint;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    static final int ACTIVITY_CHANGE_COLOR=1;   //request code for ChangeColor Activity
    static final int ACTIVITY_CHANGE_BRUSH=2;   //request code for ChangeBrush Activity
    protected FingerPainterView myFingerPainterView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //instantiate FingerPainterView
        myFingerPainterView= findViewById(R.id.Canvas);

        //This intent is sent from the system to start MainActivity Activity
        Intent intent = getIntent();
        String action = intent.getAction();
        //confirm this intent is sent from the system
        if (intent.ACTION_VIEW.equals(action)){
            //uri stores the information of the image
            Uri uri = intent.getData();
            myFingerPainterView.load(uri);
        }
    }

    public void onColorButtonClick(View v) {
        Bundle bundle = new Bundle();
        bundle.putInt("originColor", myFingerPainterView.getColour());  //This bundle sends the current chosen color to ChangeColor Activity

        Intent intent = new Intent(MainActivity.this, ChangeColor.class);
        intent.putExtras(bundle);
        startActivityForResult(intent, ACTIVITY_CHANGE_COLOR);  //wait for ChangeColor Activity to send back the result (a new color value or nothing)
    }

    public void onBrushButtonClick(View v) {
        Bundle bundle = new Bundle();
        bundle.putString("originShape", String.valueOf(myFingerPainterView.getBrush()));
        bundle.putInt("originSize", myFingerPainterView.getBrushWidth());   //This bundle sends the current brush shape and size to ChangeBrush Activity

        Intent intent = new Intent(MainActivity.this, ChangeBrush.class);
        intent.putExtras(bundle);
        startActivityForResult(intent, ACTIVITY_CHANGE_BRUSH);  //wait for ChangeBrush Activity to send back the result (a new brush shape/size or nothing)
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        //if the result is sent from ChangeColor Activity
        if (requestCode == ACTIVITY_CHANGE_COLOR) {
            //if the user has clicked the confirm button
            if (resultCode == RESULT_OK) {
                Bundle bundle = data.getExtras();
                String color = bundle.getString("newColor");
                myFingerPainterView.setColour(Color.parseColor(color));
            }
        }
        //if the result is sent from ChangeBrush Activity
        else if (requestCode == ACTIVITY_CHANGE_BRUSH) {
            //if the user has clicked the confirm button
            if (resultCode == RESULT_OK) {
                Bundle bundle = data.getExtras();
                String shape = bundle.getString("newShape");
                if (shape.equals("round")) {
                    myFingerPainterView.setBrush(Paint.Cap.ROUND);
                }
                else if (shape.equals("square")) {
                    myFingerPainterView.setBrush(Paint.Cap.SQUARE);
                }
                String size = bundle.getString("newSize");
                myFingerPainterView.setBrushWidth(Integer.parseInt(size));
            }
        }
    }
}
