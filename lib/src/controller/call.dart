import 'package:jc/jc.dart';
import 'package:rxdart/subjects.dart';

abstract class Call {
  abstract final Stream<VideoStatus> selfVideo;
  abstract final Stream<VideoStatus> companionVideo;

  void onVideoChange({
    required bool value,
    required bool self,
  });
}

class CallImpl implements Call {
  final _selfVideo = BehaviorSubject<VideoStatus>();
  final _companionVideo = BehaviorSubject<VideoStatus>();

  @override
  Stream<VideoStatus> get selfVideo => _selfVideo.stream.distinct();

  @override
  Stream<VideoStatus> get companionVideo => _companionVideo.stream.distinct();

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
