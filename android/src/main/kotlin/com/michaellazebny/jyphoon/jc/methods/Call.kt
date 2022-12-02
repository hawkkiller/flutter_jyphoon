package com.michaellazebny.jyphoon.jc.methods

import android.content.Context
import com.juphoon.cloud.JCCall
import com.juphoon.cloud.JCCall.CallParam
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.Toos.SPUtils
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel

class Call(private val context: Context) {
    private val jcManager = JCManager.getInstance()

    /**
     * Returns [Void].
     * Takes [String] account in. It is the account identifier of the person you want to call.
     * Takes [Boolean] video in. It is the type of call you want to make. If true, it will be a video call.
     *
     * Makes a call to the specified account.
     * If [JCCall.call] returns true then the call started.
     */
    fun startCall(call: MethodCall, result: MethodChannel.Result) {
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
        result.success(res)
    }
}