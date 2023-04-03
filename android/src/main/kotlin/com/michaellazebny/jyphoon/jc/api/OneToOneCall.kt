package com.michaellazebny.jyphoon.jc.api

import com.michaellazebny.jyphoon.jc.CallType
import com.michaellazebny.jyphoon.jc.JyphoonCallApi

class OneToOneCall : JyphoonCallApi {
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
        type: CallType
    ): Boolean {
        TODO("Not yet implemented")
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
        TODO("Not yet implemented")
    }

    /** Enables \ disables video. */
    override fun setVideo(video: Boolean) {
        TODO("Not yet implemented")
    }

    /** Enables \ disables audio. */
    override fun setAudio(audio: Boolean) {
        TODO("Not yet implemented")
    }

    /** Enables \ disables speaker. */
    override fun setSpeaker(speaker: Boolean) {
        TODO("Not yet implemented")
    }

    /**
     * True if the user is in the call and is not muted.
     * Otherwise, returns false.
     */
    override fun audio(): Boolean {
        TODO("Not yet implemented")
    }

    /**
     * True if the user is in the call and shares video.
     * Otherwise, returns false.
     */
    override fun video(): Boolean {
        TODO("Not yet implemented")
    }

    /**
     * True if the companion is in the call and is not muted.
     * Otherwise, returns false.
     */
    override fun otherAudio(): Boolean {
        TODO("Not yet implemented")
    }

    /**
     * True if the companion is in the call and shares video.
     * Otherwise, returns false.
     */
    override fun otherVideo(): Boolean {
        TODO("Not yet implemented")
    }

    /**
     * Hangs up the call or leaves the conference
     * depending on the call type.
     */
    override fun leave(): Boolean {
        TODO("Not yet implemented")
    }

    /** Switches the camera (front/back) */
    override fun switchCamera() {
        TODO("Not yet implemented")
    }
}