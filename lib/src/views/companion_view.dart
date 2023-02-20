import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

/// {@template companion_view}
/// CompanionView widget
/// Display this widget to show the companion view in the call.
/// {@endtemplate}
@immutable
class CompanionView extends StatelessWidget {
  /// {@macro companion_view}
  const CompanionView({super.key});

  static const String viewType = 'companion-view';

  @override
  Widget build(BuildContext context) {
    if (Platform.isIOS) {
      return const UiKitView(
        viewType: viewType,
        layoutDirection: TextDirection.ltr,
        creationParamsCodec: StandardMessageCodec(),
      );
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
