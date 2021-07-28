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

    companion object{
        var progress = "10"
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.fragment_temp, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val tempbar = view.findViewById<CircularProgressBar>(R.id.temp_progressbar)
        val temp = view.findViewById<TextView>(R.id.temp)
        tempbar.setProgressWithAnimation(65f, 40)

        tempbar.progress = progress.toFloat()
        temp.text = progress


        }

}
