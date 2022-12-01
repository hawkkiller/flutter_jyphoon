package com.michaellazebny.jyphoon.jc.methods

import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager

class UserInfo {
    private val jcManager = JCManager.getInstance()

    /**
     * Sets account number.
     * It is needed to set appKey before. Otherwise, it will fail.
     */
    fun setAccountNumber(result: MethodChannel.Result, call: MethodCall) {
        try {
            if (mLoginParam != null) {
                mLoginParam = LoginParam();
            }
            val accountNumber = call.argument<String>("accountNumber")
                ?: return result.error("setAccountNumber", "accountNumber is null", "")

//          TODO: replace 123 with real data
            val res = jcManager.client.login(accountNumber, "123", mLoginParam);
            result.success(res)

        } catch (e: Exception) {
            result.error("setAccountNumber", e.message, null)
        }
    }
}