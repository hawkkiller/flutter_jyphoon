enum VideoStatus {
  on,
  off;

  static VideoStatus fromBool(bool value) {
    if (value) {
      return VideoStatus.on;
    }
    return VideoStatus.off;
  }
}

enum AudioStatus {
  on,
  off;

  static AudioStatus fromBool(bool value) {
    if (value) {
      return AudioStatus.on;
    }
    return AudioStatus.off;
  }
}

enum ConferenceStatus {
  on,
  waiting,
  off;

  static ConferenceStatus fromString(String value) {
    switch (value) {
      case 'on':
        return ConferenceStatus.on;
      case 'waiting':
        return ConferenceStatus.waiting;
      case 'off':
        return ConferenceStatus.off;
      default:
        throw Exception('Unknown conference status: $value');
    }
  }
}
