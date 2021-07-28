package com.gglamer.watchapp

import ViewPagerAdapter

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.viewpager.widget.ViewPager
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.net.URL


class MainActivity : AppCompatActivity() {

    companion object{
        var ip = "192.168.31.160:5050"
        var state = 1
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val viewpager = findViewById<ViewPager>(R.id.viewpager)
        viewpager.adapter = ViewPagerAdapter(supportFragmentManager)


        fun getparam() {
            GlobalScope.launch {
                while (true) {
                    try {
                        val temperature = URL("http://${ip}/temperature").readText()
                        val humidity = URL("http://${ip}/humidity").readText()
                        //val pressure = URL("http://$ip/pressure").readText()


                        TempFragment.progress = temperature
                        HumidityFragment.progress = humidity

                    }catch (e: java.io.IOException){
                        getparam()
                        println(e)
                        println("catch")
                    }
                }
            }
        }
        getparam()


    }

}