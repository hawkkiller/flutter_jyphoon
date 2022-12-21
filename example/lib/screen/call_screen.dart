import 'package:flutter/material.dart';
import 'package:jc/jc.dart';
import 'package:jc_example/screen/feed_screen.dart';

/// {@template call_screen}
/// CallScreen widget
/// {@endtemplate}
class CallScreen extends StatefulWidget {
  /// {@macro call_screen}
  const CallScreen({
    super.key,
  });
  @override
  State<CallScreen> createState() => _CallScreenState();
}

class _CallScreenState extends State<CallScreen> {
  late final TextEditingController _companionController;
  late final TextEditingController _ticketController;
  late final JCCall _jcCall;
  late final JcController _jcController;
  late final JCApi _jcApi;
  bool video = false;

  @override
  void initState() {
    super.initState();
    _jcApi = JCApi();
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
                  SDKField(
                    label: 'Companion',
                    controller: _companionController,
                  ),
                  Checkbox(
                      value: video,
                      onChanged: (value) {
                        setState(() {
                          video = value!;
                        });
                      }),
                  SDKField(
                    label: 'Ticket',
                    controller: _ticketController,
                  ),
                  MaterialButton(
                    color: Colors.deepPurple,
                    onPressed: () async {
                      await _jcApi.startCall(
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
                      if (snapshot.data == VideoStatus.off ||
                          !snapshot.hasData) {
                        return const SizedBox();
                      }
                      return SizedBox(
                        key: UniqueKey(),
                        height: 200,
                        width: 100,
                        child: const SelfView(
                          callType: CallType.call,
                        ),
                      );
                    },
                  ),
                  StreamBuilder<VideoStatus>(
                    stream: _jcCall.companionVideo,
                    builder: (context, snapshot) {
                      if (snapshot.data == VideoStatus.off ||
                          !snapshot.hasData) {
                        return const SizedBox();
                      }
                      return SizedBox(
                        key: UniqueKey(),
                        height: 200,
                        width: 100,
                        child: const CompanionView(
                          callType: CallType.conference,
                        ),
                      );
                    },
                  )
                ],
              ),
            ),
          ],
        ),
      );
} // CallScreen
