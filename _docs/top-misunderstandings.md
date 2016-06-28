---
title: Top Misunderstandings 
layout: docs
permalink: /docs/top-misunderstandings.html
prevPage: layout-engine.html
nextPage: containers-overview.html
---

###Debugging

<ul>
<li><a href = "top-misunderstandings.html#accessing-the-node-s-view-before-it-is-loaded">Do not access a node's view before it is loaded.</a></li>
<li><a href = "top-misunderstandings.html#thread-safety-in-nodeblocks">Ensure thread safety in nodeBlocks.</a></li>
</ul>

###Concepts

<ul>
<li><a href = "top-misunderstandings.html#cell-node-reusability">ASDK does not use cell reuse.</a></li>
</ul>

###Performance
<ul>
<li><a href = "top-misunderstandings.html#calayer-s-cornerradius-property-kills-performance">If you care about performance, do not use CALayer's .cornerRadius property.</a></li>

<a href = "top-misunderstandings.html#asyncdisplaykit-does-not-support-uikit-auto-layout">ASDK does not support UIKit Auto Layout.</a></li>
</ul>


### ASCellNode Reusability
<ul>
AsyncDisplayKit does not use cell reuse, for a number of specific reasons. 
</ul>
<ul>
Instead, ASCellNodes are created for all items in the data source at initialization and last until the `ASTableNode` or `ASCollectionNode` is destroyed. Even if your data source is massive, initializing the cells up front will not impact perfromance since they are processed in batches off the main thread.
</ul>
<ul>
One side effect of not supporting cell reuse is that it eliminates the large class of bugs associated with cell reuse. 
</ul>
### Accessing the Node's view Before it is Loaded
<br>
Don't access the view or any UI kit things in init/before a good view is loaded

This is not thread safe and may crash when a node is allocated off of the main thread. For example, when using a node block, the block will be executed in the background and therefore any sub notes of the cell may also have their init methods be called in the background.

Don't access the view or any UI kit things in init/before a good view is loaded

This is not thread safe and may crash when a node is allocated off of the main thread. For example, when using a node block, the block will be executed in the background and therefore any sub notes of the cell may also have their init methods be called in the background.
<br>

## Thread Safety in nodeBlocks

Make sure not to access the indexPath directly within `nodeBlockForItemAtIndexPath:` or `nodeBlockForRowAtIndexPath:`. These methods are called on a background thread. See more discussion here...

`:attempt to insert nil object from objects[0]`

This error is most likely caused by returning Nil for a cell node. nodeForItem: and nodeBlockForItem: both must not return a nil cell node (same as UIKit, ASDK will crash on a nil cell).

One way to inadvertently do this is by accessing indexPath in the ASCellNodeBlock returned from nodeBlockForItem:. It is very important that node blocks be thread-safe. One aspect of that is ensuring that the data model is accessed outside of the node block. Therefore, it is unlikely that you should need to use the index inside of the block. 

## LayoutSpecs Are Regenerated

A node's layoutSpec gets regenerated every time layoutThatFits: is called.


### CALayer's .cornerRadius Property Kills Performance

CALayer's' .cornerRadius property is a disastrously expensive property that should only be used when there is no alternative. It is one of the least efficient, most render-intensive properties on CALayer (alongside shadowPath, masking, borders, etc). These properties trigger offscreen rendering to perform the clipping operation on every frame — 60FPS during scrolling! — even if the content in that area isn't changing. 

Using `.cornerRadius` will visually degraded performance on iPhone 4, 4S, and 5 (along with comparable iPads / iPods).

For a longer discussion and alternative solutions, please read our comprehensive <a href = "corner-rounding.html">corner rounding guide</a>. 

### AsyncDisplayKit does not support UIKit Auto Layout

UIKit Auto Layout is not supported by AsyncDisplayKit, because it does not meet our performance bar. 

However, AsyncDisplayKit's <a href = "automatic-layout-basics.html">Layout API</a> provides a variety of <a href = "automatic-layout-containers.html">ASLayoutSpec objects</a> that allow implementing automatic layout which is more efficient (multithreaded, off the main thread), easier to debug (can step into the code and see where all values come from, as it is open source), and reusable (you can build composable layouts that can be shared with different parts of the UI).

It is worth noting that using UIKit Autolayout is not permitted in large / experienced iOS development environments, including Facebook, Instagram, and Pinterest because it is too computationally inefficient and difficult to debug.

Because of the way that UIKit auto layout is implemented, it actually prevents all major UI frameworks for iOS from integrating with it. So, the story is the same with React Native and ComponentKit.