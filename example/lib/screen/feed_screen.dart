import 'dart:async';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:jc/jc.dart';
import 'package:jc_example/main.dart';

/// {@template feed_screen}
/// FeedScreen widget
/// {@endtemplate}
class FeedScreen extends StatefulWidget {
  /// {@macro feed_screen}
  const FeedScreen({super.key});

  @override
  State<FeedScreen> createState() => _FeedScreenState();
}

class _FeedScreenState extends State<FeedScreen> {
  late final JCApi _jcApi;

  bool isInitialized = false;

  bool _appKeySet = false;
  bool _displayNameSet = false;
  bool _accountNumberSet = false;
  bool _timeoutSet = false;
  bool _serverAddressSet = false;

  bool allFieldsSet() {
    return _appKeySet &&
        _displayNameSet &&
        _accountNumberSet &&
        _timeoutSet &&
        _serverAddressSet;
  }

  @override
  void initState() {
    super.initState();
    _jcApi = JCApi();
  }

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      child: Column(
        children: [
          _MaterialButton(
            color: Colors.deepPurple,
            onTap: () async {
              await _jcApi.initialize();
              setState(() {
                isInitialized = true;
              });
            },
            title: 'initialize',
            enabled: _appKeySet,
          ),
          SDKField(
            label: 'AppKey',
            onTap: (str) async {
              await _jcApi.setAppKey(str);
              setState(() {
                _appKeySet = true;
              });
            },
          ),
          SDKField(
            label: 'DisplayName',
            onTap: _jcApi.setDisplayName,
            isActive: isInitialized,
          ),
          SDKField(
            label: 'AccountNumber',
            onTap: _jcApi.setAccountNumber,
            isActive: isInitialized,
          ),
          SDKField(
            label: 'ServerAddress',
            onTap: _jcApi.setServerAddress,
            isActive: isInitialized,
          ),
          SDKField(
            label: 'Timeout',
            onTap: (value) => _jcApi.setTimeout(int.parse(value)),
            isActive: isInitialized,
          ),
          _MaterialButton(
              onTap: () {}, enabled: allFieldsSet(), title: 'Go to call page')
        ],
      ),
    );
  }
} // FeedScreen

class SDKField extends StatefulWidget {
  const SDKField({
    required this.label,
    this.isActive = true,
    this.onTap,
    this.controller,
    super.key,
  });

  final String label;
  final TextEditingController? controller;
  final FutureOr<void> Function(String)? onTap;
  final bool isActive;

  @override
  State<SDKField> createState() => _SDKFieldState();
}

class _SDKFieldState extends State<SDKField> {
  late final TextEditingController _controller;

  @override
  void initState() {
    super.initState();
    _controller = widget.controller ?? TextEditingController();
    _controller.text = prefs.getString(widget.label) ?? '';
  }

  @override
  void dispose() {
    super.dispose();
    if (widget.controller == null) _controller.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(8),
      child: Row(
        children: [
          Expanded(
            child: TextField(
              enabled: widget.isActive,
              controller: _controller,
              decoration: InputDecoration(
                border: const OutlineInputBorder(),
                labelText: widget.label,
              ),
            ),
          ),
          const SizedBox(width: 8),
          if (widget.onTap != null)
            _MaterialButton(
              color: CupertinoColors.systemYellow,
              enabled: widget.isActive,
              title: 'Set ${widget.label}',
              onTap: () async {
                ScaffoldMessenger.of(context).showSnackBar(SnackBar(
                  content: Text('Set ${widget.label} to ${_controller.text}'),
                ));
                await widget.onTap?.call(_controller.text);
                await prefs.setString(
                  widget.label,
                  _controller.text,
                );
              },
            ),
        ],
      ),
    );
  }
} // _SDKField

class _MaterialButton extends StatelessWidget {
  const _MaterialButton({
    required this.onTap,
    required this.enabled,
    required this.title,
    this.color = CupertinoColors.systemYellow,
  });

  final VoidCallback? onTap;
  final bool enabled;
  final String title;
  final Color color;

  @override
  Widget build(BuildContext context) => MaterialButton(
        onPressed: enabled ? onTap : null,
        color: color,
        disabledColor: CupertinoColors.inactiveGray,
        child: Text(title),
      );
} // _SdkButton