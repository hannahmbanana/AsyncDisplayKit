---
title: Corner Rounding
layout: docs
permalink: /docs/corner-rounding.html
prevPage: drawing-priority.html
nextPage: hit-test-slop.html
---

If you've worked with Scott Goodson before, you’ll know that use of CALayer’s expensive `.cornerRadius` property is one of his biggest pet peeves. This post will cover:

<ul>
<li><a href = "corner-rounding.html#calayer-s-cornerradius-is-expensive">why you shouldn’t use CALayer’s .cornerRadius</a></li>
<li><a href = "corner-rounding.html#performant-corner-rounding-strategies">more performant corner rounding options & and when to use them</a></li>
<li><a href = "corner-rounding.html#corner-rounding-strategy-flowchart">a flow chart for choosing your ideal corner rounding strategy</a></li>
<li><a href = "corner-rounding.html#corner-rounding-strategy-flowchart">ASDK corner rounding methods</a></li>
</ul>

## CALayer's .cornerRadius is Expensive

When it comes to corner rounding, many developers stick with CALayer's `.cornerRadius` property.  Unfortunately, this convenient property greatly taxes performance and should only be used when there is _no_ alternative.  

Why is `.cornerRadius` so expensive? Use of CALayer's `.cornerRadius` property triggers offScreen rendering to perform the clipping operation on every frame - 60 FPS during scrolling - even if the content in that area isn't changing! This means that the GPU has to switch context on every frame between compositing the new frame vs. doing one frame’s subtree. This intensive thrash annihilates performance for a lot of devices.  On the iPhone 4, 4S, and 5 / 5C (along with comparable iPads / iPods), expect to see visually degraded performance. On the iPhone 5S and new, reduced head room will make frame drops more likely. 


####Is it ever okay to use CALayer's .cornerRadius property?

There are a few _rare_ cases in which it is appropriate to use `.cornerRadius.` These include corner rounding cases in which there is  movement both through and underneath the corner. For certain animations, this is impossible to avoid. However, in other situations is is advisable to consider adjusting your design to eliminate one of the sources of movement. We will discuss one case later on in this post.

It is much less bad, and okay as a shortcut, to use `.cornerRadius.` for screens in which _nothing_ moves. However, any motion on the screen, even movement that doesn't involve the corners, will cause the `.cornerRadius.` perfromance tax. Additionally, any type of screen refresh will incur the cost of corner rounding. 

## Performant Corner Rounding Strategies

The ideal corner rounding strategy will depend on whether there is movement _through_ and/or _underneath_ the corner.  The following image shows movement through the corner highlighted in orange and movement underneath the corner highlighted in blue. 

**Movement underneath the corner** is defined as any movement behind the corner. For example, as a rounded-corner collection cell scrolls over a background, the background will move underneath and out from under the corners.  

To describe **movement through the corner,** imagine a small rounded-corner scroll view containing a much larger photo. As you zoom and pan the photo, the photo will move through the corners of the of the scroll view.  

<img src="/static/corner-rounding/corner-rounding-movement.PNG" width="60%" height="60%">

Note that there can be movement inside of the rounded-corner object, without moving through the corner. In the image below, you can visualize how content scrolling through the green zone will not move through the corners. Adjusting your design to eliminate one source of corner movement can make the difference between being forced to use `.cornerRadius.` versus a more optimal performance method. 

<img src="/static/corner-rounding/corner-rounding-scrolling.PNG">

### Baked-in Corners

Baked-in corners refer to corners drawn using bezier paths, thus the corners are "baked in" to the single CALayer. There are two types of baked-in corners. 

The best, most efficient method is to use **opaque corners**.  This method involves zero blending, as the corners are on a single layer that requires no offscreen rendering. Unfortunately, this method is less flexible as the background behind the rounded corners will need to be a solid color in order for the rounded corner item to move around on top of it. 

The second method involves usins bezier paths with **alpha corners** (`[path clip]`). This method is the most flexible, but incurs the cost of alpha blending the _full_ thing. This method is still way better than cornerRadius and equivocal / slightly better than clip corners (will swap places depending on device - GPU / CPU thing).

AsyncDisplayKit offers a variety of class methods to create flat-colored, rounded-corner resizable images using Baked-in Corners (Alpha + Opaque). See `UIImage+ASConveniences.h` for a complete listing. 

### Clip Corner

This strategy involves placing **4 seperate opaque corners that sit on top of the content** that needs corner rounding. This method is flexible and has quite good performance. It has minor CPU overhead of 4 seperate layers, one layer for each corner. 

Clip corners applies to two main types of corner rounding situations:

<ul>
<li>Rounded corners that move on top of a single color background, so that you cannot see that it's moving around (very common)</li>
<li>Rounded corners on top of a stationary texture or photo background (tricky, but useful!)</li>
</ul>





## Rasterization and Layerbacking

Some people have suggested that using CALayer's shouldRasterize can improve the perforamnce of .cornerRadius property. Generally this is not well understood option that is generally perilous. As long as nothing causes it to re-rasterize (no movement, no tap to change color, not on a table view that moves, etc), it is okay to use. However, generally we don't encourage this because it is very easy to cause much worse performance. 

However, for people who have shi*** app architecture and use corner radius, this *can* make a meaningful difference (if )'
    * CALayer shouldRasterize in combo with corner radius CONSIDERATIONS
        * not well understood option that is generally perilous (APPLE THING)
        * as long as nothing causes it to re-Rasterize (no movement, not tap to change button color, not on a table view that moves), it’s okay
        * there are a couple cases it is okay to use
            * e.g. ONE case in Pinterest on switches - use a 3rd party thing called sevenSwitch. papers over the sevenSwitch shittyness (Scott can share his fork of the code)
        * generally don’t encourage this, because it’s very easy to cause much worse performance
        * for people who use shitty app architecture and use corner radius, this can make a meaningful difference (if you have an app that already misuses cornerRadius, you could definitely make a significant difference with some thoughtful application of rasterization). BUT pick another option if implementing something from the ground up
        * !!! Check what it does for the Parent Node - could be best technique
    * user of cornerRadius on a node (other type of rasterization - node.shouldRasterizeDescendents (UNRELATED)
        * actual view and layer of the subnode children will not be created
        * BUT .cornerRadius ===> ASDK turns this into bezier path clipping = GOOD
        * TO DO: we could make it work for parent node by doing bezier path and blocking CALayer from reading the cornerRadius property

## Corner Rounding Strategy Flowchart

Use this flowchart to guide you to the best strategy to round a set of corners.

<img src="/static/corner-rounding/corner-rounding-flowchart.PNG" alt="corner rounding strategy flowchart">
