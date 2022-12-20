package com.michaellazebny.jyphoon.jc.views

import android.content.Context
import android.view.View
import android.view.ViewGroup
import com.juphoon.cloud.JCMediaChannel
import com.juphoon.cloud.JCMediaChannelParticipant
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCCallUtils
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.Tools.SPUtils
import com.michaellazebny.jyphoon.jc.model.CallType
import io.flutter.plugin.common.StandardMessageCodec
import io.flutter.plugin.platform.PlatformView
import io.flutter.plugin.platform.PlatformViewFactory

class CompanionView(callType: CallType) : PlatformView {
    private var view: View?
    override fun getView() = view

    init {
        when (callType) {
            CallType.CALL -> {
                val call = JCCallUtils.getActiveCall()
                view = JCCallUtils.getOtherCanvas(call)?.videoView
            }
            CallType.CONFERENCE -> {
                val jcManager = JCManager.getInstance()
                val selfParticipant = jcManager.mediaChannel.selfParticipant
                lateinit var otherParticipant: JCMediaChannelParticipant
                jcManager.mediaChannel.participants.forEach { participant ->
                    if (participant != selfParticipant) {
                        otherParticipant = participant
                    }
                }
                view = otherParticipant.startVideo(JCMediaDevice.RENDER_FULL_CONTENT, JCMediaChannel.PICTURESIZE_MAX)?.videoView
            }
        }
    }

    override fun dispose() {
        // remove a view of its parent
        val parent = view?.parent as ViewGroup?
        parent?.removeView(view)
    }
}

class RemoteViewFactory : PlatformViewFactory(StandardMessageCodec.INSTANCE) {
    override fun create(context: Context, viewId: Int, args: Any?): PlatformView {
        val map = args as Map<*, *>
        val callType = map["callType"] as Int
        return CompanionView(callType = CallType.fromInt(callType))
    }
}