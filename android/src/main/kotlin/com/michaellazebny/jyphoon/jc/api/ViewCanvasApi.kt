package com.michaellazebny.jyphoon.jc.api

import android.view.View
import com.juphoon.cloud.JCMediaChannel
import com.michaellazebny.jyphoon.jc.CallType
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager
import com.michaellazebny.jyphoon.jc.utils.JCCallUtils

sealed class ViewCanvasApi {
    abstract fun startVideo(mode: Int) : View?

    class SelfViewCanvasApi : ViewCanvasApi() {
        private val oneToOne: SelfViewCanvasApiOneToOne = SelfViewCanvasApiOneToOne()
        private val group: SelfViewCanvasApiGroup = SelfViewCanvasApiGroup()

        override fun startVideo(mode: Int): View? {
            return when (JCCallUtils.getCallType()) {
                CallType.ONETOONE -> oneToOne.startVideo(mode)
                CallType.GROUP -> group.startVideo(mode)
                else -> null
            }
        }

        class SelfViewCanvasApiOneToOne {
            fun startVideo(mode: Int): View? {
                return JCManager.getInstance().call.activeCallItem.startSelfVideo(mode)?.videoView
            }
        }

        class SelfViewCanvasApiGroup  {
            fun startVideo(mode: Int): View? {
                return JCManager.getInstance().mediaChannel.selfParticipant?.startVideo(
                    mode,
                    JCMediaChannel.PICTURESIZE_MIN
                )?.videoView
            }
        }
    }

    class CompanionViewCanvasApi : ViewCanvasApi() {
        private val oneToOne: CompanionCanvasApiOneToOne = CompanionCanvasApiOneToOne()
        private val group: CompanionViewCanvasApiGroup = CompanionViewCanvasApiGroup()

        override fun startVideo(mode: Int): View? {
            return when (JCCallUtils.getCallType()) {
                CallType.ONETOONE -> oneToOne.startVideo(mode)
                CallType.GROUP -> group.startVideo(mode)
                else -> null
            }
        }

        class CompanionCanvasApiOneToOne {
            fun startVideo(mode: Int): View? {
                return JCManager.getInstance().call.activeCallItem.startOtherVideo(mode)?.videoView
            }
        }

        class CompanionViewCanvasApiGroup {
            fun startVideo(mode: Int): View? {
                return JCCallUtils.otherParticipant?.startVideo(
                    mode,
                    JCMediaChannel.PICTURESIZE_MIN
                )?.videoView
            }
        }
    }
}
