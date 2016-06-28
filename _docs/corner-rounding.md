---
title: Corner Rounding
layout: docs
permalink: /docs/corner-rounding.html
prevPage: drawing-priority.html
nextPage: hit-test-slop.html
---

If you’ve worked with Scott Goodson before, you’ll know that one of his pet peeves is use of CALayer’s "disasterously inefficient" .cornerRadius property. This post will cover

<ul>
<li>why you shouldn’t use CALayer’s .cornerRadius if you care about performance.*</li>
<li>acceptable corner round strategies & and when to use them</li>
<li>a flow chart for choosing your ideal corner rounding strategy</li>
</ul>

## CALayer's .cornerRadius is Expensive

## Performant Corner Round Strategies

### Types of Corner Movement

The type of corner rounding strategy you pick for a corner will depend on the type of movement through and underneath the corner. 

####Movement Through the Corner

If you think of the rounded object as a window with rounded corners, the movement in the "window" would be movement through the corner. 

Note: stuff can move inside the corner, but as long as it doesn't touch the corner, it is okay. 

- stocks app
- zooming in on a photo in a rounded node

####Movement Underneath the Corner

This is movement from underneath (or behind) the corner. 

This example shows an rounded, ASTextNode with photos scrolling underneath it. 

### Clip Corner

This strategy involves placing **4 seperate opaque corners that sit on top of the content** that needs corner rounding. This method is flexible and has quite good performance. It has minor CPU overhead of 4 seperate layers, one layer for each corner. 

Clip corners applies to two main types of corner rounding situations:

<ul>
<li>Rounded corners that move on top of a single color background, so that you cannot see that it's moving around (very common)</li>
<li>Rounded corners on top of a stationary texture or photo background (tricky, but useful!)</li>
</ul>

### Baked-in Corners (Alpha & Opaque)

Baked-in corners refer to corners drawn using bezier paths. There are two ways to do baked-in corners. 

The best, most efficient method is to use opaque corners. This involves zero blending, only one layer with no offscreen rendering. Unfortunately, this method is less flexible as you neeed a solid background to move around on. 

The second method involves usins bezier paths with alpha (`[path clip]`). This method is the most flexible, but incurs the cost of alpha blending the _full_ thing. This method is still way better than cornerRadius and equivocal / slightly better than clip corners (will swap places depending on device - GPU / CPU thing).

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

To wrap this all up, here's a flowchart to guide you to the best strategy for a particular set of rounded corner. 

<img src="/static/corner-rounding-flowchart.PNG" alt="corner rounding strategy flowchart">