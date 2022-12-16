import 'package:flutter/material.dart';
import 'package:jc/jc.dart';

/// {@template call_screen}
/// CallScreen widget
/// {@endtemplate}
class CallScreen extends StatefulWidget {
  /// {@macro call_screen}
  const CallScreen({
    required this.jcApi,
    super.key,
  });

  final JCApi jcApi;

  @override
  State<CallScreen> createState() => _CallScreenState();
}

class _CallScreenState extends State<CallScreen> {
  late final TextEditingController _companionController;
  late final TextEditingController _ticketController;
  late final JCCall _jcCall;
  late final JcController _jcController;
  bool video = false;

  @override
  void initState() {
    super.initState();
    _jcController = JcController();
    _jcCall = _jcController.call;
    _companionController = TextEditingController();
    _ticketController = TextEditingController();
  }

  @override
  Widget build(BuildContext context) => Scaffold(
        body: CustomScrollView(
          slivers: [
            const SliverAppBar(
              title: Text('Call'),
              centerTitle: true,
            ),
            SliverList(
              delegate: SliverChildListDelegate(
                [
                  TextField(
                    controller: _companionController,
                    decoration: const InputDecoration(
                      labelText: 'Companion',
                    ),
                  ),
                  Checkbox(
                      value: video,
                      onChanged: (value) {
                        setState(() {
                          video = value!;
                        });
                      }),
                  TextField(
                    controller: _ticketController,
                    decoration: const InputDecoration(
                      labelText: 'Ticket',
                    ),
                  ),
                  MaterialButton(
                    color: Colors.deepPurple,
                    onPressed: () async {
                      await widget.jcApi.startCall(
                        _companionController.text,
                        video,
                        _ticketController.text,
                      );
                    },
                    child: const Text('Start Call'),
                  ),
                  StreamBuilder<VideoStatus>(
                    stream: _jcCall.selfVideo,
                    builder: (context, snapshot) {
                      final data = snapshot.data;
                      if (data == null || data == VideoStatus.off) {
                        return const Text('Self Video: null');
                      }

                      return const SelfView();
                    },
                  ),
                  StreamBuilder<VideoStatus>(
                    stream: _jcCall.companionVideo,
                    builder: (context, snapshot) {
                      final data = snapshot.data;
                      if (data == null || data == VideoStatus.off) {
                        return const Text('Companion Video: null');
                      }

                      return const CompanionView();
                    },
                  )
                ],
              ),
            ),
          ],
        ),
      );
} // CallScreen
