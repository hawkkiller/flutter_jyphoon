package com.michaellazebny.jyphoon.jc.methods

import com.juphoon.cloud.JCMediaChannel
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.tools.JCCallUtils

class MediaChannel {
    private val jcManager = JCManager.getInstance()

    fun join(channelId: String, password: String): Boolean {
        // 生成 join 参数
        val joinParam = JCMediaChannel.JoinParam()
        joinParam.capacity = 2
        joinParam.smooth = true
        joinParam.password = password
        joinParam.maxResolution = 0
        joinParam.heartbeatTime = 20
        joinParam.heartbeatTimeout = 60
        joinParam.uriMode = false
        joinParam.framerate = 24
        joinParam.customVideoResolution = ""
        joinParam.videoRatio = 1.78f
        return jcManager.mediaChannel.join(channelId, joinParam)
    }

    fun leave(): Boolean {
        return jcManager.mediaChannel.leave()
    }

    fun audio(): Boolean {
        return jcManager.mediaChannel.selfParticipant?.isAudio ?: false
    }

    fun otherAudio(): Boolean {
        return JCCallUtils.otherParticipant?.isAudio ?: false
    }

    fun video(): Boolean {
        return jcManager.mediaChannel.selfParticipant?.isVideo ?: false
    }

    fun otherVideo(): Boolean {
        return JCCallUtils.otherParticipant?.isVideo ?: false
    }

    fun switchAudio() {
        // TODO: check if this really mutes audio
        val activeCall = JCCallUtils.activeCall
        if (activeCall != null) {
            jcManager.call.muteMicrophone(activeCall, !audio())
        }
    }

    fun switchVideo() {
        if (video()) {
            jcManager.mediaChannel.selfParticipant?.stopVideo()
        } else {
            jcManager.mediaChannel.selfParticipant?.startVideo(
                JCMediaDevice.RENDER_FULL_CONTENT,
                JCMediaChannel.PICTURESIZE_MIN
            )
        }
    }

    fun confStatus(): String {
        val participants = jcManager?.mediaChannel?.participants
        if (participants == null || participants.isEmpty()) {
            return "off"
        }
        if (participants.size == 1) {
            return "waiting"
        }
        return "on"
    }

    fun switchCamera() {
        jcManager.mediaDevice.switchCamera()
    }
}