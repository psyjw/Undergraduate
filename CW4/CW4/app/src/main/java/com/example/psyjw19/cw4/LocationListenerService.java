package com.example.psyjw19.cw4;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.location.LocationManager;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class LocationListenerService extends Service {
    private final IBinder binder = new MyBinder();
    private MyLocationListener locationListener;
    private LocationManager locationManager;

    @Override
    public void onCreate() {
        super.onCreate();

        locationListener = new MyLocationListener(this);
        locationManager =
                (LocationManager)getSystemService(Context.LOCATION_SERVICE);

        try {
            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER,
                    5, // minimum time interval between updates
                    5, // minimum distance between updates, in metres
                    locationListener);
        } catch(SecurityException e) {
            Log.d("g53mdp", e.toString());
        }
    }

    @Override
    public IBinder onBind(Intent arg0) {
        return new MyBinder();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d("CW4", "service onStartCommand");
        return Service.START_STICKY;
    }

    @Override
    public void onDestroy() {
        locationManager.removeUpdates(locationListener);
        super.onDestroy();
    }

    public class MyBinder extends Binder
    {

    }
}
