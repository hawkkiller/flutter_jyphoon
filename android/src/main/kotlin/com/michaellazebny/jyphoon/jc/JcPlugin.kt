package com.michaellazebny.jyphoon.jc

import android.content.Context
import com.michaellazebny.jyphoon.jc.sdkEventsHandler.SdkEventsHandler

import com.michaellazebny.jyphoon.jc.api.Call
import com.michaellazebny.jyphoon.jc.api.GroupCall
import com.michaellazebny.jyphoon.jc.api.Initialization
import com.michaellazebny.jyphoon.jc.api.UserInfo
import com.michaellazebny.jyphoon.jc.platformViews.SelfViewFactory
import com.michaellazebny.jyphoon.jc.platformViews.CompanionViewFactory

import io.flutter.embedding.engine.plugins.FlutterPlugin
class G(B: JyphoonApi) : JyphoonApi by B
/** JcPlugin */
class JcPlugin : FlutterPlugin, JyphoonApi {
    private lateinit var applicationContext: Context
    private lateinit var receiver: JyphoonReceiver

    private val initialization = Initialization()
    private val userInfo = UserInfo()
    private val call = Call()
    private lateinit var sdkEventsHandler: SdkEventsHandler

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {

        JyphoonApi.setUp(binding.binaryMessenger, null)
        sdkEventsHandler.dispose()
    }

    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        applicationContext = flutterPluginBinding.applicationContext
        JyphoonApi.setUp(flutterPluginBinding.binaryMessenger, this)
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "self-view",
            SelfViewFactory(flutterPluginBinding.binaryMessenger),
        )
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "companion-view",
            CompanionViewFactory(flutterPluginBinding.binaryMessenger),
        )
        receiver = JyphoonReceiver(flutterPluginBinding.binaryMessenger)
        sdkEventsHandler = SdkEventsHandler(receiver, this)
        sdkEventsHandler.init()
    }

    override fun isInited() = initialization.isInited()

    override fun initialize() = initialization.initialize(applicationContext)

    override fun setAppKey(appKey: String) = initialization.setAppKey(appKey)

    override fun setDisplayName(displayName: String) = userInfo.setDisplayName(displayName)

    override fun setAccountNumber(accountNumber: String) = userInfo.setAccountNumber(accountNumber)

    override fun setTimeout(timeout: Long) = userInfo.setTimeout(timeout)

    override fun setServerAddress(serverAddress: String) = userInfo.setServerAddress(serverAddress)

    override fun setVideo(video: Boolean) = call.setVideo(video)

    override fun setAudio(audio: Boolean) = call.setAudio(audio)

    override fun call(confId: String, password: String, video: Boolean, type: CallType) =
        call.join(confId, password, video, type)

    override fun getCurrentUserId() = userInfo.getUserId()

    override fun leave() = call.leave()

    override fun audio() = call.audio()

    override fun otherAudio() = call.otherAudio()

    override fun video() = call.video()

    override fun otherVideo() = call.otherVideo()

    override fun callStatus() = call.confStatus()

    override fun switchCamera() = call.switchCamera()

    override fun setSpeaker(speaker: Boolean) = call.setSpeaker(speaker)
}
