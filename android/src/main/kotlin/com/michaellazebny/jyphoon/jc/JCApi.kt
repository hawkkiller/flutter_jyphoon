// Autogenerated from Pigeon (v4.2.14), do not edit directly.
// See also: https://pub.dev/packages/pigeon

package com.michaellazebny.jyphoon.jc

import android.util.Log
import io.flutter.plugin.common.BasicMessageChannel
import io.flutter.plugin.common.BinaryMessenger
import io.flutter.plugin.common.MessageCodec
import io.flutter.plugin.common.StandardMessageCodec
import java.io.ByteArrayOutputStream
import java.nio.ByteBuffer

/** Generated class from Pigeon. */

enum class CallType(val raw: Int) {
  ONETOONE(0),
  GROUP(1);

  companion object {
    fun ofRaw(raw: Int): CallType? {
      return values().firstOrNull { it.raw == raw }
    }
  }
}
/** Generated interface from Pigeon that represents a handler of messages from Flutter. */
interface JyphoonInitializationApi {
  /** Returns whether jyphoon sdk was inited. */
  fun isInited(): Boolean
  /**
   * Initializes the engine.
   *
   * It is needed to call [setAppKey] before.
   */
  fun initialize(): Boolean
  /** Sets appKey for the SDK. */
  fun setAppKey(appKey: String)
  /** Sets the name that is visible to another participant(s). */
  fun setDisplayName(displayName: String)
  /**
   * Sets account number. It acts like uuid. It launches login process.
   *
   * It is needed to call [setAppKey] before.
   */
  fun setAccountNumber(accountNumber: String): Boolean
  /** Sets the timeout for the call request. */
  fun setTimeout(timeout: Long)
  /** Set Jyphoon backend server address. */
  fun setServerAddress(serverAddress: String)
  /** Get current user id */
  fun getCurrentUserId(): String?

