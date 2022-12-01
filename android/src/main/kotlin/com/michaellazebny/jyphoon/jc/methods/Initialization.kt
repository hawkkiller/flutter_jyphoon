package com.michaellazebny.jyphoon.jc.methods

import android.content.Context
import androidx.annotation.NonNull
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel

class Initialization {
    private val jcManager = JCManager.getInstance()

    /**
     * Returns whether JC was inited.
     * Returns true if JCManager.initialize() was successfully called.
     * Otherwise, returns false if initialize() was not called or failed.
     */
    fun isInited(@NonNull result: MethodChannel.Result) {
        try {
            val isInited = jcManager.isInited
            result.success(isInited)
        } catch (e: Exception) {
            result.error("isInited", e.message, null)
        }
    }

    /**
     * Returns [Boolean].
     * Initializes the engine. It is needed to set appKey before. Otherwise, it will fail.
     */
    fun initialize(context: Context, @NonNull result: MethodChannel.Result) {
        try {
            val res = jcManager.initialize(context)
            result.success(res)
        } catch (e: Exception) {
            result.error("initialize", e.message, null)
        }
    }

    /**
     * Returns [Boolean].
     * Sets appKey in order to have access to the Jyphoon API.
     */
    fun setAppKey(@NonNull call: MethodCall, @NonNull result: MethodChannel.Result) {
        try {
            val appKey = call.argument<String>("appKey")
            if (appKey == null) {
                result.error("setAppKey", "appKey is null", null)
                return
            }
            JCManager.sAppkey = appKey
            result.success(null)
        } catch (e: Exception) {
            result.error("setAppKey", e.message, null)
        }
    }
}




