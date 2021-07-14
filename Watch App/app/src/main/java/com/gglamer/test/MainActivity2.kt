package com.gglamer.test

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import java.net.URL

class MainActivity2 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main2)

        val on = findViewById<Button>(R.id.on_led)
        val off = findViewById<Button>(R.id.off_led)

        on.setOnClickListener {
            CoroutineScope(Dispatchers.IO).launch {
                URL("http://192.168.31.160:5050/on_led").readText()
            }
        }
        off.setOnClickListener {
            CoroutineScope(Dispatchers.IO).launch {
                URL("http://192.168.31.160:5050/off_led").readText()
            }
        }
    }
}