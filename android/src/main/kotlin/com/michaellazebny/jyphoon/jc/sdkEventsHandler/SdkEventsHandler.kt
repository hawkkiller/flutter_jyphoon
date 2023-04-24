package com.michaellazebny.jyphoon.jc.sdkEventsHandler

import android.util.Log
import com.michaellazebny.jyphoon.jc.JyphoonApi
import com.michaellazebny.jyphoon.jc.JyphoonCallApi
import com.michaellazebny.jyphoon.jc.JyphoonInitializationApi
import com.michaellazebny.jyphoon.jc.JyphoonReceiver
import com.michaellazebny.jyphoon.jc.api.InitializationApi
import com.michaellazebny.jyphoon.jc.jcWrapper.JCEvent.JCEvent
import org.greenrobot.eventbus.EventBus
import org.greenrobot.eventbus.Subscribe

class SdkEventsHandler(
    private val receiver: JyphoonReceiver,
    private val api: JyphoonApi,
) {
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
            "clientState" to api.clientState()
        )
        Log.i("JC_EVENT", "${event.eventType.name} $map")
        receiver.onEvent(event.eventType.name, map) {}
    }
}