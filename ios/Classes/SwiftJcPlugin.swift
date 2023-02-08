import Flutter
import UIKit
import JCSDKOC.JCClient

public class SwiftJcPlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "jc", binaryMessenger: registrar.messenger())
    let instance = SwiftJcPlugin()
      JCSDKOC.JCClient.init()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    result("iOS " + UIDevice.current.systemVersion)
  }
}
