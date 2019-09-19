package com.example.psyjw19.cw4;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.location.Location;
import android.location.LocationListener;
import android.os.Bundle;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;

import java.util.ArrayList;

public class MyLocationListener implements LocationListener {

    private GoogleMap myMap;
    private ArrayList<LatLng> points = new ArrayList<LatLng>(); //added
    Polyline line;
    private Context myContext;
    private float distance = 0;
    private double latitude;
    private double longitude;
    private Location previousLocation;

//    public MyLocationListener(GoogleMap googleMap) {
//        myMap = googleMap;
//    }


    public MyLocationListener(Context myContext) {
        this.myContext = myContext;
    }

    @Override
    public void onLocationChanged(Location location) {
        if (points.isEmpty() == false) {
            distance = location.distanceTo(previousLocation);
        }

        previousLocation = location;
        latitude = location.getLatitude();
        longitude = location.getLongitude();
        LatLng latLng = new LatLng(latitude, longitude);
        points.add(latLng);

        Bundle bundle = new Bundle();
        bundle.putParcelableArrayList("routePoint", points);
        bundle.putFloat("perDistance", distance);

        Intent intent = new Intent("Tracking");
        intent.putExtras(bundle);
        LocalBroadcastManager.getInstance(myContext).sendBroadcast(intent);

        Log.d("CW4", location.getLatitude() + " " + location.getLongitude());
    }
    @Override
    public void onStatusChanged(String provider, int status, Bundle extras) {
        // information about the signal, i.e. number of satellites
        Log.d("g53mdp", "onStatusChanged: " + provider + " " + status);
    }
    @Override
    public void onProviderEnabled(String provider) {
        // the user enabled (for example) the GPS
        Log.d("g53mdp", "onProviderEnabled: " + provider);
    }
    @Override
    public void onProviderDisabled(String provider) {
        // the user disabled (for example) the GPS
        Log.d("g53mdp", "onProviderDisabled: " + provider);
    }

}
