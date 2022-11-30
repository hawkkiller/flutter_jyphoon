import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'jc_platform_interface.dart';

/// An implementation of [JcPlatform] that uses method channels.
class JC extends JcPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('jc');

  @override
  Future<bool> isInited() async {
    final response = await methodChannel.invokeMethod<bool>('isInited');
    if (response == null) {
      throw PlatformException(
        code: 'isInited',
        message: 'isInited failed',
      );
    }
    return response;
  }
}
