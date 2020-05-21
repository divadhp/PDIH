package com.example.pdih

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.fragment.app.Fragment

class HomeFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.home_layout, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val accelerometerButton = view.findViewById<Button>(R.id.accelerometerButton)
        val linearAccelButton = view.findViewById<Button>(R.id.linearAccelButton)
        val location = view.findViewById<Button>(R.id.location)

        accelerometerButton.setOnClickListener {
            activity!!.supportFragmentManager.beginTransaction().replace(R.id.container, AccelerometerFragment()).addToBackStack(null).commit()
        }

        linearAccelButton.setOnClickListener {
            activity!!.supportFragmentManager.beginTransaction().replace(R.id.container, LinearAccelerationFragment()).addToBackStack(null).commit()

        }

        location.setOnClickListener {
            activity!!.supportFragmentManager.beginTransaction().replace(R.id.container, LocationFragment()).addToBackStack(null).commit()
        }
    }

}