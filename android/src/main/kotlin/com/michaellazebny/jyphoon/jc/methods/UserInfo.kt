package com.michaellazebny.jyphoon.jc.methods

import com.juphoon.cloud.JCClient.LoginParam
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel

class UserInfo {
    private val jcManager = JCManager.getInstance()

    private var mLoginParam: LoginParam? = null

    /**
     * Returns [Void].
     *
     * Takes [String] displayName in.
     *
     * Sets the name that is visible to another participant(s).
     */
    fun setDisplayName(call: MethodCall, result: MethodChannel.Result) {
        try {
            val displayName = call.argument<String>("displayName")
            if (displayName == null) {
                result.error("setDisplayName", "displayName is null", null)
                return
            }
            jcManager.client.displayName = displayName
            result.success(null)
        } catch (e: Exception) {
            result.error("setDisplayName", e.message, null)
        }
    }

    /**
     * Sets account number.
     * It is needed to set appKey before. Otherwise, it will fail.
     */
    fun setAccountNumber(call: MethodCall, result: MethodChannel.Result) {
        try {
            if (mLoginParam != null) {
                mLoginParam = LoginParam();
            }
            val accountNumber = call.argument<String>("accountNumber")
                ?: return result.error("setAccountNumber", "accountNumber is null", "")

            // TODO: replace 123 with real data
            val res = jcManager.client.login(accountNumber, "123", mLoginParam);
            result.success(res)

        } catch (e: Exception) {
            result.error("setAccountNumber", e.message, null)
        }
    }

    /**
     * Returns [Void].
     *
     * Takes [Int] timeout in.
     *
     * Sets the timeout for the call request.
     */
    fun setTimeout(call: MethodCall, result: MethodChannel.Result) {
        try {
            val timeout = call.argument<Int>("timeout")
            if (timeout == null) {
                result.error("setTimeout", "timeout is null", null)
                return
            }
            if (mLoginParam == null) {
                mLoginParam = LoginParam()
            }
            mLoginParam!!.timeout = timeout
            result.success(null)
        } catch (e: Exception) {
            result.error("setTimeout", e.message, null)
        }
    }

    /**
     * Returns [Void].
     * Takes [String] host url in.
     * Sets set custom requestUrl.
     */
    fun setRequestUrl(call: MethodCall, result: MethodChannel.Result) {
        try {
            val host = call.argument<String>("hostUrl")
            if (host == null) {
                result.error("setRequestUrl", "hostUrl is null", null)
                return
            }
            JCManager.getInstance().client.serverAddress = host
            result.success(null)
        } catch (e: Exception) {
            result.error("setCustomHost", e.message, null)
        }
    }

}