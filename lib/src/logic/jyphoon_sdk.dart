import 'dart:async';

import 'package:jc/generated/jyphoon_api.dart';
import 'package:jc/src/logic/jyphoon_controller.dart';
import 'package:jc/src/logic/jyphoon_state.dart';
import 'package:jc/src/model/enum.dart';

abstract class JyphoonSDK {
  factory JyphoonSDK() => _instance;

  static final JyphoonSDK _instance = JyphoonSDKImpl._();

  JyphoonState get state;

  Future<bool> initialize();

  Future<bool> isInited();

  Future<bool> call(
    String confId, {
    required bool asr,
    String password = '',
    bool video = false,
  });

  Future<bool> leave();

  Future<CallStatus> callStatus();

  Future<String?> getCurrentUserId();

  Future<bool> otherAudio();

  Future<bool> otherVideo();

  Future<bool> audio();

  Future<bool> video();

  Future<void> setAudio({required bool audio});

  Future<void> setVideo({required bool video});

  Future<void> setSpeaker({required bool speaker});

  Future<bool> setAccountNumber(String accountNumber);

  Future<void> setServerAddress(String serverAddress);

  Future<void> setAppKey(String appkey);

  Future<void> setDisplayName(String displayName);

  Future<void> setTimeout(int timeout);

  Future<void> switchCamera();
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
  Future<bool> call(
    String confId, {
    required bool asr,
    String password = '',
    bool video = false,
  }) =>
      _api.call(confId, password, video, asr);

  @override
  Future<bool> leave() => _api.leave();

  @override
  Future<CallStatus> callStatus() =>
      _api.callStatus().then(CallStatus.fromString);

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
  Future<void> setAudio({required bool audio}) => _api.setAudio(audio);

  @override
  Future<void> setVideo({required bool video}) => _api.setVideo(video);

  @override
  Future<void> setSpeaker({required bool speaker}) => _api.setSpeaker(speaker);
}
