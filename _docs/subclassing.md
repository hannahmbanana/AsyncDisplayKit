---
title: Subclassing 
layout: docs
permalink: /docs/subclassing.html
prevPage: intelligent-preloading.html
nextPage: layout-engine.html
---

While subclassing nodes is similar to writing a UIView subclass, there are a few guidelines to follow to ensure both that you're utilizing the framework to its full potential and that your nodes behave as expected.

## Common Override Methods

## `-init`

More often than not, you'll write some kind of init method that calls `[super init]` and then create and configures all of your subnodes.  The most important thing to remember is that ***your init method must be capable of being called on any queue.*** Most notably, ***never initialize any UIKit objects or access / configure the node's view property*** in your initializer. Instead, use `didLoad` to call into UIKit!  

Good Intializer Example (ASViewController):

<div class = "highlight-group">
<span class="language-toggle"><a data-lang="objective-c" class = "active objcButton">Objective-C</a></span>
<div class = "code">
	<pre lang="objc" class="objc">
- (instancetype)init
{
  _tableNode = [[ASTableNode alloc] init];
  self = [super initWithNode:_tableNode];
  
  if (self) {
      
    _tableNode.dataSource = self;
    _tableNode.delegate = self;
    
    _textNode = [[ASTextNode alloc] init];
    _textNode.backgroundColor = [UIColor redColor];   // UIColor is the one UIKit class that can be in init:
    
    [self addSubnode:_textNode];
  }
  return self;
}
	</pre>
</div>
</div>

Bad Intializer Example (ASViewController):

<div class = "highlight-group">
<span class="language-toggle"><a data-lang="objective-c" class = "active objcButton">Objective-C</a></span>
<div class = "code">
	<pre lang="objc" class="objc">
- (instancetype)init
{
  _tableNode = [[ASTableNode alloc] init];
  self = [super initWithNode:_tableNode];
  
  if (self) {
      
    _tableNode.dataSource = self;
    _tableNode.delegate = self;
    
    _textNode = [[ASTextNode alloc] init];
    _textNode.backgroundColor = [UIColor redColor];  
    _textNode.view.SOMETHING = SOMETHING             // BAD: accessing a node's view in init:
    [self addGestureRecognizer:_tgr];                // BAD: adding a gesture recognizer in init:
    
    [self addSubnode:_textNode];
  }
  return self;
}
	</pre>
</div>
</div>

## `-didLoad` (Nodes) & `-loadView` (ASViewController)

This method is similar to UIViewController's `-viewDidLoad` method and is the point where the backing view has been loaded.  It is guaranteed to be called on the main thread and is the appropriate place to set up an UIKit objects you may be using.

## `-layoutSpecThatFits:`

This method is where you build out a layout spec object that will produces the size of the node, as well as the size and position of all subnodes.  

The layout spec object that you create is maleable up until the point that it is return in this method.  After this point, it will be immutable.  It's important to remember not to cache layout specs for use later but instead to recreate them when necessary.

Avoid allocating nodes here (possible, but not ideal).

## `-layout`

Right after the call to super in this method, the layout spec will have been calculated and all subnodes will have been measured and positioned.  

This is a good place to manually layout subviews if you happen to be using them for some reason.  Maybe more useful is the instances where you want to create a layout that isn't easily created via a layout spec.  Sometimes it's easier to wait until most subnodes are laid out and just set a frame manually.  If that's the case, this is the place to do it.