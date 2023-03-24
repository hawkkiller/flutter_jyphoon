package com.michaellazebny.jyphoon.jc.handler

import android.util.Log
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCEvent
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.JyphoonReceiver
import org.greenrobot.eventbus.EventBus
import org.greenrobot.eventbus.Subscribe

class Handler(private val receiver: JyphoonReceiver) {
    val jcManager: JCManager = JCManager.getInstance()

    fun init() {
        EventBus.getDefault().register(this)
    }

    fun dispose() {
        EventBus.getDefault().unregister(this)
    }

    @Subscribe
    fun onEvent(event: JCEvent) {
        Log.d("JcPlugin::Handler", "onEvent: ${event.eventType}")
        receiver.onEvent(event.eventType.name, mapOf("one" to 1)) {}
    }
}