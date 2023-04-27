package com.michaellazebny.jyphoon.jc

import android.content.Context
import com.michaellazebny.jyphoon.jc.api.*
import com.michaellazebny.jyphoon.jc.platformViews.CallViewFactory
import com.michaellazebny.jyphoon.jc.sdkEventsHandler.SdkEventsHandler
import com.michaellazebny.jyphoon.jc.utils.JCCallUtils
import io.flutter.embedding.engine.plugins.FlutterPlugin

interface JyphoonApi : JyphoonInitializationApi, JyphoonCallApi

/** JcPlugin */
class JcPlugin : FlutterPlugin, JyphoonApi {
    private lateinit var applicationContext: Context
    private lateinit var receiver: JyphoonReceiver
    private lateinit var initializationApi: InitializationApi
    private lateinit var oneToOneCallApi: OneToOneCallApi
    private lateinit var groupCallApi: GroupCallApi
    private val stub = StubCallApi()

    private lateinit var sdkEventsHandler: SdkEventsHandler

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        JyphoonInitializationApi.setUp(binding.binaryMessenger, null)
        JyphoonCallApi.setUp(binding.binaryMessenger, null)
        sdkEventsHandler.dispose()
    }

    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        applicationContext = flutterPluginBinding.applicationContext
        initializationApi = InitializationApi(applicationContext)
        oneToOneCallApi = OneToOneCallApi()
        groupCallApi = GroupCallApi()
        JyphoonCallApi.setUp(flutterPluginBinding.binaryMessenger, this)
        JyphoonInitializationApi.setUp(flutterPluginBinding.binaryMessenger, this)
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "self-view",
            CallViewFactory(
                flutterPluginBinding.binaryMessenger,
                ViewCanvasApi.SelfViewCanvasApi()
            ),
        )
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "companion-view",
            CallViewFactory(
                flutterPluginBinding.binaryMessenger,
                ViewCanvasApi.CompanionViewCanvasApi()
            ),
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

    override fun call(
        destination: String,
        password: String,
        video: Boolean,
        did: String,
        type: CallType,
        ts: Long
    ): Boolean {
        val callApi = when (type) {
            CallType.ONETOONE -> oneToOneCallApi
            CallType.GROUP -> groupCallApi
        }
        return callApi.call(destination, password, video, did, type, ts)

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

    override fun clientState() = initializationApi.clientState()

    private val callApi: JyphoonCallApi
        get() {
            return when (JCCallUtils.getCallType()) {
                CallType.ONETOONE -> oneToOneCallApi
                CallType.GROUP -> groupCallApi
                else -> stub
            }
        }
}

class StubCallApi : JyphoonCallApi {
    override fun call(
        destination: String,
        password: String,
        video: Boolean,
        did: String,
        type: CallType,
        ts: Long
    ) = false

    override fun setVideo(video: Boolean) {}

    override fun setAudio(audio: Boolean) {}

    override fun leave() = false

    override fun audio() = false

    override fun otherAudio() = false

    override fun video() = false

    override fun otherVideo() = false

    override fun callStatus() = "off"

    override fun switchCamera() {}

    override fun setSpeaker(speaker: Boolean) {}
}
