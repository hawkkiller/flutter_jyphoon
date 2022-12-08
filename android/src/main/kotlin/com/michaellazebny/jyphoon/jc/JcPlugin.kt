package com.michaellazebny.jyphoon.jc

import android.content.Context

import com.michaellazebny.jyphoon.jc.methods.Call
import com.michaellazebny.jyphoon.jc.methods.Initialization
import com.michaellazebny.jyphoon.jc.methods.UserInfo
import com.michaellazebny.jyphoon.jc.views.LocalViewFactory
import com.michaellazebny.jyphoon.jc.views.RemoteViewFactory

import io.flutter.embedding.engine.plugins.FlutterPlugin

/** JcPlugin */
class JcPlugin : FlutterPlugin, JCApi {
    private lateinit var applicationContext: Context
    private lateinit var receiver: JcReceiver

    private val initialization = Initialization()
    private val userInfo = UserInfo()
    private val call = Call()

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        JCApi.setUp(binding.binaryMessenger, null)
    }

    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        applicationContext = flutterPluginBinding.applicationContext
        JCApi.setUp(flutterPluginBinding.binaryMessenger, this)
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "local-view",
            LocalViewFactory(),
        )
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "remote-view",
            RemoteViewFactory(),
        )
        receiver = JcReceiver(flutterPluginBinding.binaryMessenger)
    }


    override fun isInited() = initialization.isInited()

    override fun initialize() = initialization.initialize(applicationContext)

    override fun uninitialize() = initialization.uninitialize()

    override fun setAppKey(appKey: String) = initialization.setAppKey(appKey)

    override fun setDisplayName(displayName: String) = userInfo.setDisplayName(displayName)

    override fun setAccountNumber(accountNumber: String) = userInfo.setAccountNumber(accountNumber)

    override fun setTimeout(timeout: Long) = userInfo.setTimeout(timeout)

    override fun startCall(accountNumber: String, video: Boolean, ticket: String) =
        call.startCall(
            accountNumber = accountNumber,
            video = video,
            context = applicationContext,
            receiver = receiver,
            callTicket = ticket,
        )

    override fun startSelfVideo() = call.startSelfVideo(applicationContext, receiver)

    override fun stopSelfVideo() = call.stopSelfVideo(receiver)

    override fun startOtherVideo() = call.startOtherVideo(applicationContext)

    override fun setServerAddress(serverAddress: String) = userInfo.setServerAddress(serverAddress)

    override fun answerCall() = call.answerCall()

}
