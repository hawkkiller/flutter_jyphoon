import 'dart:developer';

import 'package:jc/src/generated/jyphoon_api.dart';
import 'package:jc/src/model/enum.dart';
import 'package:rxdart/subjects.dart';

abstract class JyphoonState {
  abstract final Stream<VideoStatus> selfVideo;
  abstract final Stream<AudioStatus> selfAudio;

  abstract final Stream<VideoStatus> companionVideo;
  abstract final Stream<AudioStatus> companionAudio;

  /// Reactive stream of the conference status.
  abstract final Stream<ConferenceStatus> conference;
}

abstract class InnerJyphoonState implements JyphoonState {
  Future<void> updateVideoStatus();
  Future<void> updateVoiceStatus();
  Future<void> updateConfStatus();
}

class InnerJyphoonStateImpl implements InnerJyphoonState {
  InnerJyphoonStateImpl() : _api = JyphoonApi();

  final _selfVideo = BehaviorSubject<VideoStatus>();
  final _selfAudio = BehaviorSubject<AudioStatus>();

  final _companionVideo = BehaviorSubject<VideoStatus>();
  final _companionAudio = BehaviorSubject<AudioStatus>();

  final _conference = BehaviorSubject<ConferenceStatus>();

  late final JyphoonApi _api;

  @override
  Stream<VideoStatus> get selfVideo => _selfVideo.distinct();

  @override
  Stream<AudioStatus> get selfAudio => _selfAudio.distinct();

  @override
  Stream<VideoStatus> get companionVideo => _companionVideo.distinct();

  @override
  Stream<AudioStatus> get companionAudio => _companionAudio.distinct();

  @override
  Stream<ConferenceStatus> get conference => _conference.distinct();

  @override
  Future<void> updateVideoStatus() {
    return Future.wait([
      _api.video(),
      _api.otherVideo(),
    ]).then((l) {
      _selfVideo.add(VideoStatus.fromBool(l[0]));
      _companionVideo.add(VideoStatus.fromBool(l[1]));
    });
  }

  @override
  Future<void> updateVoiceStatus() {
    return Future.wait([
      _api.audio(),
      _api.otherAudio(),
    ]).then((l) {
      inspect(l);
      _selfAudio.add(AudioStatus.fromBool(l[0]));
      _companionAudio.add(AudioStatus.fromBool(l[1]));
    });
  }

  @override
  Future<void> updateConfStatus() {
    return _api.confStatus().then((value) {
      final conf = ConferenceStatus.fromString(value);
      _conference.add(conf);
    });
  }
}
