package com.gglame.vkd

import android.graphics.Color
import android.os.AsyncTask
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import com.google.android.material.textfield.TextInputEditText
import com.mikhaellopez.circularprogressbar.CircularProgressBar
import kotlinx.coroutines.*




import java.net.URL


class MainActivity : AppCompatActivity() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val but = findViewById(R.id.conn) as Button
        val temp = findViewById(R.id.temp) as TextView
        val press = findViewById(R.id.press) as TextView
        val humi = findViewById(R.id.humidity) as TextView
        val on_led = findViewById(R.id.on_led) as Button
        val off_led = findViewById(R.id.off_led) as Button
        val inf = findViewById(R.id.textView3) as TextView
        val getip = findViewById(R.id.get_ip) as TextInputEditText
        val tempro = findViewById(R.id.temp_progressbar) as CircularProgressBar
        val humipro = findViewById(R.id.humidity_progressbar) as CircularProgressBar


        fun getparam() {
            tempro.setProgressWithAnimation(65f, 40)
            humipro.setProgressWithAnimation(65f, 40)
            val ip = getip.text
            GlobalScope.launch {
                while (true) {
                    try {
                        val temperature = URL("http://" + ip + "/temperature").readText()
                        val humidity = URL("http://" + ip + "/humidity").readText()
                        val pressure = URL("http://" + ip + "/pressure").readText()
                        val tempt = temperature.toFloat()
                        val humit = humidity.toFloat()
                        runOnUiThread(Runnable {
                            temp.setText(temperature)
                            humi.setText(humidity)
                            press.setText("Pressure: $pressure")
                            tempro.progress = tempt
                            humipro.progress = humit
                        })
                    }catch (e: java.net.ConnectException){
                        println(e)
                        println("catch")
                    }
                }
            }
        }
        but.setOnClickListener {
            val ip = getip.text
            inf.setText("http://" + ip + "/temperature")
            getparam()
        }
        on_led.setOnClickListener {
            val ip = getip.text
            CoroutineScope(Dispatchers.IO).launch {
                try{
                    inf.setText(URL("http://" + ip + "/off_led").readText())
                } catch (e:java.net.ConnectException){
                    println(e)
                    println("catch")
                }
            }
        }
        off_led.setOnClickListener {
            val ip = getip.text
            CoroutineScope(Dispatchers.IO).launch {
                try{
                    inf.setText(URL("http://" + ip + "/on_led").readText())

                } catch (e:java.net.ConnectException){
                    println(e)
                    println("catch")
                }
            }
        }
    }
}


