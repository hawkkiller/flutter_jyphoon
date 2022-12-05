package com.michaellazebny.jyphoon.jc.views

import android.content.Context
import android.view.View
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class RemoteView(context: Context, id: Int, creationParams: Map<String?, Any?>?) : PlatformView {
    companion object {
        var remoteView: View? = null
    }

    override fun getView() = remoteView

    override fun dispose() {
        remoteView = null
    }
}

class RemoteViewFactory : PlatformViewFactory(StandardMessageCodec.INSTANCE) {
    override fun create(context: Context, viewId: Int, args: Any?): PlatformView {
        return RemoteView(context, viewId, null)
    }
}