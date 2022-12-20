package com.michaellazebny.jyphoon.jc.methods

import android.content.Context
import com.juphoon.cloud.JCCall
import com.juphoon.cloud.JCCall.CallParam
import com.juphoon.cloud.JCMediaChannel.JoinParam
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.Tools.SPUtils

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
                    context, "RenderMode", JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
            val remoteCanvas = item.startOtherVideo(
                SPUtils.get(
                    context, "RenderMode", JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
        }
        return res
    }

    fun confJoin(channelId: String, password: String, context: Context): Boolean {
        // 生成 join 参数
        val joinParam = JoinParam()
        joinParam.capacity = 6
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

    fun updateSelfVideo(context: Context, condition: Boolean) {
        val item = jcManager.call.activeCallItem;
        if (condition) {
            item.startSelfVideo(
                SPUtils.get(
                    context, "RenderMode", JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
        } else {
            item.stopSelfVideo()
        }
    }

    fun updateOtherVideo(condition: Boolean, context: Context) {
        val item = jcManager.call.activeCallItem;
        if (condition) {
            item.startOtherVideo(
                SPUtils.get(
                    context, "RenderMode", JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
        } else {
            item.stopOtherVideo()
        }
    }

    fun updateSelfVoice(condition: Boolean) {
        val call = jcManager.call
        val item = call.activeCallItem
        call.muteMicrophone(item, condition)
    }

    fun updateOtherVoice(condition: Boolean) {
        val call = jcManager.call
        val item = call.activeCallItem
        call.muteSpeaker(item, condition)
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