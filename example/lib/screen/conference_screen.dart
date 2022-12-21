import 'package:badges/badges.dart';
import 'package:flutter/material.dart';
import 'package:jc/jc.dart';

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
  late final JCApi _jcApi;
  late final JcController _jcController;

  @override
  void initState() {
    super.initState();
    _jcApi = JCApi();
    _jcController = JcController();

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
                    onPressed: () {
                      _jcApi.confJoin(_sessionId.text, '123456');
                    },
                    child: const Text('Join'),
                  ),
                  Container(
                    width: double.infinity,
                    decoration: BoxDecoration(
                      color: Colors.grey[200],
                    ),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        Badge(
                          shape: BadgeShape.square,
                          badgeContent: const Text('Self'),
                          borderRadius: BorderRadius.circular(8),
                          child: Container(
                            width: 100,
                            height: 100,
                            decoration: BoxDecoration(
                              border: Border.all(
                                color: Colors.grey[300]!,
                                width: 5,
                              ),
                            ),
                            child: StreamBuilder(
                              stream: _jcController.call.selfVideo,
                              builder: (context, snapshot) {
                                if (snapshot.data != VideoStatus.on) {
                                  return const SizedBox.shrink();
                                }
                                return const SelfView(
                                  callType: CallType.conference,
                                );
                              },
                            ),
                          ),
                        ),
                        Badge(
                          shape: BadgeShape.square,
                          borderRadius: BorderRadius.circular(8),
                          badgeContent: const Text('Companion'),
                          child: Container(
                            width: 100,
                            height: 100,
                            decoration: BoxDecoration(
                              border: Border.all(
                                color: Colors.grey[300]!,
                                width: 5,
                              ),
                            ),
                            child: StreamBuilder(
                              stream: _jcController.call.companionVideo,
                              builder: (context, snapshot) {
                                if (snapshot.data != VideoStatus.on) {
                                  return const SizedBox.shrink();
                                }
                                return const CompanionView(
                                  callType: CallType.conference,
                                );
                              },
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      );
}
