import 'package:jc/src/model/enum.dart';

class CallState {
  const CallState({
    required this.audio,
    required this.video,
    required this.otherAudio,
    required this.otherVideo,
    required this.callStatus,
  });

  factory CallState.fromJson(Map<String?, Object?> json) => CallState(
        audio: AudioStatus.fromBool(value: json['audio']! as bool),
        video: VideoStatus.fromBool(value: json['video']! as bool),
        otherAudio: AudioStatus.fromBool(value: json['otherAudio']! as bool),
        otherVideo: VideoStatus.fromBool(value: json['otherVideo']! as bool),
        callStatus: CallStatus.fromString(json['callStatus']! as String),
      );

  final AudioStatus audio;
  final VideoStatus video;
  final AudioStatus otherAudio;
  final VideoStatus otherVideo;
  final CallStatus callStatus;
}
