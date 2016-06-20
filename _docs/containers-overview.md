---
title: Containers Overview
layout: docs
permalink: /docs/containers-overview.html
prevPage: top-misunderstandings.html
nextPage: containers-asviewcontroller.html
---
### Use Nodes in Node Containers

For maximum performance, it is highly recommended that you use AsyncDisplayKit's nodes within a node container. AsyncDisplayKit offers the following node containers:

- <a href = "containers-asviewcontroller.html">`ASViewController`</a> in place of UIKit's `UIViewController`
- <a href = "containers-ascollectionnode.html">`ASCollectionNode`</a> in place of UIKit's `UICollectionView`
- <a href = "containers-aspagernode.html">`ASPagerNode`</a> in place of UIKit's `UIPageViewController`
- <a href = "containers-astablenode.html">`ASTableNode`</a> in place of UIKit's `UITableView`
 
Example code and specific sample projects are highlighted in the documentation for each node container. 

For a detailed description on porting an existing UIKit app to AsyncDisplayKit, read the <a href = "porting-guide.html">porting guide</a>.

### What do I Gain by Using a Node Container?

A node container automatically manages the <a href = "intelligent-preloading.html">intelligent preloading</a> of its nodes. This means that all of the node's layout measurement, data fetching, decoding and rendering will be done asynchronously. Among other conveniences, this is why it is reccomended to use nodes within a container node.

Note that while it _is_ possible to use nodes directly without an AsyncDisplayKit node container, unless you add additional calls, they will only start displaying once they come onscreen (_as UIKit does_). This can lead to performance degredation and flashing of content.
