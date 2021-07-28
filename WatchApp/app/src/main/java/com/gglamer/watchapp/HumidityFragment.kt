package com.gglamer.watchapp

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.TextureView
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import com.mikhaellopez.circularprogressbar.CircularProgressBar
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext


class HumidityFragment : Fragment() {
    companion object{
        var progress = "1"
    }



    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val v = inflater.inflate(R.layout.fragment_humidity, container, false)
        return v
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val humibar = view.findViewById<CircularProgressBar>(R.id.humidity_progressbar)
        val humi = view.findViewById<TextView>(R.id.humidity)

        CoroutineScope(Dispatchers.Main).launch(Dispatchers.IO) {
            while (true) {
                withContext(Dispatchers.Main) {
                    humibar.progress = progress.toFloat()
                    humi.text = "${progress}%"
                }

            }
        }


    }

}