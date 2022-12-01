package com.michaellazebny.jyphoon.jc.methods

import androidx.annotation.NonNull
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel

class UserInfo {
    private val jcManager = JCManager.getInstance()


    /**
     * Returns [Void].
     *
     * Takes [String] displayName in.
     *
     * Sets the name that is visible to another participant(s).
     */
    fun setDisplayName(@NonNull call: MethodCall, @NonNull result: MethodChannel.Result) {
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
}