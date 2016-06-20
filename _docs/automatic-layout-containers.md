---
title: Layout Containers
layout: docs
permalink: /docs/automatic-layout-containers.html
prevPage: automatic-layout-basics.html
nextPage: automatic-layout-examples.html 
---

AsyncDisplayKit includes a library of components that can be composed to declaratively specify a layout. **LayoutSpecs can 

The following layoutSpecs allow you to **configure multiple children**:

<table style="width:100%">
  <tr>
    <th>Component</th>
    <th>Description</th> 
  </tr>
  <tr>
    <td>**ASStackLayoutSpec**</td>
    <td>is based on a simplified version of CSS flexbox. It allows you to stack components vertically or horizontally and specify how they should be flexed and aligned to fit in the available space.</td> 
  </tr>
</table>



* **ASStackLayoutSpec** is based on a simplified version of CSS flexbox. It allows you to stack components vertically or horizontally and specify how they should be flexed and aligned to fit in the available space. 
* **ASStaticLayoutSpec** allows positioning children at fixed offsets.

The following layoutSpecs allow you to **configure a single child**: 

* **ASLayoutSpec** can be used as a spacer if it contains no children
* **ASInsetLayoutSpec** applies an inset margin around a component.
* **ASBackgroundLayoutSpec** lays out a component, stretching another component behind it as a backdrop.
* **ASOverlayLayoutSpec** lays out a component, stretching another component on top of it as an overlay.
* **ASCenterLayoutSpec** centers a component in the available space.
* **ASRatioLayoutSpec** lays out a component at a fixed aspect ratio. Great for images, gifs and videos.
* **ASRelativeLayoutSpec** lays out a component and positions it within the layout bounds according to vertical and horizontal positional specifiers. Similar to the “9-part” image areas, a child can be positioned at any of the 4 corners, or the middle of any of the 4 edges, as well as the center.

##Strategy
