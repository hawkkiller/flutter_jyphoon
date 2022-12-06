package com.michaellazebny.jyphoon.jc.views

import android.content.Context
import android.util.Log
import android.view.View
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class LocalView(context: Context, id: Int, creationParams: Map<String?, Any?>?) : PlatformView {
    companion object {
        var localView: View? = null
    }

    override fun getView() = localView

    override fun dispose() {
        localView = null
    }
}

class LocalViewFactory : PlatformViewFactory(StandardMessageCodec.INSTANCE) {
    override fun create(context: Context, viewId: Int, args: Any?): PlatformView {
        Log.d("ADDED", "misha")
        return LocalView(context, viewId, null)
    }
}