package com.michaellazebny.jyphoon.jc.views

import android.content.Context
import android.view.View
import android.view.ViewGroup
import com.michaellazebny.jyphoon.jc.JCWrapper.JCCallUtils
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class CompanionView : PlatformView {
    private var view: View
    override fun getView() = view

    init {
        val call = JCCallUtils.getActiveCall()
        view = JCCallUtils.getOtherCanvas(call).videoView
    }

    override fun dispose() {
        // remove a view of its parent
        val parent = view.parent as ViewGroup?
        parent?.removeView(view)
    }
}

class RemoteViewFactory : PlatformViewFactory(StandardMessageCodec.INSTANCE) {
    override fun create(context: Context, viewId: Int, args: Any?): PlatformView {
        return CompanionView()
    }
}