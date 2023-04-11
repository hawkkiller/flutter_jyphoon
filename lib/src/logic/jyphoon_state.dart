import 'dart:async';

import 'package:jc/src/model/call_state.dart';
import 'package:jc/src/model/enum.dart';

abstract class JyphoonState {
  abstract final Stream<VideoStatus> selfVideo;
  abstract final Stream<AudioStatus> selfAudio;

  abstract final Stream<VideoStatus> companionVideo;
  abstract final Stream<AudioStatus> companionAudio;

  /// Reactive stream of the conference status.
  abstract final Stream<CallStatus> call;

  abstract final Stream<ClientState> clientState;
}

abstract class InnerJyphoonState implements JyphoonState {
  void updateState(CallState state);
}

class InnerJyphoonStateImpl implements InnerJyphoonState {
  InnerJyphoonStateImpl() {
    _selfVideo.add(VideoStatus.off);
    _selfAudio.add(AudioStatus.off);
    _companionVideo.add(VideoStatus.off);
    _companionAudio.add(AudioStatus.off);
    _call.add(CallStatus.off);
    _clientState.add(ClientState.notInit);
  }

  final _selfVideo = StreamController<VideoStatus>.broadcast();
  final _selfAudio = StreamController<AudioStatus>.broadcast();

  final _companionVideo = StreamController<VideoStatus>.broadcast();
  final _companionAudio = StreamController<AudioStatus>.broadcast();

  final _call = StreamController<CallStatus>();

  final _clientState = StreamController<ClientState>();

  @override
  late final clientState = _clientState.stream.asBroadcastStream();

  @override
  late final selfVideo = _selfVideo.stream.distinct().asBroadcastStream();

  @override
  late final selfAudio = _selfAudio.stream.distinct().asBroadcastStream();

  @override
  late final companionVideo =
      _companionVideo.stream.distinct().asBroadcastStream();

  @override
  late final companionAudio =
      _companionAudio.stream.distinct().asBroadcastStream();

  @override
  late final call = _call.stream.distinct().asBroadcastStream();

  @override
  void updateState(CallState state) {
    _selfVideo.add(state.video);
    _selfAudio.add(state.audio);
    _companionVideo.add(state.otherVideo);
    _companionAudio.add(state.otherAudio);
    _call.add(state.callStatus);
    _clientState.add(state.clientState);
  }
}
