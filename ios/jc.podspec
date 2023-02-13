#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint jc.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'jc'
  s.version          = '0.0.1'
  s.summary          = 'A new Flutter plugin project.'
  s.description      = <<-DESC
A new Flutter plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.dependency 'Flutter'
  s.platform = :ios, '9.0'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
  s.swift_version = '5.0'
  s.preserve_paths = 'JCSDKOC.framework'
  s.vendored_frameworks = 'JCSDKOC.framework'
  s.libraries = 'c++', 'z', 'resolv'
  s.frameworks = 'SystemConfiguration', 'AssetsLibrary', 'AudioToolbox',
  'VideoToolBox', 'AVFoundation', 'CFNetwork', 'CoreMedia', 'CoreMotion', 'CoreVideo', 'GLKit',
  'ReplayKit', 'Security'
  s.xcconfig = {'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) ZPLATFORM=ZPLATFORM_IOS'}
end
