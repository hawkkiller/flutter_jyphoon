import 'package:jc/jc.dart';
import 'package:rxdart/subjects.dart';

abstract class JCState {
  abstract final Stream<VideoStatus> selfVideo;
  abstract final Stream<VideoStatus> companionVideo;

  abstract final Stream<bool> conf;

  void onVideoChange({
    required bool value,
    required bool self,
  });
}

class JCStateImpl implements JCState {
  final _selfVideo = BehaviorSubject<VideoStatus>();
  final _companionVideo = BehaviorSubject<VideoStatus>();
  final _conf = BehaviorSubject<bool>();

  @override
  Stream<VideoStatus> get selfVideo => _selfVideo.stream.distinct();

  @override
  Stream<VideoStatus> get companionVideo => _companionVideo.stream.distinct();

  @override
  Stream<bool> get conf => _conf.distinct();

  @override
  void onVideoChange({
    required bool value,
    required bool self,
  }) {
    final status = VideoStatus.fromBool(value);
    if (self) {
      _selfVideo.add(status);
    } else {
      _companionVideo.add(status);
    }
  }
}
