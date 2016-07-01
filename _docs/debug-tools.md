---
title: Debug Tools
layout: docs
permalink: /docs/debug-tools.html
prevPage: placeholder-fade-duration.html
nextPage: implicit-hierarchy-mgmt.html
---

AsyncDisplayKit offers the following developer debug tools.

<ul>
<li><a href = "debug-tools.html/hit-test-visualization">Hit Test Visualization</a></li>
Quickly visualize all ASControlNode tappable areas to see the size and placement of the tap targets in your app.
<br>
<br>
<li><a href = "debug-tools.html#image-scaling">Image Scaling</a></li>
Quickly visualize all upscaling or downscaling of images in your app contained in ASImageNodes (+ subclasses). 
<br>
<br>
<li><a href = "debug-tools.html#range-controller-visualization">ASRangeController Visualization</a></li>
Allows you to quickly see onscreen ASRangeControllers + tuning parameters.
</ul>

##Hit Test Visualization
This debug feature adds a semi-transparent highlight overlay on any ASControlNodes containing a `target:action:` pair or gesture recognizer. 

The tappable range is defined as the ASControlNode’s frame + its `.hitTestSlop` `UIEdgeInsets`. Hit test slop is a unique feature of `ASControlNode` that allows it to extend its tappable range. 

In the screenshot below, you can quickly see that
<ul> 
  <li>The tappable area for the avatar image overlaps the username’s tappable area. In this case, the user avatar image is on top in the view hierarchy and is capturing some touches that should go to the username.</li>
  <li>It would probably make sense to expand the `.hitTestSlop` for the username to allow the user to more easily hit it.</li>
  <li>I’ve accidentally set the hitTestSlop’s UIEdgeInsets to be positive instead of negative for the photo likes count label. It’s going to be hard for a user to tap the smaller target.</li>
</ul>

![screen shot 2016-03-25 at 4 39 23 pm](https://cloud.githubusercontent.com/assets/3419380/14057034/e1e71450-f2b1-11e5-8091-3e6f22862994.png)

###Hit Test Slop Restrictions

A _green_ border on the edge(s) of the highlight overlay indicates that that edge of the tapable area is restricted by one of it's superview's tapable areas. 

An _orange_ border on the edge(s) of the highlight overlay indicates that that edge of the tapable area is clipped by .clipsToBounds of a parent in its hierarchy. 

###Usage
In your `AppDelegate.m` file, 
<ul>
  <li>import `AsyncDisplayKit+Debug.h`</li>
  <li>add `[ASControlNode setEnableHitTestDebug:YES]` at the top of your `didFinishLaunchingWithOptions:` method</li>
</ul>
Make sure to call this method before initializing any ASControlNodes, including ASButtonNodes, ASImageNodes, and ASTextNodes.


##Image Scaling
##Visualize ASImageNode.image’s pixel scaling
This debug feature adds a red text overlay on the bottom right hand corner of an ASImageNode if (and only if) the image’s size in pixels does not match it’s bounds size in pixels, e.g.

```objective-c
imageSizeInPixels = image.size * image.scale
boundsSizeInPixels = bounds.size * contentsScale
scaleFactor = imageSizeInPixels / boundsSizeInPixels

if (scaleFactor != 1.0) {
      NSString *scaleString = [NSString stringWithFormat:@"%.2fx", scaleFactor];
      _debugLabelNode.hidden = NO;
}
```

**This debug feature is useful for quickly determining if you are**
<ul>
  <li><strong>downloading and rendering excessive amounts of image data</li> 
  <li>upscaling a low quality image</strong></li>
</ul>

In the screenshot below of an app with this debug feature enabled, you can see that the avatar image is unnecessarily large (9x too large) for it’s bounds size and that the center picture is more optimized, but not perfectly so. If you control your own endpoint, optimize your API / app to return an optimally sized image.

![screen shot 2016-03-25 at 4 04 59 pm](https://cloud.githubusercontent.com/assets/3419380/14056994/15561daa-f2b1-11e5-9606-59d54d2b5354.png)
###Usage
In your `AppDelegate.m` file, 
<ul>
  <li>import `AsyncDisplayKit+Debug.h`</li>
  <li>add `[ASImageNode setShouldShowImageScalingOverlay:YES]` at the top of your `didFinishLaunchingWithOptions:` method</li>
</ul>
Make sure to call this method before initializing any ASImageNodes or subclasses, including ASNetworkImageNode and ASMultiplexImageNode.

##Range Controller Visualization

This has not yet been formally added to the framework, but you can easily apply <a href = "https://github.com/facebook/AsyncDisplayKit/pull/1390">PR #1390</a> as a diff to your project.  
