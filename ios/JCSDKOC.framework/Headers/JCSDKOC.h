//
//  JCSDKOC.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <UIKit/UIKit.h>
#elif TARGET_OS_MAC
#import <Cocoa/Cocoa.h>
#endif

#define ZPLATFORM  ((TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR) ? ZPLATFORM_IOS : ZPLATFORM_OSX)

// In this header, you should import all the public headers of your framework using statements like #import <JCSDKOC/PublicHeader.h>

#import <JCSDKOC/JCClient.h>
#import <JCSDKOC/JCLog.h>
#import <JCSDKOC/JCNet.h>
#import <JCSDKOC/JCJson.h>

#if __has_include(<JCSDKOC/JCCall.h>)
#import <JCSDKOC/JCMediaDevice.h>
#import <JCSDKOC/JCCall.h>
#endif

#if __has_include(<JCSDKOC/JCMediaChannel.h>)
#import <JCSDKOC/JCMediaDevice.h>
#import <JCSDKOC/JCMediaChannel.h>
#endif

#if __has_include(<JCSDKOC/JCMessageChannel.h>)
#import <JCSDKOC/JCMessageChannel.h>
#import <JCSDKOC/JCGroup.h>
#import <JCSDKOC/JCStorage.h>
#endif

#if __has_include(<JCSDKOC/JCAccount.h>)
#import <JCSDKOC/JCAccount.h>
#endif

#if __has_include(<JCSDKOC/JCDoodle.h>)
#import <JCSDKOC/JCDoodle.h>
#endif

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <JCSDKOC/JCPush.h>
#endif

//! Project version number for JCSDKOC.
FOUNDATION_EXPORT double JCSDKOCVersionNumber;

//! Project version string for JCSDKOC.
FOUNDATION_EXPORT const unsigned char JCSDKOCVersionString[];

#define JCVersion  [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]
