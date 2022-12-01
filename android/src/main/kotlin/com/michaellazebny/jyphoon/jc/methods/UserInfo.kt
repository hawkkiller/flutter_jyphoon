package com.michaellazebny.jyphoon.jc.methods

import androidx.annotation.NonNull
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
}