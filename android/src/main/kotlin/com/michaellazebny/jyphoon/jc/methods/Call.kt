package com.michaellazebny.jyphoon.jc.methods

import android.content.Context
import com.juphoon.cloud.JCCall
import com.juphoon.cloud.JCCall.CallParam
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
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
    fun startCall(call: MethodCall, result: MethodChannel.Result, context: Context) {
        val accountNumber = call.argument<String>("accountNumber")
        if (accountNumber == null) {
            result.error("startVideoCall", "accountNumber is null", null)
            return
        }
        val video = call.argument<Boolean>("video")
        if (video == null) {
            result.error("startVideoCall", "video is null", null)
            return
        }
        val callTicket = SPUtils.get(context, "callTicket", "1234567890") as String
        val callParam = CallParam("video", callTicket)
        // start call, returns [Boolean] whether call was started or not
        val res = jcManager.call.call(accountNumber, video, callParam)
        val canvas = jcManager.call.activeCallItem.startSelfVideo(
            SPUtils.get(
                context,
                "RenderMode",
                JCMediaDevice.RENDER_FULL_CONTENT
            ) as Int
        )
        val remoteCanvas = jcManager.call.activeCallItem.startOtherVideo(
            SPUtils.get(
                context,
                "RenderMode",
                JCMediaDevice.RENDER_FULL_CONTENT
            ) as Int
        )
        Timer().schedule(object : TimerTask() {
            override fun run() {
                LocalView.localView = canvas.videoView
                RemoteView.remoteView = remoteCanvas.videoView
            }
        }, 5000)
        result.success(res)
    }
}