import 'package:flutter/material.dart';
import 'package:jc/jyphoon.dart';

/// {@template conference_screen}
/// ConferenceScreen widget
/// {@endtemplate}
class ConferenceScreen extends StatefulWidget {
  /// {@macro conference_screen}
  const ConferenceScreen({super.key});

  @override
  State<ConferenceScreen> createState() => _ConferenceScreenState();
} // ConferenceScreen

/// State for widget ConferenceScreen
class _ConferenceScreenState extends State<ConferenceScreen> {
  late final TextEditingController _sessionId;
  late final JyphoonSDK _sdk;

  @override
  void initState() {
    super.initState();
    _sdk = JyphoonSDK();

    _sessionId = TextEditingController();
  }

  @override
  Widget build(BuildContext context) => Scaffold(
        body: CustomScrollView(
          slivers: [
            const SliverAppBar(
              title: Text('Conference'),
              centerTitle: true,
            ),
            SliverList(
              delegate: SliverChildListDelegate(
                [
                  TextField(
                    controller: _sessionId,
                    decoration: const InputDecoration(
                      labelText: 'Session ID',
                    ),
                  ),
                  ElevatedButton(
                    onPressed: () async {
                      await _sdk.confJoin(_sessionId.text, '123456', true);
                    },
                    child: const Text('Join'),
                  ),
                  ElevatedButton(
                    onPressed: () async {
                      await _sdk.confLeave();
                    },
                    child: const Text('Leave'),
                  ),
                  Container(
                    height: 300,
                    decoration: BoxDecoration(
                      color: Colors.grey[200],
                    ),
                    child: Row(
                      children: [
                        Expanded(
                          child: Badge(
                            label: const Text('Self'),
                            child: DecoratedBox(
                              decoration: BoxDecoration(
                                border: Border.all(
                                  color: Colors.grey[300]!,
                                  width: 5,
                                ),
                              ),
                              child: StreamBuilder(
                                stream: _sdk.state.selfVideo,
                                builder: (context, snapshot) {
                                  if (snapshot.data != VideoStatus.on) {
                                    return const SizedBox.expand();
                                  }
                                  return StreamBuilder<ConferenceStatus>(
                                    stream: _sdk.state.conference,
                                    builder: (context, snapshot) {
                                      return const SelfView();
                                    },
                                  );
                                },
                              ),
                            ),
                          ),
                        ),
                        const SizedBox(width: 20),
                        Expanded(
                          child: Badge(
                            label: const Text('Companion'),
                            child: DecoratedBox(
                              decoration: BoxDecoration(
                                border: Border.all(
                                  color: Colors.grey[300]!,
                                  width: 5,
                                ),
                              ),
                              child: StreamBuilder(
                                stream: _sdk.state.companionVideo,
                                builder: (context, snapshot) {
                                  if (snapshot.data != VideoStatus.on) {
                                    return const SizedBox.expand();
                                  }
                                  return const CompanionView();
                                },
                              ),
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                  StreamBuilder<AudioStatus>(
                    stream: _sdk.state.selfAudio,
                    builder: (context, snapshot) {
                      if (snapshot.data == null) {
                        return const Text('data is null');
                      }
                      return TextButton(
                        onPressed: () {
                          _sdk.setAudio(
                            snapshot.data == AudioStatus.on ? false : true,
                          );
                        },
                        child: Text(
                          snapshot.data == AudioStatus.on ? 'Mute' : 'Unmute',
                        ),
                      );
                    },
                  ),
                  StreamBuilder<VideoStatus>(
                    stream: _sdk.state.selfVideo,
                    builder: (context, snapshot) {
                      if (snapshot.data == null) {
                        return const Text('data is null');
                      }
                      return TextButton(
                        onPressed: () {
                          _sdk.setVideo(
                            snapshot.data == VideoStatus.on ? false : true,
                          );
                        },
                        child: Text(
                          snapshot.data == VideoStatus.on
                              ? 'Turn video off'
                              : 'Turn video on',
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
}
