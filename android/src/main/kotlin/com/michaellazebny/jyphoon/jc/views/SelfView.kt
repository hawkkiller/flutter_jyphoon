package com.michaellazebny.jyphoon.jc.views

import android.content.Context
import android.view.View
import android.view.ViewGroup
import com.juphoon.cloud.JCMediaChannel
import com.juphoon.cloud.JCMediaChannelParticipant
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCCallUtils
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.model.CallType
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class SelfView(callType: CallType) : PlatformView {
    private var view: View? = when (callType) {
        CallType.CALL -> {
            val call = JCCallUtils.getActiveCall()
            JCCallUtils.getSelfCanvas(call)?.videoView
        }
        CallType.CONFERENCE -> {
            val jcManager = JCManager.getInstance()
            val selfParticipant = jcManager.mediaChannel.selfParticipant
            selfParticipant.startVideo(JCMediaDevice.RENDER_FULL_CONTENT, JCMediaChannel.PICTURESIZE_MAX)?.videoView
        }
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
        val map = args as Map<*, *>
        val callType = map["callType"] as Int
        return SelfView(callType = CallType.fromInt(callType))
    }
}