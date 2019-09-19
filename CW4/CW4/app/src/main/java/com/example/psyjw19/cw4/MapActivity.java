package com.example.psyjw19.cw4;

import android.content.ContentValues;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.Manifest;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.location.LocationManager;
import android.os.IBinder;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.FragmentActivity;
import android.support.v4.content.ContextCompat;
import android.support.v4.content.LocalBroadcastManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import java.text.ParseException;
import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.TimeUnit;

public class MapActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap myMap;
    private LocationListenerService.MyBinder locationService;
    private int selectedID;
    private MapBroadcastReceiver receiver;
    private int totalDistance;
    private float velocity;
    private String startTime;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_map);

        Bundle bundle = getIntent().getExtras();
        selectedID = bundle.getInt("selectedID");
        startTime = bundle.getString("startTime");

        MapFragment mapFragment = (MapFragment) getFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);

    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        myMap = googleMap;

        receiver = new MapBroadcastReceiver(myMap);
        IntentFilter filter = new IntentFilter("Tracking");
        LocalBroadcastManager.getInstance(this).registerReceiver(receiver, filter);


        this.startService(new Intent(this, LocationListenerService.class));
        this.bindService(new Intent(this, LocationListenerService.class), serviceConnection, Context.BIND_AUTO_CREATE);


        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, 1);
        }
        myMap.setMyLocationEnabled(true);

    }

    private ServiceConnection serviceConnection = new ServiceConnection()
    {
        @Override
        public void onServiceConnected(ComponentName name, IBinder
                service) {
            Log.d("CW2", "MainActivity onServiceConnected");
            locationService = (LocationListenerService.MyBinder) service;
        }
        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.d("CW2", "MainActivity onServiceDisconnected");
            locationService = null;
        }
    };

    public void onStopClick(View v) {
        totalDistance = (int)receiver.getDistance();

        String finishTime = new SimpleDateFormat("HH:mm:ss").format(new Date());
        SimpleDateFormat outputFormat = new SimpleDateFormat("HH:mm:ss");
        Date startDate = null;
        Date endDate = null;
        try {
            startDate = outputFormat.parse(startTime);
            endDate = outputFormat.parse(finishTime);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        int diffInSec = (int)TimeUnit.MILLISECONDS.toSeconds(endDate.getTime() - startDate.getTime());

        velocity = Float.parseFloat(String.format("%.2f", (float)totalDistance/(float)diffInSec));

        ContentValues values = new ContentValues();
        values.put("finish", finishTime);
        values.put("distance", totalDistance);
        values.put("velocity", velocity);
        values.put("duration", diffInSec);
        getContentResolver().update(MapProviderContract.ALL_URI, values, MapProviderContract._ID + "=" + selectedID,null);

        this.stopService(new Intent(this, LocationListenerService.class));
        this.unbindService(serviceConnection);
        LocalBroadcastManager.getInstance(this).unregisterReceiver(receiver);
        finish();
    }

    @Override
    public void onBackPressed() {
        moveTaskToBack(true);
        //super.onBackPressed();
    }
}
