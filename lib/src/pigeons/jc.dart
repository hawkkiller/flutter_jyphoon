import 'package:pigeon/pigeon.dart';

@ConfigurePigeon(
  PigeonOptions(
    dartOut: 'lib/src/jc.dart',
    kotlinOut: 'android/src/main/kotlin/com/michaellazebny/jyphoon/jc/JCApi.kt',
    kotlinOptions: KotlinOptions(package: 'com.michaellazebny.jyphoon.jc'),
  ),
)
@HostApi()
abstract class JCApi {
  /// Returns whether JC was inited.
  ///
  /// On **Android**:
  /// Returns **true** if JCManager.initialize() was successfully called.
  /// Otherwise, returns **false** if initialize() was not called or failed.
  bool isInited();

  /// Returns bool.
  ///
  /// Initializes the engine. It is needed to set appKey before. Otherwise, it will fail.
  bool initialize();

  /// Returns [Void]
  /// Deinitialize the engine. After call this method you can't use call mechanics
  void uninitialize();

  /// Sets appKey in order to have access to the Jyphoon API.
  void setAppKey(String appKey);

  /// Returns [Void].
  ///
  /// Takes [String] displayName in.
  ///
  /// Sets the name that is visible to another participant(s).
  void setDisplayName(String displayName);

  /// Returns [bool].
  /// Sets account number. It is needed to set appKey before. Otherwise, it will fail.
  bool setAccountNumber(String accountNumber);

  /// Returns [Void].
  ///
  /// Takes [Int] timeout in.
  ///
  /// Sets the timeout for the call request.
  void setTimeout(int timeout);

  /// Returns [Void].
  /// Takes [String] account in. It is the account identifier of the person you want to call.
  /// Takes [bool] video in. It is the type of call you want to make. If true, it will be a video call.
  ///
  /// Makes a call to the specified account.
  /// If [JCCall.call] returns true then the call started.
  bool startCall(String accountNumber, bool video, String ticket);

  /// Returns [Void].
  /// Starts or stops to send video.
  void setSelfVideoCondition(bool condition);

  /// Returns [Void].
  void setOtherVideoCondition(bool condition);

  /// Returns [Void].
  void setSelfVoiceCondition(bool condition);

  /// Returns [Void].
  void setOtherVoiceCondition(bool condition);

  /// Returns [Void].
  /// Takes [String] account in. It is the account identifier of the person you want to call.
  void setServerAddress(String serverAddress);

  /// Returns [Void].
  /// Answers call
  void answerCall();

  /// Returns [String].
  /// Get current user id
  String? getCurrentUserId();
}

@FlutterApi()
abstract class JcReceiver {
  void onCallStarted();

  void onSelfVideoChange(bool condition);

  void onCompanionVideoChange(bool condition);

  void onSelfVoiceChange(bool condition);

  void onCompanionVoiceChange(bool condition);

  void onCallEnded();
}
