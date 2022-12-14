package com.michaellazebny.jyphoon.jc.tools

import com.juphoon.cloud.*
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import java.util.*

object JCCallUtils {
    val activeCall: JCCallItem?
        get() {
            for (item in JCManager.getInstance().call.callItems) {
                if (item.active) {
                    return item
                }
            }
            return null
        }
    val otherParticipant: JCMediaChannelParticipant?
        get() {
            val jcManager = JCManager.getInstance()
            val selfParticipant = jcManager.mediaChannel?.selfParticipant
            var otherParticipant: JCMediaChannelParticipant? = null
            val participants = jcManager.mediaChannel.participants
            participants.forEach {
                if (it != selfParticipant) {
                    otherParticipant = it
                }
            }
            return otherParticipant
        }

    fun getSelfCanvas(item: JCCallItem): JCMediaDeviceVideoCanvas? {
        return if (item.uploadVideoStreamSelf) {
            item.startSelfVideo(JCMediaDevice.RENDER_FULL_CONTENT)
        } else {
            null
        }
    }

    fun getOtherCanvas(item: JCCallItem): JCMediaDeviceVideoCanvas? {
        return if (item.uploadVideoStreamOther) {
            item.startOtherVideo(JCMediaDevice.RENDER_FULL_CONTENT)
        } else {
            null
        }
    }

    val isIdle: Boolean
        get() = JCManager.getInstance().call.callItems.size == 0
    val needAnswerNotActiveCall: JCCallItem?
        get() {
            for (item in JCManager.getInstance().call.callItems) {
                if (!item.active && item.direction == JCCall.DIRECTION_IN && item.state == JCCall.STATE_PENDING) {
                    return item
                }
            }
            return null
        }
    val incomingCall: JCCallItem?
        get() {
            for (item in JCManager.getInstance().call.callItems) {
                if (item.direction == JCCall.DIRECTION_IN && item.state == JCCall.STATE_PENDING) {
                    return item
                }
            }
            return null
        }

    fun genCallInfo(item: JCCallItem?): String {
        return if (item == null) {
            ""
        } else when (item.state) {
            JCCall.STATE_INIT -> "?????????"
            JCCall.STATE_PENDING -> "?????????"
            JCCall.STATE_CONNECTING -> "?????????"
            JCCall.STATE_TALKING -> if (item.hold) {
                "??????"
            } else if (item.held) {
                "?????????"
            } else if (item.otherAudioInterrupt) {
                "??????????????????"
            } else {
                val secondes = System.currentTimeMillis() / 1000 - item.talkingBeginTime
                String.format(Locale.getDefault(), "%02d:%02d", secondes / 60, secondes % 60)
            }
            JCCall.STATE_OK -> "????????????"
            JCCall.STATE_CANCEL -> "????????????"
            JCCall.STATE_CANCELED -> "??????"
            JCCall.STATE_MISSED -> "??????"
            else -> "??????"
        }
    }

    fun genNetStatus(item: JCCallItem): String {
        return if (item.state != JCCall.STATE_TALKING) {
            ""
        } else when (item.audioNetReceiveStatus) {
            JCCall.NET_STATUS_DISCONNECTED -> "?????????"
            JCCall.NET_STATUS_VERY_BAD -> "??????"
            JCCall.NET_STATUS_BAD -> "???"
            JCCall.NET_STATUS_NORMAL -> "??????"
            JCCall.NET_STATUS_GOOD -> "???"
            JCCall.NET_STATUS_VERY_GOOD -> "?????????"
            else -> ""
        }
    }
}