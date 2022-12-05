import 'package:flutter/material.dart';

/// {@template local_view}
/// LocalView widget
/// {@endtemplate}
class LocalView extends StatelessWidget {
  /// {@macro local_view}
  const LocalView({super.key});

  static const String viewType = 'local-view';

  @override
  Widget build(BuildContext context) => const AndroidView(
        viewType: viewType,
        layoutDirection: TextDirection.ltr,
      );
}
