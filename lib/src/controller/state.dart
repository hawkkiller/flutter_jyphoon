import 'package:jc/jc.dart';
import 'package:rxdart/subjects.dart';

abstract class JCState {
  abstract final Stream<VideoStatus> selfVideo;
  abstract final Stream<AudioStatus> selfAudio;

  abstract final Stream<VideoStatus> companionVideo;
  abstract final Stream<AudioStatus> companionAudio;

  /// Reactive stream of the conference status.
  abstract final Stream<ConferenceStatus> conference;

  void updateVideoStatus();

  void updateVoiceStatus();

  void updateConfStatus();
}

class JCStateImpl implements JCState {
  JCStateImpl() : _api = JCApi();

  final _selfVideo = BehaviorSubject<VideoStatus>();
  final _selfAudio = BehaviorSubject<AudioStatus>();

  final _companionVideo = BehaviorSubject<VideoStatus>();
  final _companionAudio = BehaviorSubject<AudioStatus>();

  final _conference = BehaviorSubject<ConferenceStatus>();
  late final JCApi _api;

  @override
  Stream<VideoStatus> get selfVideo => _selfVideo.stream.distinct();

  @override
  Stream<AudioStatus> get selfAudio => _selfAudio.stream.distinct();

  @override
  Stream<VideoStatus> get companionVideo => _companionVideo.stream.distinct();

  @override
  Stream<AudioStatus> get companionAudio => _companionAudio.stream.distinct();

  @override
  Stream<ConferenceStatus> get conference => _conference.distinct();

  @override
  void updateVideoStatus() {
    _updateVideoStatus();
  }

  Future<void> _updateVideoStatus() async {
    _selfVideo.add(VideoStatus.fromBool(await _api.video()));
    _companionVideo.add(VideoStatus.fromBool(await _api.otherVideo()));
  }

  @override
  void updateVoiceStatus() {
    _updateVoiceStatus();
  }

  Future<void> _updateVoiceStatus() async {
    _selfAudio.add(AudioStatus.fromBool(await _api.audio()));
    _companionAudio.add(AudioStatus.fromBool(await _api.otherAudio()));
  }

  @override
  void updateConfStatus() {
    _updateConfStatus();
  }

  Future<void> _updateConfStatus() async {
    final status = await _api.confStatus();
    _conference.add(ConferenceStatus.fromString(status));
  }
}
