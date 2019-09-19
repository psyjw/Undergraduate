package com.example.psyjw19.cw2;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.ListView;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

import android.content.ServiceConnection;
import android.os.IBinder;
import android.content.ComponentName;
import android.widget.ProgressBar;

public class MainActivity extends AppCompatActivity {

    private MP3PlayerService.MyBinder mp3Service = null;
    private ProgressBar progressBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        progressBar = findViewById(R.id.progressBar);

        this.startService(new Intent(this, MP3PlayerService.class));
        this.bindService(new Intent(this, MP3PlayerService.class), serviceConnection, Context.BIND_AUTO_CREATE);

        final ListView lv = (ListView) findViewById(R.id.listView);
        File musicDir = new File(
                Environment.getExternalStorageDirectory().getPath()+ "/Music/");
        final File list[] = musicDir.listFiles();
        List<String> temp = new ArrayList<String>();

        int counter = 0;
        while (counter < list.length) {
            temp.add(list[counter].getName());
            counter += 1;
        }

        lv.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, temp));
        init();
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> myAdapter,
                                    View myView,
                                    int myItemInt,
                                    long mylng) {
                File selectedFromList =list[myItemInt];
                Log.d("CW2", selectedFromList.getAbsolutePath());
                // do something with selectedFromList...
                mp3Service.stop();
                mp3Service.load(selectedFromList.getAbsolutePath());
            }
        });
    }

    private ServiceConnection serviceConnection = new ServiceConnection()
    {
        @Override
        public void onServiceConnected(ComponentName name, IBinder
                service) {
            Log.d("CW2", "MainActivity onServiceConnected");
            mp3Service = (MP3PlayerService.MyBinder) service;
        }
        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.d("CW2", "MainActivity onServiceDisconnected");
            mp3Service = null;
        }
    };

    private Handler seekbarHandler = new Handler() {
        public void handleMessage(Message msg) {
                int currentPosition = mp3Service.getProgress();
                int totalTime = mp3Service.getDuration();
                int totalLength = progressBar.getMax();

                if (totalTime==0) {
                    progressBar.setProgress(0);
                }
                else {
                    progressBar.setProgress(currentPosition*totalLength/totalTime);
                }
        }
    };

    public void init() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while(true) {
                    try {
                        Thread.sleep(1000);
                    } catch (Exception e) {;}
                    seekbarHandler.sendEmptyMessage(0);
                    //Log.d("CW2","1");
                }
            }
        }).start();
    }

    public void onPlayClick(View v) {
        mp3Service.play();
    }

    public void onPauseClick(View v) {
        mp3Service.pause();
    }

    public void onStopClick(View v) {
        mp3Service.stop();
    }

    public void onQuitClick(View v) {
        mp3Service.quit();
        this.finish();
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d("CW2", "MainActivity onResume");
    }

    @Override
    protected void onStart() {

        super.onStart();
        Log.d("CW2", "MainActivity onStart");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d("CW2", "MainActivity onStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d("CW2","MainActivity onDestroy");
        if(serviceConnection!=null) {
            unbindService(serviceConnection);
            serviceConnection = null;
        }
    }


}
