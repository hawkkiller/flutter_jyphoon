import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'jc_method_channel.dart';

abstract class JcPlatform extends PlatformInterface {
  /// Constructs a JcPlatform.
  JcPlatform() : super(token: _token);

  static final Object _token = Object();

  static JcPlatform _instance = MethodChannelJc();

  /// The default instance of [JcPlatform] to use.
  ///
  /// Defaults to [MethodChannelJc].
  static JcPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [JcPlatform] when
  /// they register themselves.
  static set instance(JcPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
