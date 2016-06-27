---
title: Installation
layout: docs
permalink: /docs/installation.html
prevPage: philosophy.html
nextPage: intelligent-preloading.html
---

AsyncDisplayKit may be added to your project via 
<ul>
  <li><a href = "installation.html#cocoapods">CocoaPods</a></li>
  <li><a href = "installation.html#carthage-standard-build">Carthage</a> (standard build)</li>
  <li><a href = "installation.html#static-library">Static Library</a></li>
</ul>

Don't forget to import the framework header or create an <a href="https://developer.apple.com/library/ios/documentation/swift/conceptual/buildingcocoaapps/MixandMatch.html">Objective-C bridging header</a> (if you're using **Swift**)

<div class = "highlight-group">
<span class="language-toggle"><a data-lang="objective-c" class = "active objcButton">Objective-C</a></span>
<div class = "code">
	<pre lang="objc" class="objc">
#import &lt;AsyncDisplayKit/AsyncDisplayKit.h&gt;
	</pre>
</div>
</div>

If you have any problems installing AsyncDisplayKit, don't hesitate to reach out to us on <a href = "https://github.com/facebook/AsyncDisplayKit/issues">Github</a> or <a href = "/resources.html#slack">Slack</a>!

## CocoaPods

AsyncDisplayKit is available on <a href="http://cocoapods.org">CocoaPods</a>. Add the following to your Podfile:

<div class = "highlight-group">
<span class="language-toggle"><a data-lang="ruby" class = "active">CocoaPods</a></span>

<div class = "code">
	<pre lang="ruby" class="CocoaPods">
target 'MyApp' do
	pod "AsyncDisplayKit"
end
	</pre>
</div>
</div>

Quit Xcode completely before running 

`> pod install` 

in the project directory in Terminal.  

To update your version of AsyncDisplayKit, run 

`> pod update AsyncDisplayKit`

in the project directory in Terminal. 

Notes: 
<ul>
  <li>With CocoaPods, be sure to open use workspace (`.xcworkspace`) and _not_ the project file (`.xcodeproj`)</li>
  <li>Please see the sample <a href = "https://github.com/facebook/AsyncDisplayKit/tree/master/examples/ASDKgram">ASDKgram</a> app for an example of how to include AsyncDisplayKit in an Xcode project via CocoaPods.</li>
</ul>

## Carthage (standard build*)

<div class = "note">
The standard way to use Carthage is by having a Cartfile listing the dependencies, and then running carthage update to download them in the Cathage/Checkouts folder, and build each of those into frameworks located in the Carthage/Build folder, and finally the developer has to manually integrate in the project.
</div>

AsyncDisplayKit is also available through <a href="https://github.com/Carthage/Carthage">Carthage</a>. 

Add the following to your Cartfile to get the **latest release branch**:

<div class = "highlight-group">
<span class="language-toggle"><a data-lang="carthage" class = "active">Carthage</a></span>
<div class = "code">
	<pre lang="carthage" class="carthage">
github "facebook/AsyncDisplayKit"
	</pre>
</div>
</div>

Or, to get the **master branch**:

<div class = "highlight-group">
<span class="language-toggle"><a data-lang="carthage" class = "active">Carthage</a></span>
<div class = "code">
	<pre lang="carthage" class="carthage">
github "facebook/AsyncDisplayKit" "master"
	</pre>
</div>
</div>

AsyncDisplayKit has its own Cartfile which lists its dependencies, so this is the only neccessary line. 

Run 

`> carthage update` 

in Terminal. This will fetch dependencies into a Carthage/Checkouts folder, then build each one. 

Look for terminal output confirming `AsyncDisplayKit`, `PINRemoteImage (3.0.0-beta.2)` and `PINCache` are all fetched and built. The ASDK framework Cartfile should handle the dependencies correctly. 

In Xcode, on your application targets’ **“General”** settings tab, in the **“Linked Frameworks and Libraries”** section, drag and drop each framework you want to use from the Carthage/Build folder on disk.

## Carthage (light)

AsyncDisplayKit does not yet support the lighter way of using Carthage, in which you manually add the project files. This is because one of its dependencies, PINCache (a nested dependency of PINRemoteImag) does not have a project file. 

Without including PINRemoteImage and PINCache, you will not get AsyncDisplayKit's full image feature set. 
