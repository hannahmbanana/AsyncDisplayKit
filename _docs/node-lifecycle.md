---
title: Node Lifecycle 
layout: docs
permalink: /docs/node-lifecycle.html
prevPage: intelligent-preloading.html
nextPage: layout-engine.html
---

To best understand this section, we reccommend that you first become familiar with the concept of <a href = "intelligent-preloading.html">Intelligent Preloading</a>. 

### Initialization through First Appearance

These methods are called on a node, in the following order, as it goes from initialization through its _first_ time onscreen:

1. `-init`  can occur on **any thread**.

2. `-layoutSpecThatFits:`  can occur on **any thread**. 

3. `-fetchStateDidChange:YES`* will occur on the **main thread**. The node has now entered the Fetch Data Range in which content is gathered from an external source, whether that’s some API or a local disk.

4. `-displayStateDidChange:YES`* and `-didLoad` are called roughly at the same time. These methods occur on the **main thread.** The node has now entered the Display Range in which display tasks such as text rasterization and image decoding take place.

5. `-layout` will occur on the **main thread**.

6. `-visibilityDidChange:YES`* The node is now onscreen.

\* These methods are associated with the concept of <a href = "intelligent-preloading.html">Intelligent Preloading</a>. 

### Updates after First Appearance

####Example 1 (WIP)

<-- _Let's say we change the attributedText of an onscreen ASTextNode from on word to a full sentence. Changing the attributedText will cause an asynchronous layout pass to draw the new contents. As with UIKit, this layout change will bubble up the tree. 

Doing something like setAttributedText, in the process calls both setNeedsLayout and setNeedsDisplay for this particular example. SetNeedsLayout: if the node is in display range. SetNeedsDisplay will trigger a asynchronous display pass. If the node is not in the display range, then the next time it enters the display range, it will perform that display operation. 
setNeedsLayout will result in the layoutSpecThatFits: for some of the parents to calculate and adapt to the new size of the node. Layout will get called afterwards._

####Example 2 (WIP)

_Add a graphic to describe this

Scrolling offscreen, out of display range, out of the fetch data range and back.

Just onscree with new text set on it. 

Updating layout or display

E.g. ASTextNode, change attributedText after it is onscreen. Causes an asynchronous layout pass to draw the new contents. 

changes the layout of the things above it (bubbles up the tree). Longer text_ -->

### End of Life

- `-dealloc` occurs on the **main thread**. We would like to soon offer the option to do deallocation on a background thread, so it would be wise, when writing your code, to treat this as if it is on a background thread.