package com.michaellazebny.jyphoon.jc.handler

import com.michaellazebny.jyphoon.jc.JyphoonApi
import com.michaellazebny.jyphoon.jc.JyphoonReceiver
import com.michaellazebny.jyphoon.jc.jcWrapper.JCEvent.JCEvent
import org.greenrobot.eventbus.EventBus
import org.greenrobot.eventbus.Subscribe

class Handler(private val receiver: JyphoonReceiver, private val api: JyphoonApi) {
    fun init() {
        EventBus.getDefault().register(this)
    }

    fun dispose() {
        EventBus.getDefault().unregister(this)
    }

    @Subscribe
    fun onEvent(event: JCEvent) {
        // do not trigger updates on log events
        if (event.eventType == JCEvent.EventType.JCLOG) return;
        val map = mapOf<String?, Any>(
            "video" to api.video(),
            "audio" to api.audio(),
            "otherAudio" to api.otherAudio(),
            "otherVideo" to api.otherVideo(),
            "callStatus" to api.callStatus(),
            "clientState" to api.clientState(),
        )
        receiver.onEvent(event.eventType.name, map) {}
    }
}