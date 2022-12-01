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
    final res = await methodChannel.invokeMethod<bool>('isInited');
    if (res == null) {
      throw PlatformException(
        code: 'isInited',
        message: 'isInited failed',
      );
    }
    return res;
  }

  @override
  Future<bool> initialize() async {
    final res = await methodChannel.invokeMethod<bool>('initialize');
    if (res == null) {
      throw PlatformException(
        code: 'initialize',
        message: 'initialize failed',
      );
    }
    return res;
  }

  @override
  Future<void> setAppKey(String appKey) async {
    final arguments = {'appKey': appKey};
    await methodChannel.invokeMethod<void>('setAppKey', arguments);
  }

  @override
  Future<bool> setAccountNumber(String accountNumber) async {
    final arguments = {'accountNumber': accountNumber};
    final res =
        await methodChannel.invokeMethod<bool>('setAccountNumber', arguments);
    if (res == null) {
      throw PlatformException(
        code: 'setAccountNumber',
        message: 'setAccountNumber failed',
      );
    }
    return res;
  }
}
