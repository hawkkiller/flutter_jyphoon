package com.michaellazebny.jyphoon.jc.views

import android.content.Context
import android.view.View
import android.view.ViewGroup
import com.juphoon.cloud.JCMediaChannel
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.model.CallType
import com.michaellazebny.jyphoon.jc.tools.JCCallUtils
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class SelfView : PlatformView {
    private var view: View?
    init {
        val jcManager = JCManager.getInstance()
        val selfParticipant = jcManager.mediaChannel?.selfParticipant
        view = selfParticipant?.startVideo(JCMediaDevice.RENDER_FULL_CONTENT, JCMediaChannel.PICTURESIZE_MIN)?.videoView
    }

    override fun getView() = view

    override fun dispose() {
        // remove a view of its parent
        val parent = view?.parent as ViewGroup?
        parent?.removeView(view)
    }
}

class SelfViewFactory : PlatformViewFactory(StandardMessageCodec.INSTANCE) {
    override fun create(context: Context, viewId: Int, args: Any?): PlatformView {
        return SelfView()
    }
}