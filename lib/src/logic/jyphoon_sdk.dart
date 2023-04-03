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
    String destination, {
    CallType type = CallType.group,
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
    _callApi = JyphoonCallApi();
    _initializationApi = JyphoonInitializationApi();
    _controller = JyphoonControllerImpl();
    state = _controller.state;
  }

  late final JyphoonCallApi _callApi;
  late final JyphoonInitializationApi _initializationApi;
  late final JyphoonController _controller;

  @override
  late final JyphoonState state;

  @override
  Future<bool> call(
    String destination, {
    String password = '',
    bool video = false,
    CallType type = CallType.group,
  }) =>
      _callApi.call(destination, password, video, type);

  @override
  Future<bool> leave() => _callApi.leave();

  @override
  Future<CallStatus> callStatus() =>
      _callApi.callStatus().then(CallStatus.fromString);

  @override
  Future<String?> getCurrentUserId() => _initializationApi.getCurrentUserId();

  @override
  Future<bool> initialize() => _initializationApi.initialize();

  @override
  Future<bool> isInited() => _initializationApi.isInited();

  @override
  Future<bool> otherAudio() => _callApi.otherAudio();

  @override
  Future<bool> otherVideo() => _callApi.otherVideo();

  @override
  Future<bool> setAccountNumber(
    String accountNumber,
  ) =>
      _initializationApi.setAccountNumber(accountNumber);

  @override
  Future<void> setAppKey(
    String appkey,
  ) =>
      _initializationApi.setAppKey(appkey);

  @override
  Future<void> setDisplayName(
    String displayName,
  ) =>
      _initializationApi.setDisplayName(displayName);

  @override
  Future<void> setServerAddress(
    String serverAddress,
  ) =>
      _initializationApi.setServerAddress(serverAddress);

  @override
  Future<void> setTimeout(
    int timeout,
  ) =>
      _initializationApi.setTimeout(timeout);

  @override
  Future<void> switchCamera() => _callApi.switchCamera();

  @override
  Future<bool> video() => _callApi.video();

  @override
  Future<bool> audio() => _callApi.audio();

  @override
  Future<void> setAudio({
    required bool audio,
  }) =>
      _callApi.setAudio(audio);

  @override
  Future<void> setVideo({
    required bool video,
  }) =>
      _callApi.setVideo(video);

  @override
  Future<void> setSpeaker({
    required bool speaker,
  }) =>
      _callApi.setSpeaker(speaker);
}
