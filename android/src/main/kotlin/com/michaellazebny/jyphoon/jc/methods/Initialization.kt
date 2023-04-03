package com.michaellazebny.jyphoon.jc.methods

import android.content.Context
import android.os.Build
import androidx.annotation.NonNull
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel

class Initialization {
    private val jcManager = JCManager.getInstance()

    /**
     * Returns whether JC was inited.
     * Returns true if JCManager.initialize() was successfully called.
     * Otherwise, returns false if initialize() was not called or failed.
     */
    fun isInited() = jcManager.isInited

    /**
     * Returns [Boolean].
     * Initializes the engine. It is needed to set appKey before. Otherwise, it will fail.
     */
    fun initialize(context: Context): Boolean {
        val res = jcManager.initialize(context)
        if (Build.VERSION.SDK_INT >= 31){
            JCManager.getInstance().mediaDevice.useInternalAudioDeviceLogic = false;
        }
        return res;
    }

    /**
     * Returns [Boolean].
     * Sets appKey in order to have access to the Jyphoon API.
     */
    fun setAppKey(appKey: String) {
        JCManager.sAppkey = appKey
    }
}




