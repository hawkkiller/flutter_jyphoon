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
  Widget build(BuildContext context) {
    if (Platform.isIOS) {
      return const _UiKitSelfView();
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

class _UiKitSelfView extends StatefulWidget {
  const _UiKitSelfView();

  @override
  State<_UiKitSelfView> createState() => __UiKitSelfViewState();
}

class __UiKitSelfViewState extends State<_UiKitSelfView> {
  late final UiKitController _controller;

  @override
  void initState() {
    _controller = UiKitController();
    super.initState();
  }

  @override
  Widget build(BuildContext context) => LayoutBuilder(
        builder: (context, constraints) {
          _controller.setSelfFrame(
            constraints.maxWidth,
            constraints.maxHeight,
          );
          return UiKitView(
            viewType: SelfView.viewType,
            layoutDirection: TextDirection.ltr,
            onPlatformViewCreated: (_) => _controller.setSelfFrame(
              constraints.maxWidth,
              constraints.maxHeight,
            ),
            creationParamsCodec: const StandardMessageCodec(),
          );
        },
      );
}
