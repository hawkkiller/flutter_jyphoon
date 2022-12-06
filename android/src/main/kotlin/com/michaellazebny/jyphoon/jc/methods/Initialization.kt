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
    fun isInited() = jcManager.isInited

    /**
     * Returns [Boolean].
     * Initializes the engine. It is needed to set appKey before. Otherwise, it will fail.
     */
    fun initialize(context: Context) = jcManager.initialize(context)

    /**
     * Returns [Boolean].
     * Sets appKey in order to have access to the Jyphoon API.
     */
    fun setAppKey(appKey: String) {
        JCManager.sAppkey = appKey
    }

    /**
     * Returns [Void]
     * Deinitialize the engine. After call this method you can't use call mechanics
     */
    fun uninitialize() = jcManager.uninitialize()
}




