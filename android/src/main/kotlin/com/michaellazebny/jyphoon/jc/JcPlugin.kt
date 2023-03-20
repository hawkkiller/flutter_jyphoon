package com.michaellazebny.jyphoon.jc

import android.content.Context
import com.michaellazebny.jyphoon.jc.handler.Handler

import com.michaellazebny.jyphoon.jc.methods.MediaChannel
import com.michaellazebny.jyphoon.jc.methods.Initialization
import com.michaellazebny.jyphoon.jc.methods.UserInfo
import com.michaellazebny.jyphoon.jc.views.SelfViewFactory
import com.michaellazebny.jyphoon.jc.views.RemoteViewFactory

import io.flutter.embedding.engine.plugins.FlutterPlugin

/** JcPlugin */
class JcPlugin : FlutterPlugin, JyphoonApi {
    private lateinit var applicationContext: Context
    private lateinit var receiver: JyphoonReceiver

    private val initialization = Initialization()
    private val userInfo = UserInfo()
    private val mediaChannel = MediaChannel()
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
            SelfViewFactory(),
        )
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "companion-view",
            RemoteViewFactory(),
        )
        receiver = JyphoonReceiver(flutterPluginBinding.binaryMessenger)
        handler = Handler(receiver)
        handler.init()
    }

    override fun isInited() = initialization.isInited()

    override fun initialize() = initialization.initialize(applicationContext)

    override fun setAppKey(appKey: String) = initialization.setAppKey(appKey)

    override fun setDisplayName(displayName: String) = userInfo.setDisplayName(displayName)

    override fun setAccountNumber(accountNumber: String) = userInfo.setAccountNumber(accountNumber)

    override fun setTimeout(timeout: Long) = userInfo.setTimeout(timeout)

    override fun setServerAddress(serverAddress: String) = userInfo.setServerAddress(serverAddress)

    override fun setVideo(video: Boolean) = mediaChannel.setVideo(video)

    override fun setAudio(audio: Boolean) = mediaChannel.setAudio(audio)

    override fun confJoin(confId: String, password: String, video: Boolean) = mediaChannel.join(confId, password, video)

    override fun getCurrentUserId() = userInfo.getUserId()

    override fun confLeave() = mediaChannel.leave()

    override fun audio() = mediaChannel.audio()

    override fun otherAudio() = mediaChannel.otherAudio()

    override fun video() = mediaChannel.video()

    override fun otherVideo() = mediaChannel.otherVideo()

    override fun confStatus() = mediaChannel.confStatus()

    override fun switchCamera() = mediaChannel.switchCamera()

    override fun setSpeaker(speaker: Boolean) = mediaChannel.setSpeaker(speaker)
}
