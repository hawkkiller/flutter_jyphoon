package com.michaellazebny.jyphoon.jc.methods

import com.juphoon.cloud.JCMediaChannel
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.tools.JCCallUtils

class MediaChannel {
    private val jcManager = JCManager.getInstance()

    fun join(channelId: String, password: String, video: Boolean): Boolean {
        // 生成 join 参数
        val joinParam = JCMediaChannel.JoinParam()
        joinParam.capacity = 2
        jcManager.mediaDevice.enableSpeaker(true)
        jcManager.mediaChannel.enableUploadAudioStream(true)
        jcManager.mediaChannel.enableUploadVideoStream(true)
        val res = jcManager.mediaChannel.join(channelId, joinParam)
        if (res && video) {
            setVideo(true)
        }
        return res
    }

    fun leave(): Boolean {
        return jcManager.mediaChannel.leave()
    }

    fun audio(): Boolean {
        val selfAudio = jcManager.mediaChannel.selfParticipant?.isAudio ?: false
        val audioStart = jcManager.mediaDevice.isAudioStart
        val uploadLocalAudio = jcManager.mediaChannel.uploadLocalAudio
        return selfAudio && audioStart && uploadLocalAudio
    }

    fun video(): Boolean {
        val selfVideo = jcManager.mediaChannel.selfParticipant?.isVideo ?: false
        val videoStart = jcManager.mediaDevice.isCameraOpen
        val uploadLocalVideo = jcManager.mediaChannel.uploadLocalVideo
        return selfVideo && videoStart && uploadLocalVideo
    }

    fun otherAudio(): Boolean {
        return JCCallUtils.otherParticipant?.isAudio ?: false
    }

    fun otherVideo(): Boolean {
        return JCCallUtils.otherParticipant?.isVideo ?: false
    }

    fun setAudio(audio: Boolean) {
        jcManager.mediaChannel.enableUploadAudioStream(audio)
        if (audio) {
            jcManager.mediaDevice.startAudio()
        } else {
            jcManager.mediaDevice.stopAudio()
        }
    }

    fun setVideo(video: Boolean) {
        jcManager.mediaChannel.enableUploadVideoStream(video)
        if (video) {
            jcManager.mediaDevice.startCamera()
        } else {
            jcManager.mediaDevice.stopCamera()
        }
    }

    fun setSpeaker(value: Boolean) {
        jcManager.mediaDevice.enableSpeaker(value)
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