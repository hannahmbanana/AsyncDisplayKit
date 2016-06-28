---
title: Layout Options
layout: docs
permalink: /docs/layout-options.html
prevPage: automatic-layout-debugging.html
nextPage: layer-backing.html
---

When using AsyncDisplayKit, you have three options for layout:


<a href = "layout-options.html#">automatic, extensible Layout API</a>

<ul>
<li>The Layout API, which is based on the CSS flexbox model, is the reccomended layout option.</li>
This is a test
<li>Manual Sizing & Layout [For a few cases in which the Layout API doesn't make sense]</li>
<li>Unified Sizing & Layout [Advanced users only]</li>
</ul>

Please note that <a href = "top-misunderstandings.html#asyncdisplaykit-does-not-support-uikit-auto-layout">UIKit Auto Layout is not supported</a>.


## Automatic, Extensible Layout (Reccomended)

This is the reccomended layout method. It does not have a UIKit analog and is implemented by calling

`- (ASLayoutSpec *)layoutSpecThatFits:(ASSizeRange)constraint`
###Advantages
- can reuse even complex, custom layouts
- built-in specs provide automatic layout
- combine to compose new layouts easily
- still async, cached, and zero duplication

The diagram below shows how options #2 and #3 above both result in an ASLayout, except that in option #3, the ASLayout is produced automatically by the ASLayoutSpec.  

<INSERT DIAGRAM>

##Manual Sizing & Layout

This original layout method shipped with ASDK 1.0 and is analogous to UIKit's layout methods. Use this method for ASViewControllers (unless you subclass the node).

`[ASDisplayNode calculateSizeThatFits:]` **vs.** `[UIView sizeThatFits:]`

`[ASDisplayNode layout]` **vs.** `[UIView layoutSubviews]`

###Advantages (over UIKit)
- Eliminates all main thread layout cost
- Results are cached

###Shortcomings (same as UIKit):
- Code duplication between methods
- Logic is not reusable

##Unified Sizing & Layout

For advanced users only, you can use this method to get some of the benefit. 

This layout method does not have a UIKit analog. It is implemented by calling

`- (ASLayout *)calculateLayoutThatFits: (ASSizeRange)constraint`

###Advantages
- zero duplication
- still async, still cached

###Shortcomings
- logic is not reusable, and is still manual


##Combining Layout Methods

The following layout methods are okay to combine:
<ul>
<li>`-layout` and `-layoutSpecThatFits:`</li>
<li>`-layout` and `-calculateSizeThatFits:`</li>
<li>`-layout` and `-calculateLayoutThatFits:`</li>
</ul>

Do **not**, however, combine any `-{*}ThatFits:` methods with any other `-{*}ThatFits:` methods.  
