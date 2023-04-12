package com.michaellazebny.jyphoon.jc.utils

import com.juphoon.cloud.*
import com.michaellazebny.jyphoon.jc.CallType
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager

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
    fun getCallType(): CallType? {
        return if (JCManager.getInstance().call.callItems.isNotEmpty()) {
            CallType.ONETOONE
        } else if (JCManager.getInstance().mediaChannel.selfParticipant != null) {
            CallType.GROUP
        } else {
            null
        }
    }
}