  companion object {
    /** The codec used by JyphoonInitializationApi. */
    val codec: MessageCodec<Any?> by lazy {
      StandardMessageCodec()
    }
    /** Sets up an instance of `JyphoonInitializationApi` to handle messages through the `binaryMessenger`. */
    @Suppress("UNCHECKED_CAST")
    fun setUp(binaryMessenger: BinaryMessenger, api: JyphoonInitializationApi?) {
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonInitializationApi.isInited", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.isInited())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonInitializationApi.initialize", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.initialize())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonInitializationApi.setAppKey", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val appKeyArg = args[0] as String
              api.setAppKey(appKeyArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonInitializationApi.setDisplayName", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val displayNameArg = args[0] as String
              api.setDisplayName(displayNameArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonInitializationApi.setAccountNumber", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val accountNumberArg = args[0] as String
              wrapped = listOf<Any?>(api.setAccountNumber(accountNumberArg))
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonInitializationApi.setTimeout", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val timeoutArg = args[0].let { if (it is Int) it.toLong() else it as Long }
              api.setTimeout(timeoutArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonInitializationApi.setServerAddress", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val serverAddressArg = args[0] as String
              api.setServerAddress(serverAddressArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonInitializationApi.getCurrentUserId", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.getCurrentUserId())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
    }
  }
}
/** Generated interface from Pigeon that represents a handler of messages from Flutter. */
interface JyphoonCallApi {
  /**
   * Starts the "call".
   * Returns true if the call was started successfully.
   *
   * [destination] - the identifier of the companion or the conference.
   *
   * [password] - the password for the conference.
   *
   * [video] - initiate call as videocall or audiocall.
   *
   * [type] - oneToOne or group.
   */
  fun call(destination: String, password: String, video: Boolean, type: CallType): Boolean
  /**
   * Returns CallStatus.
   * Returns the current call status.
   * It can be one of the following:
   * - CallStatus.on
   * - CallStatus.off
   * - CallStatus.waiting
   */
  fun callStatus(): String
  /**
   * True if the user is in the call and is not muted.
   * Otherwise, returns false.
   */
  fun audio(): Boolean
  /**
   * True if the user is in the call and shares video.
   * Otherwise, returns false.
   */
  fun video(): Boolean
  /**
   * True if the companion is in the call and is not muted.
   * Otherwise, returns false.
   */
  fun otherAudio(): Boolean
  /**
   * True if the companion is in the call and shares video.
   * Otherwise, returns false.
   */
  fun otherVideo(): Boolean
  /**
   * Hangs up the call or leaves the conference
   * depending on the call type.
   */
  fun leave(): Boolean
  /** Switches the camera (front/back) */
  fun switchCamera()
  /** Enables \ disables video. */
  fun setVideo(video: Boolean)
  /** Enables \ disables audio. */
  fun setAudio(audio: Boolean)
  /** Enables \ disables speaker. */
  fun setSpeaker(speaker: Boolean)

  companion object {
    /** The codec used by JyphoonCallApi. */
    val codec: MessageCodec<Any?> by lazy {
      StandardMessageCodec()
    }
    /** Sets up an instance of `JyphoonCallApi` to handle messages through the `binaryMessenger`. */
    @Suppress("UNCHECKED_CAST")
    fun setUp(binaryMessenger: BinaryMessenger, api: JyphoonCallApi?) {
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.call", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val destinationArg = args[0] as String
              val passwordArg = args[1] as String
              val videoArg = args[2] as Boolean
              val typeArg = CallType.ofRaw(args[3] as Int)!!
              wrapped = listOf<Any?>(api.call(destinationArg, passwordArg, videoArg, typeArg))
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.callStatus", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.callStatus())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.audio", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.audio())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.video", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.video())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.otherAudio", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.otherAudio())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.otherVideo", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.otherVideo())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.leave", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              wrapped = listOf<Any?>(api.leave())
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.switchCamera", codec)
        if (api != null) {
          channel.setMessageHandler { _, reply ->
            var wrapped = listOf<Any?>()
            try {
              api.switchCamera()
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.setVideo", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val videoArg = args[0] as Boolean
              api.setVideo(videoArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.setAudio", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val audioArg = args[0] as Boolean
              api.setAudio(audioArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonCallApi.setSpeaker", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val speakerArg = args[0] as Boolean
              api.setSpeaker(speakerArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
    }
  }
}
/** Generated class from Pigeon that represents Flutter messages that can be called from Kotlin. */
@Suppress("UNCHECKED_CAST")
class JyphoonReceiver(private val binaryMessenger: BinaryMessenger) {
  companion object {
    /** The codec used by JyphoonReceiver. */
    val codec: MessageCodec<Any?> by lazy {
      StandardMessageCodec()
    }
  }
  /** Called when the call status changes. */
  fun onEvent(eventArg: String, dataArg: Map<String?, Any?>, callback: () -> Unit) {
    val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.JyphoonReceiver.onEvent", codec)
    channel.send(listOf(eventArg, dataArg)) {
      callback()
    }
  }
}
/** Generated interface from Pigeon that represents a handler of messages from Flutter. */
interface CompanionViewApi {
  fun setCompanionFrame(width: Double, height: Double)

  companion object {
    /** The codec used by CompanionViewApi. */
    val codec: MessageCodec<Any?> by lazy {
      StandardMessageCodec()
    }
    /** Sets up an instance of `CompanionViewApi` to handle messages through the `binaryMessenger`. */
    @Suppress("UNCHECKED_CAST")
    fun setUp(binaryMessenger: BinaryMessenger, api: CompanionViewApi?) {
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.CompanionViewApi.setCompanionFrame", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val widthArg = args[0] as Double
              val heightArg = args[1] as Double
              api.setCompanionFrame(widthArg, heightArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
    }
  }
}
/** Generated interface from Pigeon that represents a handler of messages from Flutter. */
interface SelfViewApi {
  fun setSelfFrame(width: Double, height: Double)

  companion object {
    /** The codec used by SelfViewApi. */
    val codec: MessageCodec<Any?> by lazy {
      StandardMessageCodec()
    }
    /** Sets up an instance of `SelfViewApi` to handle messages through the `binaryMessenger`. */
    @Suppress("UNCHECKED_CAST")
    fun setUp(binaryMessenger: BinaryMessenger, api: SelfViewApi?) {
      run {
        val channel = BasicMessageChannel<Any?>(binaryMessenger, "dev.flutter.pigeon.SelfViewApi.setSelfFrame", codec)
        if (api != null) {
          channel.setMessageHandler { message, reply ->
            var wrapped = listOf<Any?>()
            try {
              val args = message as List<Any?>
              val widthArg = args[0] as Double
              val heightArg = args[1] as Double
              api.setSelfFrame(widthArg, heightArg)
              wrapped = listOf<Any?>(null)
            } catch (exception: Error) {
              wrapped = wrapError(exception)
            }
            reply.reply(wrapped)
          }
        } else {
          channel.setMessageHandler(null)
        }
      }
    }
  }
}

private fun wrapResult(result: Any?): List<Any?> {
  return listOf(result)
}

private fun wrapError(exception: Throwable): List<Any> {
  return listOf<Any>(
    exception.javaClass.simpleName,
    exception.toString(),
    "Cause: " + exception.cause + ", Stacktrace: " + Log.getStackTraceString(exception)
  )
}
