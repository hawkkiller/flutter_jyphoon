import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'jc_platform_interface.dart';

/// An implementation of [JcPlatform] that uses method channels.
class MethodChannelJc extends JcPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('jc');

  @override
  Future<String?> getPlatformVersion() async {
    final version =
        await methodChannel.invokeMethod<bool>('getPlatformVersion');
    return version.toString();
  }
}
