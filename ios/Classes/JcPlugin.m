#import "JcPlugin.h"
#if __has_include(<jc/jc-Swift.h>)
#import <jc/jc-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "jc-Swift.h"
#endif

@implementation JcPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftJcPlugin registerWithRegistrar:registrar];
}
@end
