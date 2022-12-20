package com.michaellazebny.jyphoon.jc.handler

import android.util.Log
import com.juphoon.cloud.JCCallItem
import com.michaellazebny.jyphoon.jc.JCWrapper.JCCallUtils
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCEvent
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.JcReceiver
import org.greenrobot.eventbus.EventBus
import org.greenrobot.eventbus.Subscribe

class Handler(private val receiver: JcReceiver) {
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
        val activeCallItem = JCCallUtils.getActiveCall() ?: return
        when (event.eventType) {
            JCEvent.EventType.CAMERA_UPDATE, JCEvent.EventType.CALL_UPDATE -> {
                onVideoUpdate(activeCallItem)
            }
            else -> {}
        }
    }

    private fun onVideoUpdate(callItem: JCCallItem) {
        val selfVideo = callItem.uploadVideoStreamSelf
        val companionVideo = callItem.uploadVideoStreamOther

        receiver.onVideoChange(selfVideo, true) {}
        receiver.onVideoChange(companionVideo, false) {}
    }
}