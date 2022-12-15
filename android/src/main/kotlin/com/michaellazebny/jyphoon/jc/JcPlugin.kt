package com.michaellazebny.jyphoon.jc

import android.content.Context
import android.util.Log
import com.michaellazebny.jyphoon.jc.JCWrapper.JCCallUtils
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCEvent
import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager

import com.michaellazebny.jyphoon.jc.methods.Call
import com.michaellazebny.jyphoon.jc.methods.Initialization
import com.michaellazebny.jyphoon.jc.methods.UserInfo
import com.michaellazebny.jyphoon.jc.views.LocalViewFactory
import com.michaellazebny.jyphoon.jc.views.RemoteViewFactory

import io.flutter.embedding.engine.plugins.FlutterPlugin
import org.greenrobot.eventbus.EventBus
import org.greenrobot.eventbus.Subscribe

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
        EventBus.getDefault().register(this)
    }

    @Subscribe
    fun onEvent(event: JCEvent) {
        Log.d("JcPlugin", "onEvent: ${event.eventType}")
        val activeCallItem = JCCallUtils.getActiveCall()
        if (activeCallItem != null) {
            print("activeCallItem: $activeCallItem")
        }
    }

    override fun isInited() = initialization.isInited()

    override fun initialize() = initialization.initialize(applicationContext)

    override fun uninitialize() = initialization.uninitialize()

    override fun setAppKey(appKey: String) = initialization.setAppKey(appKey)

    override fun setDisplayName(displayName: String) = userInfo.setDisplayName(displayName)

    override fun setAccountNumber(accountNumber: String) = userInfo.setAccountNumber(accountNumber)

    override fun setTimeout(timeout: Long) = userInfo.setTimeout(timeout)

    override fun startCall(accountNumber: String, video: Boolean, ticket: String) = call.startCall(
        accountNumber = accountNumber,
        video = video,
        context = applicationContext,
        receiver = receiver,
        callTicket = ticket,
    )

    override fun setSelfVideoCondition(condition: Boolean) =
        call.setSelfVideoCondition(applicationContext, condition)

    override fun setOtherVideoCondition(condition: Boolean) =
        call.setOtherVideoCondition(condition, applicationContext)

    override fun setSelfVoiceCondition(condition: Boolean) = call.setSelfVoiceCondition(condition)

    override fun setOtherVoiceCondition(condition: Boolean) = call.setOtherVoiceCondition(condition)

    override fun setServerAddress(serverAddress: String) = userInfo.setServerAddress(serverAddress)

    override fun answerCall() = call.answerCall()

    override fun confJoin(confId: String, password: String) =
        call.confJoin(confId, password, applicationContext)

    override fun getCurrentUserId() = userInfo.getUserId()
}
