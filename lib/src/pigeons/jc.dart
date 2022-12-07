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
  bool startCall(String accountNumber, bool video);

  /// Returns [Void].
  /// Starts to send video.
  void startSelfVideo();

  /// Returns [Void].
  /// Stops to send video.
  void stopSelfVideo();

  /// Returns [Void].
  /// Gets the video from the other participant.
  void startOtherVideo();

  /// Returns [Void].
  /// Takes [String] account in. It is the account identifier of the person you want to call.
  void setServerAddress(String serverAddress);
}

@FlutterApi()
abstract class JcReceiver {
  void onCallStarted();

  void onVideoStarted();

  void onVideoStopped();

  void onCallEnded();
}
