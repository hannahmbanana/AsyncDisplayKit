---
title: Node Subclassing 
layout: docs
permalink: /docs/subclassing.html
prevPage: intelligent-preloading.html
nextPage: layout-engine.html
---

While subclassing nodes is similar to writing a UIView subclass, there are a few guidelines to follow to ensure both that you're utilizing the framework to its full potential and that your nodes behave as expected.

<ul>
<li><a href = "subclassing.html#common-override-methods">Common override methods and what to include in each</a></li>
<li><a href = "subclassing.html#which-thread-am-i-on">Which thread is this method on?</a></li>
</ul>

## Common Override Methods
## `-init`

More often than not, you'll write some kind of init method that calls `[super init]` and then create and configures all of your subnodes.  The most important thing to remember is that ***your init method must be capable of being called on any queue.***  Most notably, never do any of the following in `-init`:
<ul>
  <li>initialize or access any UIKit objects</li>
  <li>configure the node's view property</li>
  <li>create or add a gesture recognizer</li>
</ul>

Instead, these operations are ideal to perform in -didLoad.

## `-didLoad`

This method is similar to UIViewController's `-viewDidLoad` method and is the point where the backing view has been loaded.  It is guaranteed to be called on the main thread and is the appropriate place to set up an UIKit objects you may be using.

## `-layoutSpecThatFits:`

This method is where you build out a layout spec object that will produces the size of the node, as well as the size and position of all subnodes.  

The layout spec object that you create is maleable up until the point that it is return in this method.  After this point, it will be immutable.  It's important to remember not to cache layout specs for use later but instead to recreate them when necessary.

Avoid allocating nodes here (possible, but not ideal). 

Note that this method can be called on any thread.

## `-layout`

Right after the call to super in this method, the layout spec will have been calculated and all subnodes will have been measured and positioned.  

This is a good place to manually layout subviews if you happen to be using them for some reason.  Maybe more useful is the instances where you want to create a layout that isn't easily created via a layout spec.  Sometimes it's easier to wait until most subnodes are laid out and just set a frame manually.  If that's the case, this is the place to do it.

This method is called on the main thread.

## Which Thread am I on?

All ASViewController actions and methods are called on the main thread.

The following node methods are called on the **main thread** only:

- `-didLoad`
- `-layout`
- `-dealloc`\*
- all Interface State Change methods, including `-fetchStateDidChange:`\*, `displayStateDidChange:`\*, and `-visibilityDidChange:` 

\* We would like to soon offer the option to call these methods on a background thread. So it would be wise, when writing your code, to treat this as if it is on a background thread._

The following node methods can be called on **any thread**:

- `-init`
- `-layoutSpecThatFits:`