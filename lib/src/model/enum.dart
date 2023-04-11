enum VideoStatus {
  on(value: true),
  off(value: false);

  const VideoStatus({required this.value});

  final bool value;

  static VideoStatus fromBool({required bool value}) {
    if (value) {
      return VideoStatus.on;
    }
    return VideoStatus.off;
  }
}

enum AudioStatus {
  on(value: true),
  off(value: false);

  const AudioStatus({required this.value});

  final bool value;

  static AudioStatus fromBool({required bool value}) {
    if (value) {
      return AudioStatus.on;
    }
    return AudioStatus.off;
  }
}

enum CallStatus {
  on,
  waiting,
  off;

  static CallStatus fromString(String value) {
    switch (value) {
      case 'on':
        return CallStatus.on;
      case 'waiting':
        return CallStatus.waiting;
      case 'off':
        return CallStatus.off;
      default:
        throw Exception('Unknown conference status: $value');
    }
  }
}
