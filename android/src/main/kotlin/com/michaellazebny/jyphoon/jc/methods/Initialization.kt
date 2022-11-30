package com.michaellazebny.jyphoon.jc.methods

import android.content.Context
import androidx.annotation.NonNull
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
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
     * Returns void.
     * Initializes the engine. It is needed to set appKey before. Otherwise, it will fail.
     */
    fun initialize(context: Context, @NonNull result: MethodChannel.Result) {
        try {
            jcManager.initialize(context)
            result.success(null)
        } catch (e: Exception) {
            result.error("initialize", e.message, null)
        }
    }
}
