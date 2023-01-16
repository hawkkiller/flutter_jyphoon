import 'dart:async';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:jc/jyphoon.dart';
import 'package:jc_example/main.dart';
import 'package:jc_example/screen/conference_screen.dart';

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
  late final JyphoonSDK _sdk;

  bool isInitialized = false;

  bool _appKeySet = false;
  bool _displayNameSet = false;
  bool _accountNumberSet = false;
  bool _timeoutSet = false;
  bool _serverAddressSet = false;

  bool _allFieldsSet() {
    return _appKeySet &&
        _displayNameSet &&
        _accountNumberSet &&
        _timeoutSet &&
        _serverAddressSet;
  }

  @override
  void initState() {
    super.initState();
    _sdk = JyphoonSDK();
  }

  @override
  Widget build(BuildContext context) {
    var allFieldsSet = _allFieldsSet();

    return SingleChildScrollView(
      child: Column(
        children: [
          MaterialButton(
            color: Colors.green,
            child: const Text('Is Inited'),
            onPressed: () async {
              ScaffoldMessenger.of(context).showSnackBar(
                SnackBar(
                  content: Text(
                    await _sdk.isInited().then((value) => value.toString()),
                  ),
                ),
              );
            },
          ),
          _MaterialButton(
            color: Colors.deepPurple,
            onTap: () => _sdk.initialize().then(
                  (value) => setState(
                    () => isInitialized = true,
                  ),
                ),
            title: 'initialize',
            enabled: _appKeySet,
          ),
          SDKField(
            label: 'AppKey',
            onTap: (str) => _sdk.setAppKey(str).then(
                  (value) => setState(
                    () => _appKeySet = true,
                  ),
                ),
          ),
          SDKField(
            label: 'DisplayName',
            onTap: (str) => _sdk.setDisplayName(str).then(
                  (value) => setState(
                    () => _displayNameSet = true,
                  ),
                ),
            isActive: isInitialized,
          ),
          SDKField(
            label: 'AccountNumber',
            onTap: (str) => _sdk.setAccountNumber(str).then(
                  (value) => setState(
                    () => _accountNumberSet = true,
                  ),
                ),
            isActive: isInitialized,
          ),
          SDKField(
            label: 'ServerAddress',
            onTap: (str) => _sdk.setServerAddress(str).then(
                  (value) => setState(
                    () => _serverAddressSet = true,
                  ),
                ),
            isActive: isInitialized,
          ),
          SDKField(
            label: 'Timeout',
            onTap: (str) => _sdk.setTimeout(int.parse(str)).then(
                  (value) => setState(
                    () => _timeoutSet = true,
                  ),
                ),
            isActive: isInitialized,
          ),
          _MaterialButton(
            onTap: () {
              Navigator.of(context).push(MaterialPageRoute(
                builder: (context) => const ConferenceScreen(),
              ));
            },
            enabled: allFieldsSet,
            title: 'Go to Conference Screen',
          )
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

  Future<void> _save() async {
    await prefs.setString(
      widget.label,
      _controller.text,
    );
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(8),
      child: Row(
        children: [
          Expanded(
            child: TextField(
              onChanged: (value) async {
                await _save();
              },
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