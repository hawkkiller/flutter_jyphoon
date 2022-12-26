package com.michaellazebny.jyphoon.jc

import android.content.Context
import com.michaellazebny.jyphoon.jc.handler.Handler

import com.michaellazebny.jyphoon.jc.methods.Conf
import com.michaellazebny.jyphoon.jc.methods.Initialization
import com.michaellazebny.jyphoon.jc.methods.UserInfo
import com.michaellazebny.jyphoon.jc.views.SelfViewFactory
import com.michaellazebny.jyphoon.jc.views.RemoteViewFactory

import io.flutter.embedding.engine.plugins.FlutterPlugin

/** JcPlugin */
class JcPlugin : FlutterPlugin, JCApi {
    private lateinit var applicationContext: Context
    private lateinit var receiver: JcReceiver

    private val initialization = Initialization()
    private val userInfo = UserInfo()
    private val conf = Conf()
    private lateinit var handler: Handler

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        JCApi.setUp(binding.binaryMessenger, null)
        handler.dispose()
    }

    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        applicationContext = flutterPluginBinding.applicationContext
        JCApi.setUp(flutterPluginBinding.binaryMessenger, this)
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "self-view",
            SelfViewFactory(),
        )
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "companion-view",
            RemoteViewFactory(),
        )
        receiver = JcReceiver(flutterPluginBinding.binaryMessenger)
        handler = Handler(receiver)
        handler.init()
    }

    override fun isInited() = initialization.isInited()

    override fun initialize() = initialization.initialize(applicationContext)

    override fun uninitialize() = initialization.uninitialize()

    override fun setAppKey(appKey: String) = initialization.setAppKey(appKey)

    override fun setDisplayName(displayName: String) = userInfo.setDisplayName(displayName)

    override fun setAccountNumber(accountNumber: String) = userInfo.setAccountNumber(accountNumber)

    override fun setTimeout(timeout: Long) = userInfo.setTimeout(timeout)

    override fun setServerAddress(serverAddress: String) = userInfo.setServerAddress(serverAddress)

    override fun confJoin(confId: String, password: String) = conf.join(confId, password)

    override fun getCurrentUserId() = userInfo.getUserId()

    override fun confLeave() = conf.leave()

    override fun switchVideo() = conf.switchVideo()

    override fun switchAudio() = conf.switchAudio()

    override fun audio() = conf.audio()

    override fun otherAudio() = conf.otherAudio()

    override fun video() = conf.video()

    override fun otherVideo() = conf.otherVideo()
}
