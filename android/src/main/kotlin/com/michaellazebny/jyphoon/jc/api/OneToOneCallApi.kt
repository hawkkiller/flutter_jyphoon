package com.michaellazebny.jyphoon.jc.api

import android.util.Log
import com.juphoon.cloud.JCCall
import com.michaellazebny.jyphoon.jc.CallType
import com.michaellazebny.jyphoon.jc.JyphoonCallApi
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager

class OneToOneCallApi : JyphoonCallApi {
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
        val param = JCCall.CallParam(
            if (video) "video" else "audio",
            "${did}_$ts",
        )
        val res = JCManager.getInstance().call.call(destination, video, param)
        if (res && video) {
            setVideo(true)
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
        val call = JCManager.getInstance().call
        val activeCall = call.activeCallItem ?: return "off"
        JCCall.REASON_NONE
        Log.i("JC_CALL_STATUS_REASON", activeCall.reason.toString())

        return when (activeCall.state) {
            JCCall.STATE_OK, JCCall.STATE_TALKING -> "on"
            JCCall.STATE_PENDING, JCCall.STATE_CONNECTING, JCCall.STATE_INIT -> "waiting"
            else -> "off"
        }
    }

    /**
     * True if the user is in the call and is not muted.
     * Otherwise, returns false.
     */
    override fun audio(): Boolean {
        val audioStart = JCManager.getInstance().mediaDevice.isAudioStart
        val uploadLocalAudio = JCManager.getInstance().call.activeCallItem?.microphoneMute ?: false
        return audioStart && uploadLocalAudio
    }

    /**
     * True if the user is in the call and shares video.
     * Otherwise, returns false.
     */
    override fun video(): Boolean {
        val videoStart = JCManager.getInstance().mediaDevice.isCameraOpen
        val uploadVideoStreamSelf =
            JCManager.getInstance().call.activeCallItem.uploadVideoStreamSelf
        val video = JCManager.getInstance().call.activeCallItem.video
        return videoStart && uploadVideoStreamSelf && video
    }

    /**
     * True if the companion is in the call and is not muted.
     * Otherwise, returns false.
     */
    override fun otherAudio(): Boolean {
        return !JCManager.getInstance().call.activeCallItem.otherAudioInterrupt
    }

    /**
     * True if the companion is in the call and shares video.
     * Otherwise, returns false.
     */
    override fun otherVideo(): Boolean {
        return JCManager.getInstance().call.activeCallItem.uploadVideoStreamOther
    }

    /**
     * Hangs up the call or leaves the conference
     * depending on the call type.
     */
    override fun leave(): Boolean {
        val call = JCManager.getInstance().call
        call.term(call.activeCallItem, JCCall.REASON_NONE, "term")
        return true
    }

    /** Switches the camera (front/back) */
    override fun switchCamera() {
        JCManager.getInstance().mediaDevice.switchCamera()
    }

    /** Enables \ disables video. */
    override fun setVideo(video: Boolean) {
        if (video) {
            JCManager.getInstance().mediaDevice.startCamera()
        } else {
            JCManager.getInstance().mediaDevice.stopCamera()
        }
    }

    /** Enables \ disables audio. */
    override fun setAudio(audio: Boolean) {
        if (audio) {
            JCManager.getInstance().mediaDevice.startAudio()
        } else {
            JCManager.getInstance().mediaDevice.stopAudio()
        }
    }

    /** Enables \ disables speaker. */
    override fun setSpeaker(speaker: Boolean) {
        JCManager.getInstance().mediaDevice.enableSpeaker(speaker)
    }

}