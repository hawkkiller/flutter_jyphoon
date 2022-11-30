import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'jc.dart';

abstract class JcPlatform extends PlatformInterface {
  /// Constructs a JcPlatform.
  JcPlatform() : super(token: _token);

  static final Object _token = Object();

  static JcPlatform _instance = JC();

  /// The default instance of [JcPlatform] to use.
  ///
  /// Defaults to [JC].
  static JcPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [JcPlatform] when
  /// they register themselves.
  static set instance(JcPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<bool> initialize() {
    throw UnimplementedError('initialize() has not been implemented.');
  }

  Future<void> uninitialize() {
    throw UnimplementedError('uninstall() has not been implemented.');
  }

  Future<bool> isInited() {
    throw UnimplementedError('isInitialized() has not been implemented.');
  }

  Future<String> getNowLogs() {
    throw UnimplementedError('getNowLogs() has not been implemented.');
  }

  Future<void> addLog(String log) {
    throw UnimplementedError('addLog() has not been implemented.');
  }

  Future<void> onLogin(bool result, /*@JCClient.ClientReason*/ int reason) {
    throw UnimplementedError('onLogin() has not been implemented.');
  }

  Future<void> onLogout(/*@JCClient.ClientReason*/ int reason) {
    throw UnimplementedError('onLogout() has not been implemented.');
  }

  Future<void> onClientStateChange(
    /*@@JCClient.ClientState*/ int state,
    /*@@JCClient.ClientState*/ int oldState,
  ) {
    throw UnimplementedError('onClientStateChange() has not been implemented.');
  }

  Future<void> onOnlineMessageSendResult(int operationId, bool result) {
    throw UnimplementedError(
        'onOnlineMessageSendResult() has not been implemented.');
  }

  Future<void> onOnlineMessageReceive(String userId, String content) {
    throw UnimplementedError(
        'onOnlineMessageReceive() has not been implemented.');
  }

  Future<void> onCallItemAdd(/*JCCallItem*/ item) {
    throw UnimplementedError('onCallItemAdd() has not been implemented.');
  }

  Future<void> onCallItemRemove(
    /*JCCallItem*/ item,
    /*@JCCall.CallReason*/ int reason,
    String description,
  ) {
    throw UnimplementedError('onCallItemRemove() has not been implemented.');
  }

  Future<void> onCallItemUpdate(
      /*JCCallItem*/ item, /*JCCallItem.ChangeParam*/ changeParam) {
    throw UnimplementedError('onCallItemUpdate() has not been implemented.');
  }

  Future<void> onMessageReceive(
      String type, String content, /*JCCallItem*/ callItem) {
    throw UnimplementedError('onMessageReceive() has not been implemented.');
  }

  Future<void> onMissedCallItem(/*JCCallItem*/ jcCallItem) {
    throw UnimplementedError('onMissedCallItem() has not been implemented.');
  }

  Future<void> onDtmfReceived(
      /*JCCallItem*/ jcCallItem, /*@JCCall.DtmfValue*/ int value) {
    throw UnimplementedError('onDtmfReceived() has not been implemented.');
  }

  Future<void> onMediaChannelStateChange(
      /*@JCMediaChannel.MediaChannelState*/ int state,
      /*@JCMediaChannel.MediaChannelState*/ int oldState) {
    throw UnimplementedError(
        'onMediaChannelStateChange() has not been implemented.');
  }

  Future<void> onMediaChannelPropertyChange(
      /*JCMediaChannel.PropChangeParam*/ propChangeParam) {
    throw UnimplementedError(
        'onMediaChannelPropertyChange() has not been implemented.');
  }

  Future<void> onJoin(bool result,
      /*@JCMediaChannel.MediaChannelReason*/ int reason, String channelId) {
    throw UnimplementedError('onJoin() has not been implemented.');
  }

  Future<void> onLeave(
      /*@JCMediaChannel.MediaChannelReason*/ int reason, String channelId) {
    throw UnimplementedError('onLeave() has not been implemented.');
  }

  Future<void> onStop(
      bool result, /*@JCMediaChannel.MediaChannelReason*/ int reason) {
    throw UnimplementedError('onStop() has not been implemented.');
  }

  Future<void> onQuery(
      int operationId,
      bool result,
      /*@JCMediaChannel.MediaChannelReason*/ int reason,
      /*JCMediaChannelQueryInfo */ queryInfo) {
    throw UnimplementedError('onQuery() has not been implemented.');
  }

  Future<void> onParticipantJoin(/*JCMediaChannelParticipant*/ participant) {
    throw UnimplementedError('onParticipantJoin() has not been implemented.');
  }

  Future<void> onParticipantLeft(/*JCMediaChannelParticipant*/ participant) {
    throw UnimplementedError('onParticipantLeft() has not been implemented.');
  }

  Future<void> onParticipantUpdate(/*JCMediaChannelParticipant*/ participant,
      /*JCMediaChannelParticipant.ChangeParam*/ changeParam) {
    throw UnimplementedError('onParticipantUpdate() has not been implemented.');
  }

  // TODO: imolement
  //  Future<void> onMessageReceive(String type, String content, String fromUserId) {
  //   throw UnimplementedError('onMessageReceive() has not been implemented.');
  //  }

  Future<void> onInviteSipUserResult(int operationId, bool result, int reason) {
    throw UnimplementedError(
        'onInviteSipUserResult() has not been implemented.');
  }

  Future<void> onParticipantVolumeChange(
      /*JCMediaChannelParticipant*/ jcMediaChannelParticipant) {
    throw UnimplementedError(
        'onParticipantVolumeChange() has not been implemented.');
  }

  Future<void> onCameraUpdate() {
    throw UnimplementedError('onCameraUpdate() has not been implemented.');
  }

  Future<void> onAudioOutputTypeChange(int audioRouteType) {
    throw UnimplementedError(
        'onAudioOutputTypeChange() has not been implemented.');
  }

  Future<void> onRenderReceived(
      /*JCMediaDeviceVideoCanvas */ jcMediaDeviceVideoCanvas) {
    throw UnimplementedError('onRenderReceived() has not been implemented.');
  }

  Future<void> onRenderStart(
      /*JCMediaDeviceVideoCanvas*/ jcMediaDeviceVideoCanvas) {
    throw UnimplementedError('onRenderStart() has not been implemented.');
  }

  Future<void> onVideoError(
      /*JCMediaDeviceVideoCanvas*/ jcMediaDeviceVideoCanvas) {
    throw UnimplementedError('onVideoError() has not been implemented.');
  }

  Future<void> onMessageSendUpdate(
      /*JCMessageChannelItem*/ jcMessageChannelItem) {
    throw UnimplementedError('onMessageSendUpdate() has not been implemented.');
  }

  Future<void> onMessageRecv(/*JCMessageChannelItem*/ jcMessageChannelItem) {
    throw UnimplementedError('onMessageRecv() has not been implemented.');
  }

  Future<void> onFileUpdate(/*JCStorageItem*/ jcStorageItem) {
    throw UnimplementedError('onFileUpdate() has not been implemented.');
  }

  Future<void> onFileResult(/*JCStorageItem*/ jcStorageItem) {
    throw UnimplementedError('onFileResult() has not been implemented.');
  }

  Future<void> onQueryUserStatusResult(
      int i, bool result, /*List<JCAccountItem>*/ list) {
    throw UnimplementedError(
        'onQueryUserStatusResult() has not been implemented.');
  }

  Future<void> onNetChange(int newNetType, int oldNetType) {
    throw UnimplementedError('onNetChange() has not been implemented.');
  }
}
