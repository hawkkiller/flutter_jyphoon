import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

/// {@template self_view}
/// SelfView widget
/// {@endtemplate}
class SelfView extends StatelessWidget {
  /// {@macro self_view}
  const SelfView({super.key});

  static const String viewType = 'self-view';

  @override
  Widget build(BuildContext context) {
    if (Platform.isIOS) {
      return const SizedBox();
    }
    if (Platform.isAndroid) {
      return const AndroidView(
        viewType: viewType,
        layoutDirection: TextDirection.ltr,
        creationParamsCodec: StandardMessageCodec(),
      );
    }
    throw UnsupportedError('Unsupported platform');
  }
}
