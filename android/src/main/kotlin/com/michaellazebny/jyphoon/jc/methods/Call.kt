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
     *
     * Makes a call to the specified account.
     * If [JCCall.call] returns true then the call started.
     */
    fun startVideoCall(call: MethodCall, result: MethodChannel.Result) {
        val accountNumber = call.argument<String>("accountNumber")
        if (accountNumber == null) {
            result.error("startVideoCall", "accountNumber is null", null)
            return
        }
        val callTicket = SPUtils.get(context, "callTicket", "1234567890") as String
        val callParam = CallParam("video", callTicket)
        // start call, returns [Boolean] whether call was started or not
        val res = jcManager.call.call(accountNumber, true, callParam)
        result.success(res)
    }
}