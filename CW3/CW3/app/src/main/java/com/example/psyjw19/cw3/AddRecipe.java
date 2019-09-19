package com.example.psyjw19.cw3;

import android.content.ContentValues;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class AddRecipe extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_recipe);
    }

    public void onConfirmClick(View v) {
        final EditText titleField = (EditText) findViewById(R.id.title);
        String title = titleField.getText().toString();

        final EditText instructionField = (EditText) findViewById(R.id.instruction);
        String instruction = instructionField.getText().toString();

        if (title.equals("") || instruction.equals("")) {
            Toast.makeText(AddRecipe.this, "Title and Instruction cannot be empty", Toast.LENGTH_SHORT).show();
            return;
        }

        ContentValues newValues = new ContentValues();
        newValues.put(myProviderContract.TITLE, title);
        newValues.put(myProviderContract.INSTRUCTION, instruction);
        newValues.put(myProviderContract.RATING, 0);

        getContentResolver().insert(myProviderContract.ALL_URI, newValues);

        finish();
    }
}
