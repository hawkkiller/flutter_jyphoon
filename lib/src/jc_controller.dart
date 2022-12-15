import 'dart:async';

import 'package:jc/src/jc.dart';

class JcController extends JcReceiver {
  JcController() {
    JcReceiver.setup(this);
  }

  final StreamController<VideoStatus> _selfVideoStatus =
      StreamController<VideoStatus>.broadcast();

  final StreamController<VideoStatus> _companionVideoStatus =
      StreamController<VideoStatus>.broadcast();

  final StreamController<VoiceStatus> _selfVoiceStatus =
      StreamController<VoiceStatus>.broadcast();

  final StreamController<VoiceStatus> _companionVoiceStatus =
      StreamController<VoiceStatus>.broadcast();

  @override
  void onCompanionVideoChange(bool value) => value
      ? _companionVideoStatus.add(VideoStatus.started)
      : _companionVideoStatus.add(VideoStatus.stopped);

  @override
  void onCompanionVoiceChange(bool value) => value
      ? _companionVoiceStatus.add(VoiceStatus.started)
      : _companionVoiceStatus.add(VoiceStatus.ended);

  @override
  void onSelfVideoChange(bool value) => value
      ? _selfVideoStatus.add(VideoStatus.started)
      : _selfVideoStatus.add(VideoStatus.stopped);

  @override
  void onSelfVoiceChange(bool value) => value
      ? _selfVoiceStatus.add(VoiceStatus.started)
      : _selfVoiceStatus.add(VoiceStatus.ended);
}

enum VideoStatus { started, stopped }

enum VoiceStatus { started, ended }
