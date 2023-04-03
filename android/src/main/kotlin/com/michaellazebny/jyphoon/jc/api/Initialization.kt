package com.michaellazebny.jyphoon.jc.api

import android.content.Context
import android.os.Build
import com.juphoon.cloud.JCClient
import com.michaellazebny.jyphoon.jc.JyphoonInitializationApi
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager

class Initialization(private val context: Context) : JyphoonInitializationApi {
    /**
     * Returns whether JC was inited.
     * Returns true if JCManager.getInstance().initialize() was successfully called.
     * Otherwise, returns false if initialize() was not called or failed.
     */
    override fun isInited() = JCManager.getInstance().isInited

    /**
     * Returns [Boolean].
     * Initializes the engine. It is needed to set appKey before. Otherwise, it will fail.
     */
    override fun initialize(): Boolean {
        val res = JCManager.getInstance().initialize(context)
        if (Build.VERSION.SDK_INT >= 31) {
            JCManager.getInstance().mediaDevice.useInternalAudioDeviceLogic = false;
        }
        return res;
    }

    /**
     * Returns [Boolean].
     * Sets appKey in order to have access to the Jyphoon API.
     */
    override fun setAppKey(appKey: String) {
        JCManager.sAppkey = appKey
    }

    private var mLoginParam: JCClient.LoginParam? = null

    /**
     * Returns [Void].
     *
     * Takes [String] displayName in.
     *
     * Sets the name that is visible to another participant(s).
     */
    override fun setDisplayName(displayName: String) {
        JCManager.getInstance().client.displayName = displayName
    }

    /**
     * Sets account number.
     * It is needed to set appKey before. Otherwise, it will fail.
     */
    override fun setAccountNumber(accountNumber: String): Boolean {
        if (mLoginParam != null) {
            mLoginParam = JCClient.LoginParam()
        }

        return JCManager.getInstance().client.login(accountNumber, "123", mLoginParam)
    }

    /**
     * Returns [Void].
     *
     * Takes [Int] timeout in.
     *
     * Sets the timeout for the call request.
     */
    override fun setTimeout(timeout: Long) {
        if (mLoginParam == null) {
            mLoginParam = JCClient.LoginParam()
        }
        mLoginParam!!.timeout = timeout.toInt()
    }

    /**
     * Returns [Void].
     * Takes [String] hostUrl in.
     * Sets server address.
     */
    override fun setServerAddress(hostUrl: String) {
        JCManager.getInstance().client.serverAddress = hostUrl
    }

    /**
     * Returns [String].
     * Get current user id.
     */
    override fun getCurrentUserId(): String? {
        if (JCManager.getInstance().client.userId != null) {
            return JCManager.getInstance().client.userId
        }
        return null
    }
}




