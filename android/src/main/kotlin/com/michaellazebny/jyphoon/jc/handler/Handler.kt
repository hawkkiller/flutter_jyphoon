package com.michaellazebny.jyphoon.jc.handler

import android.util.Log
import com.juphoon.cloud.JCCallItem
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCEvent
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.JcReceiver
import com.michaellazebny.jyphoon.jc.tools.JCCallUtils
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

        when (event.eventType) {
            JCEvent.EventType.CAMERA_UPDATE, JCEvent.EventType.CALL_UPDATE -> {
                val activeCallItem = JCCallUtils.activeCall ?: return
                onCallUpdate(activeCallItem)
            }
            JCEvent.EventType.CONFERENCE_PARTP_UPDATE, JCEvent.EventType.CONFERENCE_PROP_CHANGE, JCEvent.EventType.CONFERENCE_JOIN, JCEvent.EventType.CONFERENCE_LEAVE -> {
                onConfUpdate()
            }
            else -> {}
        }
    }

    private fun onCallUpdate(callItem: JCCallItem) {
        val selfVideo = callItem.uploadVideoStreamSelf
        val companionVideo = callItem.uploadVideoStreamOther

        receiver.onVideoChange(selfVideo, true) {}
        receiver.onVideoChange(companionVideo, false) {}
    }

    private fun onConfUpdate() {
        val otherParticipant = JCCallUtils.otherParticipant
        val selfParticipant = jcManager.mediaChannel.selfParticipant
        if (selfParticipant != null) {
            receiver.onVideoChange(selfParticipant.isVideo, true) {}
        }
        if (otherParticipant != null) {
            receiver.onVideoChange(otherParticipant.isVideo, false) {}
        }

    }
}