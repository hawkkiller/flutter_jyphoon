package com.michaellazebny.jyphoon.jc.methods

import android.content.Context
import com.juphoon.cloud.JCCall
import com.juphoon.cloud.JCCall.CallParam
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.JcReceiver
import com.michaellazebny.jyphoon.jc.Toos.SPUtils
import com.michaellazebny.jyphoon.jc.views.LocalView
import com.michaellazebny.jyphoon.jc.views.RemoteView

class Call() {
    private val jcManager = JCManager.getInstance()

    /**
     * Returns [Void].
     * Takes [String] account in. It is the account identifier of the person you want to call.
     * Takes [Boolean] video in. It is the type of call you want to make. If true, it will be a video call.
     *
     * Makes a call to the specified account.
     * If [JCCall.call] returns true then the call started.
     */
    fun startCall(
        accountNumber: String,
        video: Boolean,
        callTicket: String,
        context: Context,
        receiver: JcReceiver
    ): Boolean {
        val callParam = CallParam("video", callTicket)
        // start call, returns [Boolean] whether call was started or not
        var item = jcManager.call.activeCallItem;
        if (item != null) {
            jcManager.call.term(item, JCCall.REASON_NONE, "term")
        }
        val res = jcManager.call.call(accountNumber, video, callParam)
        if (res) {
            item = jcManager.call.activeCallItem;
        } else {
            return res
        }
        if (video) {
            val canvas = item.startSelfVideo(
                SPUtils.get(
                    context,
                    "RenderMode",
                    JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
            val remoteCanvas = item.startOtherVideo(
                SPUtils.get(
                    context,
                    "RenderMode",
                    JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
            LocalView.localView = canvas.videoView
            RemoteView.remoteView = remoteCanvas.videoView
        }
        receiver.onCallStarted {}
        return res
    }

    fun startSelfVideo(context: Context, receiver: JcReceiver) {
        val item = jcManager.call.activeCallItem;
        val canvas = item.startSelfVideo(
            SPUtils.get(
                context,
                "RenderMode",
                JCMediaDevice.RENDER_FULL_CONTENT
            ) as Int
        )
        LocalView.localView = canvas.videoView
        receiver.onVideoStarted {}
    }

    fun stopSelfVideo(receiver: JcReceiver) {
        val item = jcManager.call.activeCallItem;
        item.stopSelfVideo()

        LocalView.localView = null
        receiver.onVideoStopped {}
    }

    fun startOtherVideo(context: Context) {
        val item = jcManager.call.activeCallItem;
        val canvas = item.startOtherVideo(
            SPUtils.get(
                context,
                "RenderMode",
                JCMediaDevice.RENDER_FULL_CONTENT
            ) as Int
        )
        RemoteView.remoteView = canvas.videoView
    }

    /**
     * Returns [Void].
     * Answers incoming call.
     */
    fun answerCall() {
        val item = JCManager.getInstance().call.activeCallItem
        if (item != null) {
            JCManager.getInstance().call.answer(item, true)
        }
    }
}