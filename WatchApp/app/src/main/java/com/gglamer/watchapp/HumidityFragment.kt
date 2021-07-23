package com.gglamer.watchapp

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.TextureView
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import com.mikhaellopez.circularprogressbar.CircularProgressBar


class HumidityFragment : Fragment() {


    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val v = inflater.inflate(R.layout.fragment_humidity, container, false)

        val humibar = v.findViewById<CircularProgressBar>(R.id.humidity_progressbar)
        val humi = v.findViewById<TextView>(R.id.humidity)




        return v
    }

}