package com.gglamer.test

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import com.gglamer.test.databinding.ActivityMainBinding
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.net.URL

class MainActivity : Activity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val conn = findViewById(R.id.conn) as Button
        val temp = findViewById(R.id.temp) as TextView
        val humi = findViewById(R.id.humi) as TextView
        val press = findViewById(R.id.press) as TextView
        val but = findViewById(R.id.but) as Button



        fun getparam() {
            GlobalScope.launch {
                try {
                    while (true) {
                        val temperature = URL("http://192.168.31.160:5050/temperature").readText()
                        val humidity = URL("http://192.168.31.160:5050/humidity").readText()
                        val pressure = URL("http://192.168.31.160:5050/pressure").readText()
                        runOnUiThread(Runnable {
                            temp.setText("Temp: " + temperature)
                            humi.setText("Humidity: " + humidity)
                            press.setText("Pressure:" + pressure)
                        })
                    }
                }
                catch (e: java.io.IOException){
                    println(e)
                    getparam()
                }
            }
        }
        conn.setOnClickListener {
            getparam()
        }
        but.setOnClickListener {
            val intent = Intent(this,MainActivity2::class.java)
            startActivity(intent)
        }

    }
}