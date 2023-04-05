package com.michaellazebny.jyphoon.jc.platformViews

import android.content.Context
import android.view.View
import android.view.ViewGroup
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.SelfViewApi
import com.michaellazebny.jyphoon.jc.api.ViewCanvasApi
import io.flutter.plugin.common.BinaryMessenger
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class CallView(messenger: BinaryMessenger, canvasApi: ViewCanvasApi) : PlatformView, SelfViewApi {
    private var view: View?

    init {
        when (canvasApi) {
            is ViewCanvasApi.SelfViewCanvasApi -> {
                SelfViewApi.setUp(messenger, this)
            }
            is ViewCanvasApi.CompanionViewCanvasApi -> {
                SelfViewApi.setUp(messenger, this)
            }
        }
        view = canvasApi.startVideo(JCMediaDevice.RENDER_FULL_SCREEN)
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

class CallViewFactory(private val messenger: BinaryMessenger, private val canvasApi: ViewCanvasApi) :
    PlatformViewFactory(StandardMessageCodec.INSTANCE) {
    override fun create(context: Context, viewId: Int, args: Any?): PlatformView {
        return CallView(messenger, canvasApi)
    }
}