import 'package:pigeon/pigeon.dart';

enum CallType {
  oneToOne,
  group,
}

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
abstract class JyphoonInitializationApi {
  /// Returns whether jyphoon sdk was inited.
  bool isInited();

  /// Initializes the engine.
  ///
  /// It is needed to call [setAppKey] before.
  bool initialize();

  /// Sets appKey for the SDK.
  void setAppKey(String appKey);

  /// Sets the name that is visible to another participant(s).
  void setDisplayName(String displayName);

  /// Sets account number. It acts like uuid. It launches login process.
  ///
  /// It is needed to call [setAppKey] before.
  bool setAccountNumber(String accountNumber);

  /// Sets the timeout for the call request.
  void setTimeout(int timeout);

  /// Set Jyphoon backend server address.
  void setServerAddress(String serverAddress);

  /// Get current user id
  String? getCurrentUserId();

  int clientState();
}

@HostApi()
abstract class JyphoonCallApi {
  /// Starts the "call".
  /// Returns true if the call was started successfully.
  ///
  /// [destination] - the identifier of the companion or the conference.
  ///
  /// [password] - the password for the conference.
  ///
  /// [video] - initiate call as videocall or audiocall.
  ///
  /// [type] - oneToOne or group.
  bool call(
    String destination,
    String password,
    bool video,
    CallType type,
  );

  /// Returns CallStatus.
  /// Returns the current call status.
  /// It can be one of the following:
  /// - CallStatus.on
  /// - CallStatus.off
  /// - CallStatus.waiting
  String callStatus();

  /// True if the user is in the call and is not muted.
  /// Otherwise, returns false.
  bool audio();

  /// True if the user is in the call and shares video.
  /// Otherwise, returns false.
  bool video();

  /// True if the companion is in the call and is not muted.
  /// Otherwise, returns false.
  bool otherAudio();

  /// True if the companion is in the call and shares video.
  /// Otherwise, returns false.
  bool otherVideo();

  /// Hangs up the call or leaves the conference
  /// depending on the call type.
  bool leave();

  /// Switches the camera (front/back)
  void switchCamera();

  /// Enables \ disables video.
  void setVideo(bool video);

  /// Enables \ disables audio.
  void setAudio(bool audio);

  /// Enables \ disables speaker.
  void setSpeaker(bool speaker);
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
