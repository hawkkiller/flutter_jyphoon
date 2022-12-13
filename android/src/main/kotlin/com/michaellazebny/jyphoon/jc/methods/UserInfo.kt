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
    fun setDisplayName(displayName: String) {
        jcManager.client.displayName = displayName
    }

    /**
     * Sets account number.
     * It is needed to set appKey before. Otherwise, it will fail.
     */
    fun setAccountNumber(accountNumber: String): Boolean {
        if (mLoginParam != null) {
            mLoginParam = LoginParam()
        }

        return jcManager.client.login(accountNumber, "123", mLoginParam)
    }

    /**
     * Returns [Void].
     *
     * Takes [Int] timeout in.
     *
     * Sets the timeout for the call request.
     */
    fun setTimeout(timeout: Long) {
        if (mLoginParam == null) {
            mLoginParam = LoginParam()
        }
        mLoginParam!!.timeout = timeout.toInt()
    }

    /**
     * Returns [Void].
     * Takes [String] hostUrl in.
     * Sets server address.
     */
    fun setServerAddress(hostUrl: String) {
        JCManager.getInstance().client.serverAddress = hostUrl
    }

    /**
     * Returns [String].
     * Get current user id.
     */
    fun getUserId(): String? {
        if (jcManager.client.userId != null) {
            return jcManager.client.userId
        }
        return null
    }
}