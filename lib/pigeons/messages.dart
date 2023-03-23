import 'package:pigeon/pigeon.dart';

@ConfigurePigeon(
  PigeonOptions(
    dartOut: 'lib/src/generated/jyphoon_api.dart',
    kotlinOut: 'android/src/main/kotlin/com/michaellazebny/jyphoon/jc/JCApi.kt',
    kotlinOptions: KotlinOptions(package: 'com.michaellazebny.jyphoon.jc'),
    swiftOptions: SwiftOptions(),
    swiftOut: 'ios/Classes/JCApi.swift',
  ),
)
@HostApi()
abstract class JyphoonApi {
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

  /// Returns [Boolean].
  /// Takes [String] confId in. It is the conference identifier.
  /// Takes [String] password in. It is the password for the conference.
  /// Starts the "call".
  bool confJoin(
    String confId,
    String password,
    bool video,
    bool asr,
  );

  /// Returns [Void].
  /// Takes [String] account in. It is the account identifier of the person you want to call.
  void setServerAddress(String serverAddress);

  /// Returns [Void].
  /// Starts or stops to send video
  void setVideo(bool video);

  /// Returns [Void].
  /// Starts or stops to send audio.
  void setAudio(bool audio);

  /// Returns [Void].
  ///
  /// Configures the speaker mode.
  void setSpeaker(bool speaker);

  /// Returns [Boolean].
  /// True if the user is in the call and is not muted.
  /// Otherwise, returns false.
  bool audio();

  /// Returns [Boolean].
  /// True if the companion is in the call and is not muted.
  /// Otherwise, returns false.
  bool otherAudio();

  /// Returns [Boolean].
  /// True if the user is in the call and shares video.
  /// Otherwise, returns false.
  bool video();

  /// Returns [String].
  /// Get current user id
  String? getCurrentUserId();

  /// Returns [Void].
  /// Hangs up the "call".
  bool confLeave();

  /// Returns [Boolean].
  /// True if the companion is in the call and shares video.
  /// Otherwise, returns false.
  bool otherVideo();

  /// Returns [ConferenceStatus].
  /// Returns the current conference status.
  /// It can be one of the following:
  /// - [ConferenceStatus.on]
  /// - [ConferenceStatus.off]
  /// - [ConferenceStatus.waiting]
  String confStatus();

  /// Returns [Void].
  /// Switches the camera.
  void switchCamera();
}

@FlutterApi()
abstract class JyphoonReceiver {
  @async
  void onEvent(String event);
}

@HostApi()
abstract class CompanionViewApi {
  void setCompanionFrame(double width, double height);
}

@HostApi()
abstract class SelfViewApi {
  void setSelfFrame(double width, double height);
}
