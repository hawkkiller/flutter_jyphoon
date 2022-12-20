import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:jc/src/controller/jc_controller.dart';

/// {@template companion_view}
/// CompanionView widget
/// Display this widget to show the companion view in the call.
/// {@endtemplate}
@immutable
class CompanionView extends StatelessWidget {
  /// {@macro companion_view}
  const CompanionView({required this.callType, super.key});

  final CallType callType;

  static const String viewType = 'companion-view';

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
