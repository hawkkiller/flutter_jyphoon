import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:jc/src/controller/jc_controller.dart';

/// {@template self_view}
/// SelfView widget
/// {@endtemplate}
class SelfView extends StatelessWidget {
  /// {@macro self_view}
  const SelfView({required this.callType, super.key});

  final CallType callType;

  static const String viewType = 'self-view';

  @override
  Widget build(BuildContext context) => AndroidView(
        viewType: viewType,
        layoutDirection: TextDirection.ltr,
        creationParamsCodec: const StandardMessageCodec(),
        creationParams: {
          'callType': callType.index,
        },
      );
}
