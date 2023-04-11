import 'package:pigeon/pigeon.dart';

@ConfigurePigeon(
  PigeonOptions(
    dartOut: 'lib/generated/jyphoon_api.dart',
    kotlinOut: 'android/src/main/kotlin/com/michaellazebny/jyphoon/jc/JCApi.kt',
    kotlinOptions: KotlinOptions(package: 'com.michaellazebny.jyphoon.jc'),
    swiftOptions: SwiftOptions(),
    swiftOut: 'ios/Classes/JCApi.swift',
  ),
)
@HostApi()
abstract class JyphoonApi {
  /// Returns whether JC was inited.
  bool isInited();

  /// Initializes the engine. It is needed to set appKey before. Otherwise, it will fail.
  bool initialize();

  /// Sets appKey in order to have access to the Jyphoon API.
  void setAppKey(String appKey);

  /// Sets the name that is visible to another participant(s).
  void setDisplayName(String displayName);

  /// Sets account number. It acts like uuid. It launches login process.
  /// It is needed to set appKey before. Otherwise, it will fail.
  bool setAccountNumber(String accountNumber);

  /// Sets the timeout for the call request.
  void setTimeout(int timeout);

  /// Starts the "call".
  bool call(
    String confId,
    String password,
    bool video,
    bool asr,
  );

  /// Set Jyphoon backend server address.
  void setServerAddress(String serverAddress);

  /// Starts or stops to send video
  void setVideo(bool video);

  /// Starts or stops to send audio.
  void setAudio(bool audio);

  /// Configures the speaker mode.
  void setSpeaker(bool speaker);

  /// True if the user is in the call and is not muted.
  /// Otherwise, returns false.
  bool audio();

  /// True if the companion is in the call and is not muted.
  /// Otherwise, returns false.
  bool otherAudio();

  /// True if the user is in the call and shares video.
  /// Otherwise, returns false.
  bool video();

  /// Get current user id
  String? getCurrentUserId();

  /// Hangs up the "call".
  bool leave();

  /// True if the companion is in the call and shares video.
  /// Otherwise, returns false.
  bool otherVideo();

  /// Returns CallStatus.
  /// Returns the current call status.
  /// It can be one of the following:
  /// - CallStatus.on
  /// - CallStatus.off
  /// - CallStatus.waiting
  String callStatus();

  /// Switches the camera (front/back)
  void switchCamera();

  /// Returns the current state of the client.
  int clientState();
}

@FlutterApi()
abstract class JyphoonReceiver {
  /// Called when the call status changes.
  void onEvent(String event, Map<String?, Object?> data);
}

@HostApi()
abstract class CompanionViewApi {
  void setCompanionFrame(double width, double height);
}

@HostApi()
abstract class SelfViewApi {
  void setSelfFrame(double width, double height);
}
