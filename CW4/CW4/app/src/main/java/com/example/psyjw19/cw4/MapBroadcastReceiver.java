package com.example.psyjw19.cw4;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;

import java.util.ArrayList;

public class MapBroadcastReceiver extends BroadcastReceiver {
    private ArrayList<LatLng> points = new ArrayList<LatLng>();
    private GoogleMap myMap;
    Polyline line;
    private double totalDistance = 0;

    public MapBroadcastReceiver(GoogleMap googleMap) {
        myMap = googleMap;
   }

    @Override
    public void onReceive(Context context, Intent intent) {
        points = intent.getParcelableArrayListExtra("routePoint");
        totalDistance = totalDistance + intent.getFloatExtra("perDistance", 0);
        redrawLine();
    }

    public void redrawLine() {
        if (line != null) {
            myMap.clear();  //clears all Markers and Polylines
        }

        PolylineOptions options = new PolylineOptions().width(5).color(Color.BLUE).geodesic(true);
        for (int i = 0; i < points.size(); i++) {
            LatLng point = points.get(i);
            options.add(point);
        }

        line = myMap.addPolyline(options); //add Polyline
    }

    public double getDistance() {
        return totalDistance;
    }
}
