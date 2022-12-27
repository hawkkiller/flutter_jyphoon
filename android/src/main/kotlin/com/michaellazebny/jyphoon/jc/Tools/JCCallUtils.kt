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
            JCCall.STATE_INIT -> "呼叫中"
            JCCall.STATE_PENDING -> "振铃中"
            JCCall.STATE_CONNECTING -> "连接中"
            JCCall.STATE_TALKING -> if (item.hold) {
                "挂起"
            } else if (item.held) {
                "被挂起"
            } else if (item.otherAudioInterrupt) {
                "对方声音中断"
            } else {
                val secondes = System.currentTimeMillis() / 1000 - item.talkingBeginTime
                String.format(Locale.getDefault(), "%02d:%02d", secondes / 60, secondes % 60)
            }
            JCCall.STATE_OK -> "通话结束"
            JCCall.STATE_CANCEL -> "通话结束"
            JCCall.STATE_CANCELED -> "挂断"
            JCCall.STATE_MISSED -> "未接"
            else -> "异常"
        }
    }

    fun genNetStatus(item: JCCallItem): String {
        return if (item.state != JCCall.STATE_TALKING) {
            ""
        } else when (item.audioNetReceiveStatus) {
            JCCall.NET_STATUS_DISCONNECTED -> "无网络"
            JCCall.NET_STATUS_VERY_BAD -> "很差"
            JCCall.NET_STATUS_BAD -> "差"
            JCCall.NET_STATUS_NORMAL -> "一般"
            JCCall.NET_STATUS_GOOD -> "好"
            JCCall.NET_STATUS_VERY_GOOD -> "非常好"
            else -> ""
        }
    }
}