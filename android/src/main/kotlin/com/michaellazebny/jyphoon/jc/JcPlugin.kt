package com.michaellazebny.jyphoon.jc

import android.content.Context
import com.michaellazebny.jyphoon.jc.handler.Handler

import com.michaellazebny.jyphoon.jc.methods.Call
import com.michaellazebny.jyphoon.jc.methods.Initialization
import com.michaellazebny.jyphoon.jc.methods.UserInfo
import com.michaellazebny.jyphoon.jc.views.SelfViewFactory
import com.michaellazebny.jyphoon.jc.views.CompanionViewFactory

import io.flutter.embedding.engine.plugins.FlutterPlugin

/** JcPlugin */
class JcPlugin : FlutterPlugin, JyphoonApi {
    private lateinit var applicationContext: Context
    private lateinit var receiver: JyphoonReceiver

    private val initialization = Initialization()
    private val userInfo = UserInfo()
    private val call = Call()
    private lateinit var handler: Handler

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        JyphoonApi.setUp(binding.binaryMessenger, null)
        handler.dispose()
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
        handler = Handler(receiver, this)
        handler.init()
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

    override fun call(confId: String, password: String, video: Boolean, asr: Boolean) =
        call.join(confId, password, video, asr);

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
