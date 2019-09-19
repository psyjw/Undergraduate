package com.example.psyjw19.cw1;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class ChangeColor extends AppCompatActivity {

    private RadioGroup radioGroup;
    private RadioButton black, red, yellow, blue, green;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_color);

        //a radio group guarantees only one choice can be made at the same time
        radioGroup = (RadioGroup) findViewById((R.id.ColorGroup));
        black = (RadioButton)findViewById(R.id.BlackRadio);
        red = (RadioButton)findViewById(R.id.RedRadio);
        yellow = (RadioButton)findViewById(R.id.YellowRadio);
        blue = (RadioButton)findViewById(R.id.BlueRadio);
        green = (RadioButton)findViewById(R.id.GreenRadio);

        //This bundle is sent from MainActivity, including the current chosen color
        //ChangeColor Activity gets the current chosen value and sets the corresponding radio button checked
        Bundle bundle = getIntent().getExtras();
        int originColor = bundle.getInt("originColor");
        switch (originColor){
            case -16777216:
                black.setChecked(true);
                break;
            case -65536:
                red.setChecked(true);
                break;
            case -256:
                yellow.setChecked(true);
                break;
            case -16776961:
                blue.setChecked(true);
                break;
            case -16711936:
                green.setChecked(true);
                break;
        }

    }

    public void onClick(View v) {
        int selected = radioGroup.getCheckedRadioButtonId();    //This is the id of the selected radio button in the radio group
        Bundle bundle = new Bundle();

        if (selected == black.getId()) {
            bundle.putString("newColor", "#FF000000");
        }
        else if (selected == red.getId()) {
            bundle.putString("newColor", "#FFFF0000");
        }
        else if (selected == yellow.getId()) {
            bundle.putString("newColor", "#FFFFFF00");
        }
        else if (selected == blue.getId()) {
            bundle.putString("newColor", "#FF0000FF");
        }
        else {
            bundle.putString("newColor", "#FF00FF00");
        }

        //send back the new chosen color, set the result code to OK, close ChangeColor Activity
        Intent result = new Intent();
        result.putExtras(bundle);
        setResult(Activity.RESULT_OK, result);
        finish();
    }
}
