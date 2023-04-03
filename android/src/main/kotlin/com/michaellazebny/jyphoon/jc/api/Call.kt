package com.michaellazebny.jyphoon.jc.api

import com.juphoon.cloud.JCCall
import com.juphoon.cloud.JCMediaChannel
import com.michaellazebny.jyphoon.jc.CallType
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager
import com.michaellazebny.jyphoon.jc.utils.JCCallUtils

class Call {
    private val jcManager = JCManager.getInstance()

    fun join(channelId: String, password: String, video: Boolean, type: CallType): Boolean {
        val res: Boolean
        val accountId = channelId.split("_").last()
        when (type) {
            CallType.ONETOONE -> {
                res = jcManager.call.call(
                    accountId,
                    video,
                    JCCall.CallParam(if (video) "video" else "audio", channelId),
                )
            }
            CallType.GROUP -> {
                val joinParam = JCMediaChannel.JoinParam()
                joinParam.capacity = 2
                joinParam.password = password
                jcManager.mediaDevice.enableSpeaker(true)
                jcManager.mediaChannel.enableUploadAudioStream(true)
                jcManager.mediaChannel.enableUploadVideoStream(true)
                res = jcManager.mediaChannel.join(channelId, joinParam)
            }
        }
        if (res && video) {
            setVideo(true)
        }
        return res
    }

    fun getCallType(): CallType? {
        return if (jcManager.call.callItems.isNotEmpty()) {
            CallType.ONETOONE
        } else if (jcManager.mediaChannel.selfParticipant != null) {
            CallType.GROUP
        } else {
            null
        }
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