package com.gglamer.watchapp

import ViewPagerAdapter

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.viewpager.widget.ViewPager


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val viewpager = findViewById<ViewPager>(R.id.viewpager)
        viewpager.adapter = ViewPagerAdapter(supportFragmentManager)

    }

}