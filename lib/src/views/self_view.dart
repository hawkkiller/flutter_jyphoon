import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:jc/src/views/controller.dart';

/// {@template self_view}
/// SelfView widget
/// {@endtemplate}
class SelfView extends StatelessWidget {
  /// {@macro self_view}
  const SelfView({super.key});

  static const String viewType = 'self-view';

  @override
  Widget build(BuildContext context) => const _SelfView();
}

class _SelfView extends StatefulWidget {
  const _SelfView();

  @override
  State<_SelfView> createState() => _SelfViewState();
}

class _SelfViewState extends State<_SelfView> {
  late final SelfController _controller;

  @override
  void initState() {
    _controller = SelfController();
    super.initState();
  }

  @override
  Widget build(BuildContext context) => LayoutBuilder(
        builder: (context, constraints) {
          _controller.setSelfFrame(
            constraints.maxWidth,
            constraints.maxHeight,
          );
          if (Platform.isIOS) {
            return UiKitView(
              viewType: SelfView.viewType,
              layoutDirection: TextDirection.ltr,
              onPlatformViewCreated: (_) => _controller.setSelfFrame(
                constraints.maxWidth,
                constraints.maxHeight,
              ),
              creationParamsCodec: const StandardMessageCodec(),
            );
          }
          if (Platform.isAndroid) {
            return AndroidView(
              viewType: SelfView.viewType,
              layoutDirection: TextDirection.ltr,
              onPlatformViewCreated: (_) => _controller.setSelfFrame(
                constraints.maxWidth,
                constraints.maxHeight,
              ),
              creationParamsCodec: const StandardMessageCodec(),
            );
          }
          throw UnsupportedError('Unsupported platform');
        },
      );
}
