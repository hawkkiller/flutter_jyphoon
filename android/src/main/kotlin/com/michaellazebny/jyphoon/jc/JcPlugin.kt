package com.michaellazebny.jyphoon.jc

import android.content.Context
import com.michaellazebny.jyphoon.jc.api.GroupCall
import com.michaellazebny.jyphoon.jc.api.Initialization
import com.michaellazebny.jyphoon.jc.api.OneToOneCall
import com.michaellazebny.jyphoon.jc.jcWrapper.JCManager
import com.michaellazebny.jyphoon.jc.sdkEventsHandler.SdkEventsHandler

import com.michaellazebny.jyphoon.jc.platformViews.SelfViewFactory
import com.michaellazebny.jyphoon.jc.platformViews.CompanionViewFactory

import io.flutter.embedding.engine.plugins.FlutterPlugin

/** JcPlugin */
class JcPlugin : FlutterPlugin, JyphoonInitializationApi, JyphoonCallApi {
    private lateinit var applicationContext: Context
    private lateinit var receiver: JyphoonReceiver
    private lateinit var initializationApi: Initialization
    private lateinit var oneToOneCall: OneToOneCall
    private lateinit var groupCall: GroupCall

    private lateinit var sdkEventsHandler: SdkEventsHandler

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        JyphoonInitializationApi.setUp(binding.binaryMessenger, null)
        JyphoonCallApi.setUp(binding.binaryMessenger, null)
        sdkEventsHandler.dispose()
    }

    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        applicationContext = flutterPluginBinding.applicationContext
        initializationApi = Initialization(applicationContext)
        oneToOneCall = OneToOneCall()
        groupCall = GroupCall()
        JyphoonCallApi.setUp(flutterPluginBinding.binaryMessenger, this)
        JyphoonInitializationApi.setUp(flutterPluginBinding.binaryMessenger, this)
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

    override fun isInited() = initializationApi.isInited()

    override fun initialize() = initializationApi.initialize()

    override fun setAppKey(appKey: String) = initializationApi.setAppKey(appKey)

    override fun setDisplayName(displayName: String) = initializationApi.setDisplayName(displayName)

    override fun setAccountNumber(accountNumber: String) =
        initializationApi.setAccountNumber(accountNumber)

    override fun setTimeout(timeout: Long) = initializationApi.setTimeout(timeout)

    override fun getCurrentUserId() = initializationApi.getCurrentUserId()

    override fun setServerAddress(serverAddress: String) =
        initializationApi.setServerAddress(serverAddress)

    override fun call(destination: String, password: String, video: Boolean, type: CallType) : Boolean {
        val callApi = when (type) {
            CallType.ONETOONE -> oneToOneCall
            CallType.GROUP -> groupCall
        }
        return callApi.call(destination, password, video, type)

    }

    override fun setVideo(video: Boolean) = callApi.setVideo(video)

    override fun setAudio(audio: Boolean) = callApi.setAudio(audio)

    override fun leave() = callApi.leave()

    override fun audio() = callApi.audio()

    override fun otherAudio() = callApi.otherAudio()

    override fun video() = callApi.video()

    override fun otherVideo() = callApi.otherVideo()

    override fun callStatus() = callApi.callStatus()

    override fun switchCamera() = callApi.switchCamera()

    override fun setSpeaker(speaker: Boolean) = callApi.setSpeaker(speaker)

    // TODO: think about it, how to work with it when there is no call
    private fun getCallType(): CallType? {
        return if (JCManager.getInstance().call.callItems.isNotEmpty()) {
            CallType.ONETOONE
        } else if (JCManager.getInstance().mediaChannel.selfParticipant != null) {
            CallType.GROUP
        } else {
            null
        }
    }

    private val callApi: JyphoonCallApi
        get() {
            return when (getCallType()) {
                CallType.ONETOONE -> oneToOneCall
                CallType.GROUP -> groupCall
                else -> throw Exception("Call type is not set")
            }
        }
}
