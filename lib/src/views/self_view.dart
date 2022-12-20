import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

/// {@template self_view}
/// SelfView widget
/// {@endtemplate}
class SelfView extends StatelessWidget {
  /// {@macro self_view}
  const SelfView({super.key});

  static const String viewType = 'local-view';

  @override
  Widget build(BuildContext context) => AndroidView(
        viewType: viewType,
        layoutDirection: TextDirection.ltr,
        onPlatformViewCreated: (id) {
          print('SelfView: onPlatformViewCreated: $id');
        },
        creationParamsCodec: const StandardMessageCodec(),
      );
}
