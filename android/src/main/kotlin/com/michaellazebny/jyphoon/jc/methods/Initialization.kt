package com.michaellazebny.jyphoon.jc.methods

import androidx.annotation.NonNull
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import io.flutter.plugin.common.MethodChannel

class Initialization {
    private val jcManager = JCManager.getInstance()

    /**
     * Returns whether JC was initialized.
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
}
