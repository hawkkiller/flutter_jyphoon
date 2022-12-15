package com.michaellazebny.jyphoon.jc.methods

import android.content.Context
import com.juphoon.cloud.JCCall
import com.juphoon.cloud.JCCall.CallParam
import com.juphoon.cloud.JCMediaChannel
import com.juphoon.cloud.JCMediaChannel.JoinParam
import com.juphoon.cloud.JCMediaChannel.RecordParam
import com.juphoon.cloud.JCMediaDevice
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager
import com.michaellazebny.jyphoon.jc.JcReceiver
import com.michaellazebny.jyphoon.jc.Toos.SPUtils
import com.michaellazebny.jyphoon.jc.views.LocalView
import com.michaellazebny.jyphoon.jc.views.RemoteView
import org.greenrobot.eventbus.EventBus

class Call() {
    private val jcManager = JCManager.getInstance()

    /**
     * Returns [Void].
     * Takes [String] account in. It is the account identifier of the person you want to call.
     * Takes [Boolean] video in. It is the type of call you want to make. If true, it will be a video call.
     *
     * Makes a call to the specified account.
     * If [JCCall.call] returns true then the call started.
     */
    fun startCall(
        accountNumber: String,
        video: Boolean,
        callTicket: String,
        context: Context,
        receiver: JcReceiver
    ): Boolean {
        val callParam = CallParam("video", callTicket)
        // start call, returns [Boolean] whether call was started or not
        var item = jcManager.call.activeCallItem;
        if (item != null) {
            jcManager.call.term(item, JCCall.REASON_NONE, "term")
        }
        val res = jcManager.call.call(accountNumber, video, callParam)
        if (res) {
            item = jcManager.call.activeCallItem;
        } else {
            return res
        }
        if (video) {
            val canvas = item.startSelfVideo(
                SPUtils.get(
                    context, "RenderMode", JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
            val remoteCanvas = item.startOtherVideo(
                SPUtils.get(
                    context, "RenderMode", JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
            LocalView.localView = canvas.videoView
            RemoteView.remoteView = remoteCanvas.videoView
        }
        receiver.onCallStarted {}
        return res
    }

    fun confJoin(channelId: String, password: String, context: Context): Boolean {
        // 生成 join 参数
        val joinParam = JoinParam()
        joinParam.capacity = 6
        joinParam.smooth = true
        joinParam.password = password
        joinParam.maxResolution = 0
        joinParam.heartbeatTime = 20
        joinParam.heartbeatTimeout = 60
        joinParam.uriMode = false
        joinParam.framerate = 24
        joinParam.customVideoResolution = ""
        joinParam.videoRatio = 1.78f
//        val joinParam = JoinParam()
//        joinParam.capacity = SPUtils.get(context, "ConfJoinCapacity", 16) as Int
//        joinParam.password = SPUtils.get(context, "ConfJoinPassword", password) as String
//        joinParam.smooth = SPUtils.get(context, "ConfJoinSmooth", true) as Boolean
//        joinParam.maxResolution = SPUtils.get(context, "ConfJoinMaxResolution", 0) as Int
//        joinParam.heartbeatTime = SPUtils.get(context, "ConfJoinHeartbeatTime", 20) as Int
//        joinParam.heartbeatTimeout = SPUtils.get(context, "ConfJoinHeartbeatTimeout", 60) as Int
//        joinParam.uriMode = SPUtils.get(context, "ConfJoinUriMode", false) as Boolean
//        joinParam.framerate = SPUtils.get(context, "ConfJoinFramerate", 24) as Int
////            joinParam.maxBitrate = (int)SPUtils.get(context,"ConfJoinMaxBitrate", 2000);
//        //            joinParam.maxBitrate = (int)SPUtils.get(context,"ConfJoinMaxBitrate", 2000);
//        joinParam.customProperty = SPUtils.get(context, "ConfJoinCustomProperty", "") as String
//        joinParam.defaultBitrate = SPUtils.get(context, "ConfDefaultBitrate", 0) as Int
//        if (SPUtils.get(context, "ConfCdn", false) as Boolean) {
//            joinParam.cdn = SPUtils.get(context, "ConfCdnUrl", "") as String
//        }
//        if (SPUtils.get(context, "ConfRecord", false) as Boolean) {
//            joinParam.record = RecordParam()
//            if (SPUtils.get(context, "RecordType", 0) as Int == 0) {
//                joinParam.record.recordString = RecordParam.buildQiniuRecordParam(
//                    SPUtils.get(context, "ConfRecordQiNiuVideo", true) as Boolean,
//                    SPUtils.get(context, "ConfRecordQiNiuBucketName", "") as String,
//                    SPUtils.get(context, "ConfRecordQiNiuSecretKey", "") as String,
//                    SPUtils.get(context, "ConfRecordQiNiuAccessKey", "") as String,
//                    SPUtils.get(context, "ConfRecordQiNiuFilename", "") as String
//                )
//            } else if (SPUtils.get(context, "RecordType", 0) as Int == 1) {
//                joinParam.record.recordString = RecordParam.buildAliossRecordParam(
//                    SPUtils.get(context, "ConfRecordAliVideo", true) as Boolean,
//                    SPUtils.get(context, "ConfRecordAliBucketName", "") as String,
//                    SPUtils.get(context, "ConfRecordAliSecretKey", "") as String,
//                    SPUtils.get(context, "ConfRecordAliAccessKey", "") as String,
//                    SPUtils.get(context, "ConfRecordAliUploadEndPoint", "") as String,
//                    SPUtils.get(context, "ConfRecordAliFilename", "") as String
//                )
//            }
//        }
//        joinParam.customVideoResolution =
//            SPUtils.get(context, "ConfCustomVideoResolution", "") as String
//        joinParam.videoRatio = SPUtils.get(context, "ConfVideoRatio", 1.78f) as Float
        return jcManager.mediaChannel.join(channelId, joinParam)
    }

    fun startSelfVideo(context: Context, receiver: JcReceiver) {
        val item = jcManager.call.activeCallItem;
        if (condition) {
            val canvas = item.startSelfVideo(
                SPUtils.get(
                    context, "RenderMode", JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
            LocalView.localView = canvas.videoView
        } else {
            item.stopSelfVideo()
            LocalView.localView = null
        }
    }

    fun setOtherVideoCondition(condition: Boolean, context: Context) {
        val item = jcManager.call.activeCallItem;
        if (condition) {
            val canvas = item.startOtherVideo(
                SPUtils.get(
                    context, "RenderMode", JCMediaDevice.RENDER_FULL_CONTENT
                ) as Int
            )
            RemoteView.remoteView = canvas.videoView
        } else {
            item.stopOtherVideo()
            RemoteView.remoteView = null
        }
    }

    fun setSelfVoiceCondition(condition: Boolean) {
        val call = jcManager.call
        val item = call.activeCallItem
        call.muteMicrophone(item, condition)
    }

    fun setOtherVoiceCondition(condition: Boolean) {
        val call = jcManager.call
        val item = call.activeCallItem
        call.muteSpeaker(item, condition)
    }


    /**
     * Returns [Void].
     * Answers incoming call.
     */
    fun answerCall() {
        val item = JCManager.getInstance().call.activeCallItem
        if (item != null) {
            JCManager.getInstance().call.answer(item, true)
        }
    }
}