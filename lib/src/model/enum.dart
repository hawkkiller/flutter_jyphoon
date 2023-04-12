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

enum ClientState {
  notInit(0),
  idle(1),
  logining(2),
  logined(3),
  logouting(4);

  const ClientState(this.value);

  final int value;

  static ClientState fromInt(int value) {
    switch (value) {
      case 0:
        return ClientState.notInit;
      case 1:
        return ClientState.idle;
      case 2:
        return ClientState.logining;
      case 3:
        return ClientState.logined;
      case 4:
        return ClientState.logouting;
      default:
        throw Exception('Unknown client state: $value');
    }
  }
}
