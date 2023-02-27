import 'package:jc/src/generated/jyphoon_api.dart';
import 'package:jc/src/logic/jyphoon_controller.dart';
import 'package:jc/src/logic/jyphoon_state.dart';

abstract class JyphoonSDK implements JyphoonApi {
  JyphoonState get state;

  static final JyphoonSDK _instance = JyphoonSDKImpl._();

  factory JyphoonSDK() => _instance;
}

class JyphoonSDKImpl implements JyphoonSDK {
  JyphoonSDKImpl._() {
    _api = JyphoonApi();
    _controller = JyphoonControllerImpl();
    state = _controller.state;
  }

  late final JyphoonApi _api;
  late final JyphoonController _controller;

  @override
  late final JyphoonState state;

  @override
  Future<bool> confJoin(
    String argConfid,
    String argPassword,
    bool video,
  ) =>
      _api.confJoin(argConfid, argPassword, video);

  @override
  Future<bool> confLeave() => _api.confLeave();

  @override
  Future<String> confStatus() => _api.confStatus();

  @override
  Future<String?> getCurrentUserId() => _api.getCurrentUserId();

  @override
  Future<bool> initialize() => _api.initialize();

  @override
  Future<bool> isInited() => _api.isInited();

  @override
  Future<bool> otherAudio() => _api.otherAudio();

  @override
  Future<bool> otherVideo() => _api.otherVideo();

  @override
  Future<bool> setAccountNumber(String accountNumber) =>
      _api.setAccountNumber(accountNumber);

  @override
  Future<void> setAppKey(String appkey) => _api.setAppKey(appkey);

  @override
  Future<void> setDisplayName(String displayName) =>
      _api.setDisplayName(displayName);

  @override
  Future<void> setServerAddress(String serverAddress) =>
      _api.setServerAddress(serverAddress);

  @override
  Future<void> setTimeout(int timeout) => _api.setTimeout(timeout);

  @override
  Future<void> switchCamera() => _api.switchCamera();

  @override
  Future<bool> video() => _api.video();

  @override
  Future<bool> audio() => _api.audio();

  @override
  Future<void> setAudio(bool audio) => _api.setAudio(audio);

  @override
  Future<void> setVideo(bool video) => _api.setVideo(video);

  @override
  Future<void> setSpeaker(bool speaker) => _api.setSpeaker(speaker);
}
