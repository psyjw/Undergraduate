package com.example.psyjw19.cw1;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class ChangeBrush extends AppCompatActivity {

    private RadioGroup radioGroup;
    private RadioButton round, square;
    private EditText size;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_brush);

        radioGroup = (RadioGroup) findViewById((R.id.ShapeGroup));
        round = (RadioButton)findViewById(R.id.RoundRadio);
        square = (RadioButton)findViewById(R.id.SquareRadio);
        //This editText only accepts 2-digit positive integer
        size = (EditText) findViewById((R.id.SizeText));

        //This bundle is sent from MainActivity, including the current brush shape and size
        //ChangeBrush Activity gets the current brush shape and sets the corresponding radio button checked
        Bundle bundle = getIntent().getExtras();
        String originShape = bundle.getString("originShape");
        switch (originShape) {
            case "ROUND":
                round.setChecked(true);
                break;
            case "SQUARE":
                square.setChecked(true);
                break;
        }
        //ChangeBrush Activity gets the current brush size and sets the editText
        int originSize = bundle.getInt("originSize");
        size.setText(String.valueOf(originSize));
    }

    public void onClick(View v) {
        int selected = radioGroup.getCheckedRadioButtonId();
        Bundle bundle = new Bundle();

        if (selected == round.getId()) {
            bundle.putString("newShape", "round");
        }
        else if (selected == square.getId()) {
            bundle.putString("newShape", "square");
        }

        if (Integer.parseInt(size.getText().toString()) == 0) {
            size.setText(String.valueOf(1));
        }
        bundle.putString("newSize", size.getText().toString());

        //send back the new brush and shape, set the result code to OK, close ChangeBrush Activity
        Intent result = new Intent();
        result.putExtras(bundle);
        setResult(Activity.RESULT_OK, result);
        finish();
    }
}
