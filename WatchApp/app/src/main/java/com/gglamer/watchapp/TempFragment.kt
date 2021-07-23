package com.gglamer.watchapp

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView

import com.mikhaellopez.circularprogressbar.CircularProgressBar

import kotlinx.coroutines.*
import java.net.URL


class TempFragment : Fragment() {

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.fragment_temp, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val tempbar = view.findViewById<CircularProgressBar>(R.id.temp_progressbar)
        val temp = view.findViewById<TextView>(R.id.temp)

        CoroutineScope(Dispatchers.IO).launch {
            while (true) {
                try {
                    val temperature = URL("http://192.168.31.40:5000/temperature/").readText()

                    val tempt = temperature.toFloat()
                    activity?.runOnUiThread(Runnable{
                        temp.setText(temperature)
                        tempbar.progress = tempt
                    })

                }catch (e: java.net.ConnectException){
                    println(e)
                    println("catch")
                }
            }
        }
    }

}