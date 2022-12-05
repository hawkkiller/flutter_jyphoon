package com.michaellazebny.jyphoon.jc

import android.content.Context
import androidx.annotation.NonNull

import com.michaellazebny.jyphoon.jc.methods.Call
import com.michaellazebny.jyphoon.jc.methods.Initialization
import com.michaellazebny.jyphoon.jc.methods.UserInfo
import com.michaellazebny.jyphoon.jc.views.LocalViewFactory
import com.michaellazebny.jyphoon.jc.views.RemoteViewFactory

import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result

/** JcPlugin */
class JcPlugin : FlutterPlugin, MethodCallHandler {
    private lateinit var channel: MethodChannel
    private lateinit var applicationContext: Context

    private val initialization = Initialization()

    private val userInfo = UserInfo()

    private val call = Call()


    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        val channelName = "jc"
        channel = MethodChannel(flutterPluginBinding.binaryMessenger, channelName)
        applicationContext = flutterPluginBinding.applicationContext
        channel.setMethodCallHandler(this)
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "local-view",
            LocalViewFactory(),
        )
        flutterPluginBinding.platformViewRegistry.registerViewFactory(
            "remote-view",
            RemoteViewFactory(),
        )
    }


    override fun onMethodCall(call: MethodCall, result: Result) {
        when (call.method) {
            "isInited" -> {
                initialization.isInited(result)
            }
            "initialize" -> {
                initialization.initialize(applicationContext, result)
            }
            "setAppKey" -> {
                initialization.setAppKey(call, result)
            }
            "setDisplayName" -> {
                userInfo.setDisplayName(call, result)
            }
            "setAccountNumber" -> {
                userInfo.setAccountNumber(call, result)
            }
            "setTimeout" -> {
                userInfo.setTimeout(call, result)
            }
            "uninitialize" -> {
                initialization.uninitialize(result)
            }
            "startCall" -> {
                this.call.startCall(call, result, applicationContext)
            }
            "setRequestUrl" -> {
                userInfo.setRequestUrl(call, result)
            }
            else -> {
                result.notImplemented()
            }
        }

    }

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        channel.setMethodCallHandler(null)
    }
}
