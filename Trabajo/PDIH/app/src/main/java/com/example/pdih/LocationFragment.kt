package com.example.pdih

import android.Manifest
import android.app.Service
import android.content.pm.PackageManager
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import android.location.LocationProvider
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import android.widget.Toast
import androidx.core.app.ActivityCompat
import androidx.fragment.app.Fragment

class LocationFragment: Fragment(), LocationListener {

    private lateinit var locationManager: LocationManager

    private lateinit var longitudeView: TextView
    private lateinit var latitudeView: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        locationManager = activity!!.getSystemService(Service.LOCATION_SERVICE) as LocationManager


    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.location_layout, container, false)
    }


    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        longitudeView = view.findViewById(R.id.longitude)
        latitudeView = view.findViewById(R.id.latitude)
    }

    override fun onLocationChanged(location: Location?) {

        Log.d("Location", location!!.altitude.toString())
        longitudeView.text = location?.longitude.toString()
        latitudeView.text = location?.latitude.toString()
    }

    override fun onStatusChanged(provider: String?, status: Int, extras: Bundle?) {
    }

    override fun onProviderEnabled(provider: String?) {
    }

    override fun onProviderDisabled(provider: String?) {
    }

    override fun onResume() {
        super.onResume()

        if (ActivityCompat.checkSelfPermission(
                context!!,
                Manifest.permission.ACCESS_FINE_LOCATION
            ) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(
                context!!,
                Manifest.permission.ACCESS_COARSE_LOCATION
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            requestPermissions(arrayOf(Manifest.permission.ACCESS_FINE_LOCATION), 99 )
        }


        locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 10, 0f, this)
    }

    override fun onPause() {
        super.onPause()

        locationManager.removeUpdates(this)
    }
}