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
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import java.util.*
import java.util.logging.Handler

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
    fun startCall(accountNumber: String, video: Boolean, context: Context): Boolean {
        val callTicket = SPUtils.get(context, "callTicket", "1234567890") as String
        val callParam = CallParam("video", callTicket)
        // start call, returns [Boolean] whether call was started or not
        var item = jcManager.call.activeCallItem;
        if (item != null) {
            jcManager.call.term(item, JCCall.REASON_NONE, "term")
        }
        val res = jcManager.call.call(accountNumber, video, callParam)
        if (res) {
            item = jcManager.call.activeCallItem;
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
}