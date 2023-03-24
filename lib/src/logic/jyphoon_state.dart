import 'dart:async';

import 'package:jc/generated/jyphoon_api.dart';
import 'package:jc/src/model/enum.dart';

abstract class JyphoonState {
  abstract final Stream<VideoStatus> selfVideo;
  abstract final Stream<AudioStatus> selfAudio;

  abstract final Stream<VideoStatus> companionVideo;
  abstract final Stream<AudioStatus> companionAudio;

  /// Reactive stream of the conference status.
  abstract final Stream<CallStatus> call;
}

abstract class InnerJyphoonState implements JyphoonState {
  Future<void> updateVideoStatus();
  Future<void> updateVoiceStatus();
  Future<void> updateConfStatus();
}

class InnerJyphoonStateImpl implements InnerJyphoonState {
  InnerJyphoonStateImpl() : _api = JyphoonApi();

  final _selfVideo = StreamController<VideoStatus>.broadcast();
  final _selfAudio = StreamController<AudioStatus>.broadcast();

  final _companionVideo = StreamController<VideoStatus>.broadcast();
  final _companionAudio = StreamController<AudioStatus>.broadcast();

  final _call = StreamController<CallStatus>();

  late final JyphoonApi _api;

  @override
  Stream<VideoStatus> get selfVideo => _selfVideo.stream.distinct();

  @override
  Stream<AudioStatus> get selfAudio => _selfAudio.stream.distinct();

  @override
  Stream<VideoStatus> get companionVideo => _companionVideo.stream.distinct();

  @override
  Stream<AudioStatus> get companionAudio => _companionAudio.stream.distinct();

  @override
  Stream<CallStatus> get call => _call.stream.distinct();

  @override
  Future<void> updateVideoStatus() => Future.wait([
        _api.video(),
        _api.otherVideo(),
      ]).then((l) {
        _selfVideo.add(VideoStatus.fromBool(value: l[0]));
        _companionVideo.add(VideoStatus.fromBool(value: l[1]));
      });

  @override
  Future<void> updateVoiceStatus() => Future.wait([
        _api.audio(),
        _api.otherAudio(),
      ]).then((l) {
        _selfAudio.add(AudioStatus.fromBool(value: l[0]));
        _companionAudio.add(AudioStatus.fromBool(value: l[1]));
      });

  @override
  Future<void> updateConfStatus() => _api.callStatus().then((value) {
        final conf = CallStatus.fromString(value);
        _call.add(conf);
      });
}
