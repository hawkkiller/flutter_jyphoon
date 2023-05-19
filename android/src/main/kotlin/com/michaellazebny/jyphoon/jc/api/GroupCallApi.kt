package com.michaellazebny.jyphoon.jc.api

import com.juphoon.cloud.JCCall
import com.juphoon.cloud.JCMediaChannel
import com.michaellazebny.jyphoon.jc.CallType
import com.michaellazebny.jyphoon.jc.JyphoonCallApi
import com.michaellazebny.jyphoon.jc.jcWrapper.JCEvent.JCEvent
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager
import com.michaellazebny.jyphoon.jc.utils.JCCallUtils
import org.greenrobot.eventbus.EventBus

class GroupCallApi : JyphoonCallApi {
    /**
     * Starts the "call".
     * Returns true if the call was started successfully.
     *
     * [destination] - the identifier of the companion or the conference.
     *
     * [password] - the password for the conference.
     *
     * [video] - initiate call as videocall or audiocall.
     *
     * [type] - oneToOne or group.
     */
    override fun call(
        destination: String,
        password: String,
        video: Boolean,
        did: String,
        type: CallType,
        ts: Long
    ): Boolean {
        val res: Boolean
        val joinParam = JCMediaChannel.JoinParam()
        joinParam.capacity = 2
        joinParam.password = password
        JCManager.getInstance().mediaDevice.enableSpeaker(true)
        JCManager.getInstance().mediaChannel.enableUploadAudioStream(true)
        JCManager.getInstance().mediaChannel.enableUploadVideoStream(true)
        JCManager.getInstance().call.updateMediaConfig(JCCall.MediaConfig.generateByMode(JCCall.MediaConfig.MODE_720P))
        res = JCManager.getInstance().mediaChannel.join(destination, joinParam)
        if (res && video) {
            setVideo(true)
            setSpeaker(true)
        }
        return res
    }

    /**
     * Returns CallStatus.
     * Returns the current call status.
     * It can be one of the following:
     * - CallStatus.on
     * - CallStatus.off
     * - CallStatus.waiting
     */
    override fun callStatus(): String {
        val participants = JCManager.getInstance()?.mediaChannel?.participants
        if (participants == null || participants.isEmpty()) {
            return "off"
        }
        if (participants.size == 1) {
            return "waiting"
        }
        return "on"
    }

    /**
     * True if the user is in the call and is not muted.
     * Otherwise, returns false.
     */
    override fun audio(): Boolean {
        val selfAudio = JCManager.getInstance().mediaChannel.selfParticipant?.isAudio ?: false
        val audioStart = JCManager.getInstance().mediaDevice.isAudioStart
        val uploadLocalAudio = JCManager.getInstance().mediaChannel.uploadLocalAudio
        return selfAudio && audioStart && uploadLocalAudio
    }

    /**
     * True if the user is in the call and shares video.
     * Otherwise, returns false.
     */
    override fun video(): Boolean {
        val selfVideo = JCManager.getInstance().mediaChannel.selfParticipant?.isVideo ?: false
        val videoStart = JCManager.getInstance().mediaDevice.isCameraOpen
        val uploadLocalVideo = JCManager.getInstance().mediaChannel.uploadLocalVideo
        return selfVideo && videoStart && uploadLocalVideo
    }

    override fun speaker(): Boolean {
        return JCManager.getInstance().mediaDevice.isSpeakerOn
    }

    /**
     * True if the companion is in the call and is not muted.
     * Otherwise, returns false.
     */
    override fun otherAudio(): Boolean {
        return JCCallUtils.otherParticipant?.isAudio ?: false
    }

    /**
     * True if the companion is in the call and shares video.
     * Otherwise, returns false.
     */
    override fun otherVideo(): Boolean {
        return JCCallUtils.otherParticipant?.isVideo ?: false
    }

    /**
     * Hangs up the call or leaves the conference
     * depending on the call type.
     */
    override fun leave(): Boolean {
        return JCManager.getInstance().mediaChannel.leave()
    }

    /** Switches the camera (front/back) */
    override fun switchCamera() {
        JCManager.getInstance().mediaDevice.switchCamera()
    }

    /** Enables \ disables video. */
    override fun setVideo(video: Boolean) {
        JCManager.getInstance().mediaChannel.enableUploadVideoStream(video)
        if (video) {
            JCManager.getInstance().mediaDevice.startCamera()
        } else {
            JCManager.getInstance().mediaDevice.stopCamera()
        }
    }

    /** Enables \ disables audio. */
    override fun setAudio(audio: Boolean) {
        JCManager.getInstance().mediaChannel.enableUploadAudioStream(audio)
        if (audio) {
            JCManager.getInstance().mediaDevice.startAudio()
        } else {
            JCManager.getInstance().mediaDevice.stopAudio()
        }
        EventBus.getDefault().post(JCEvent(JCEvent.EventType.CALL_UPDATE))
    }

    /** Enables \ disables speaker. */
    override fun setSpeaker(speaker: Boolean) {
        JCManager.getInstance().mediaDevice.enableSpeaker(speaker)
        EventBus.getDefault().post(JCEvent(JCEvent.EventType.CALL_UPDATE))
    }


}