package com.michaellazebny.jyphoon.jc.views

import android.content.Context
import android.view.View
import android.view.ViewGroup
import com.juphoon.cloud.JCMediaChannel
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager
import com.michaellazebny.jyphoon.jc.SelfViewApi
import io.flutter.plugin.common.BinaryMessenger
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class SelfView(messenger: BinaryMessenger) : PlatformView, SelfViewApi {
    private var view: View?

    init {
        SelfViewApi.setUp(messenger, this)
        val jcManager = JCManager.getInstance()
        val selfParticipant = jcManager.mediaChannel?.selfParticipant
        view = selfParticipant?.startVideo(
            JCMediaDevice.RENDER_FULL_SCREEN,
            JCMediaChannel.PICTURESIZE_MIN
        )?.videoView
    }

    override fun getView() = view

    override fun dispose() {
        // remove a view of its parent
        val parent = view?.parent as ViewGroup?
        parent?.removeView(view)
    }

    override fun setSelfFrame(width: Double, height: Double) {
        view?.layoutParams?.width = ViewHelper.convertDpToPixel(width).toInt()
        view?.layoutParams?.height = ViewHelper.convertDpToPixel(height).toInt()
    }
}

class SelfViewFactory(private val messenger: BinaryMessenger) :
    PlatformViewFactory(StandardMessageCodec.INSTANCE) {
    override fun create(context: Context, viewId: Int, args: Any?): PlatformView {
        return SelfView(messenger)
    }
}