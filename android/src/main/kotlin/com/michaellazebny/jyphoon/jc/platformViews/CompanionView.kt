package com.michaellazebny.jyphoon.jc.platformViews

import android.content.Context
import android.view.View
import android.view.ViewGroup
import com.juphoon.cloud.JCMediaChannel
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.CompanionViewApi
import com.michaellazebny.jyphoon.jc.utils.JCCallUtils
import io.flutter.plugin.common.BinaryMessenger
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class CompanionView(messenger: BinaryMessenger) : PlatformView, CompanionViewApi {
    private var view: View?
    override fun getView() = view

    init {
        CompanionViewApi.setUp(messenger, this)
        val otherParticipant = JCCallUtils.otherParticipant
        view = otherParticipant?.startVideo(
            JCMediaDevice.RENDER_FULL_SCREEN,
            JCMediaChannel.PICTURESIZE_MIN
        )?.videoView
    }

    override fun dispose() {
        // remove a view of its parent
        val parent = view?.parent as ViewGroup?
        parent?.removeView(view)
    }

    override fun setCompanionFrame(width: Double, height: Double) {
        view?.layoutParams?.width = ViewHelper.convertDpToPixel(width).toInt()
        view?.layoutParams?.height = ViewHelper.convertDpToPixel(height).toInt()
    }
}

class CompanionViewFactory(private val messenger: BinaryMessenger) :
    PlatformViewFactory(StandardMessageCodec.INSTANCE) {
    override fun create(context: Context, viewId: Int, args: Any?): PlatformView {
        return CompanionView(messenger)
    }
}