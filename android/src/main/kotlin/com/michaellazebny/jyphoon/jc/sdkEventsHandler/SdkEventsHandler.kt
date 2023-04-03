package com.michaellazebny.jyphoon.jc.sdkEventsHandler

import com.michaellazebny.jyphoon.jc.JyphoonCallApi
import com.michaellazebny.jyphoon.jc.JyphoonReceiver
import com.michaellazebny.jyphoon.jc.jcWrapper.JCEvent.JCEvent
import org.greenrobot.eventbus.EventBus
import org.greenrobot.eventbus.Subscribe

class SdkEventsHandler(private val receiver: JyphoonReceiver, private val callApi: JyphoonCallApi) {
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
            "video" to callApi.video(),
            "audio" to callApi.audio(),
            "otherAudio" to callApi.otherAudio(),
            "otherVideo" to callApi.otherVideo(),
            "callStatus" to callApi.callStatus(),
        )
        receiver.onEvent(event.eventType.name, map) {}
    }
}