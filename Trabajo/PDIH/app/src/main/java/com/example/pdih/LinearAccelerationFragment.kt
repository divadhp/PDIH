package com.example.pdih

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.TextureView
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import android.widget.Toast
import androidx.fragment.app.Fragment
import kotlin.math.pow
import kotlin.math.sqrt

class LinearAccelerationFragment : Fragment(), SensorEventListener {


    private val TAG = "LinearAcceleration"

    private lateinit var viewX: TextView
    private lateinit var viewY: TextView
    private lateinit var viewZ: TextView
    private lateinit var viewAcc: TextView
    private lateinit var sensorManager: SensorManager
    private lateinit var sensor: Sensor

    private var lastAccel: Double? = null


    private val THRESHOLD = 5.0

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        viewX = view.findViewById(R.id.viewX)
        viewY = view.findViewById(R.id.viewY)
        viewZ = view.findViewById(R.id.viewZ)
        viewAcc = view.findViewById(R.id.viewAcc)

        sensorManager = activity!!.getSystemService(Context.SENSOR_SERVICE) as SensorManager
        sensor = sensorManager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION)

    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.accelerometer_layout, container, false)
    }

    override fun onResume() {
        super.onResume()
        sensor.also {
            sensorManager.registerListener(this, it, SensorManager.SENSOR_DELAY_NORMAL)
        }
    }

    override fun onPause() {
        super.onPause()
        sensorManager.unregisterListener(this)
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
    }

    override fun onSensorChanged(event: SensorEvent?) {

        val x = event!!.values[0].toDouble()
        val y = event.values[1].toDouble()
        val z = event.values[2].toDouble()

        viewX.text = x.toString()
        viewY.text = y.toString()
        viewZ.text = z.toString()

        val acceleration = sqrt(x.pow(2) + y.pow(2) + z.pow(2))
        viewAcc.text = acceleration.toString()
        var delta: Double = 0.0
        lastAccel?.apply {
            delta = acceleration - lastAccel!!
        }

        lastAccel = acceleration

        if (acceleration > THRESHOLD) {
            Log.d(TAG, delta.toString())

            Toast.makeText(context, "Detectada caída", Toast.LENGTH_SHORT).show()
        }

    }


}