---
title: LayoutSpecs
layout: docs
permalink: /docs/automatic-layout-containers.html
prevPage: automatic-layout-basics.html
nextPage: automatic-layout-examples.html 
---

### Layoutable Properties

The following properties can be applied to both nodes _and_ layoutSpecs. Both conform to the <ASLayoutable> protocol. 

### ASStackLayoutable Properties

The following properties will only apply to a child wrapped in an *stack* layoutSpec.

<table style="width:100%"  class = "paddingBetweenCols">
  <tr>
    <th>Property</th>
    <th>Description</th> 
  </tr>
  <tr>
    <td><b>.spacingBefore</b></td>
    <td>Additional space to place before this object in the stacking direction.</td> 
  </tr>
  <tr>
    <td><b>.spacingAfter</b></td>
    <td>Additional space to place after this object in the stacking direction.</td> 
  </tr>
  <tr>
    <td><b>.flexGrow</b></td>
    <td> </td> 
  </tr>
  <tr>
    <td><b>.flexShrink</b></td>
    <td> </td> 
  </tr>
  <tr>
    <td><b>.flexBasis</b></td>
    <td> Specifies the initial size for this object, in the stack dimension (horizontal or vertical), before the flexGrow or flexShrink properties are applied and the remaining space is distributed.  <img src="/static/layoutable-properties/flex-basis.png"> </td> 
  </tr>
  <tr>
    <td><b>.ascender</b></td>
    <td> </td> 
  </tr>
  <tr>
    <td><b>.descender</b></td>
    <td> </td> 
  </tr>
</table> 




AsyncDisplayKit includes a library of `layoutSpec` components that can be composed to declaratively specify a layout. 

**The child(ren) of a layoutSpec may be a node or another layoutSpec.**  Both nodes and layoutSpecs conform to the <ASLayoutable> protocol.  Any `ASLayoutable` object may be the child of a layoutSpec. 

### Single Child layoutSpecs

<table style="width:100%"  class = "paddingBetweenCols">
  <tr>
    <th>Component</th>
    <th>Description</th> 
  </tr>
  <tr>
    <td><b>ASLayoutSpec</b></td>
    <td>can be used as a spacer if it contains no child.</td> 
  </tr>
  <tr>
    <td><b>ASInsetLayoutSpec</b></td>
    <td>applies an inset margin around a component. </td> 
  </tr>
  <tr>
    <td><b>ASBackgroundLayoutSpec</b></td>
    <td>lays out a component, stretching another component behind it as a backdrop. </td> 
  </tr>
  <tr>
    <td><b>ASOverlayLayoutSpec</b></td>
    <td>lays out a component, stretching another component on top of it as an overlay.</td> 
  </tr>
  <tr>
    <td><b>ASCenterLayoutSpec</b></td>
    <td>centers a component in the available space. </td> 
  </tr>
  <tr>
    <td><b>ASRatioLayoutSpec</b></td>
    <td>lays out a component at a fixed aspect ratio (which can be scaled). Great for images, gifs and videos. </td> 
  </tr>
  <tr>
    <td><b>ASRelativeLayoutSpec</b></td>
    <td>lays out a component and positions it within the layout bounds according to vertical and horizontal positional specifiers. Similar to the “9-part” image areas, a child can be positioned at any of the 4 corners, or the middle of any of the 4 edges, as well as the center. </td> 
  </tr>
</table> 

### Multiple Child(ren) layoutSpecs

<table style="width:100%" class = "paddingBetweenCols">
  <tr>
    <th>Component</th>
    <th>Description</th> 
  </tr>
  <tr>
    <td><b>ASStackLayoutSpec</b></td>
    <td>is based on a simplified version of CSS flexbox. It allows you to stack components vertically or horizontally and specify how they should be flexed and aligned to fit in the available space.</td> 
  </tr>
  <tr>
    <td><b>ASStackLayoutSpec</b></td>
    <td>is based on a simplified version of CSS flexbox. It allows you to stack components vertically or horizontally and specify how they should be flexed and aligned to fit in the available space. </td> 
  </tr>
  <tr>
    <td><b>ASStaticLayoutSpec</b></td>
    <td>allows positioning children at fixed offsets. </td> 
  </tr>
</table>

### LayoutSpec Strategy

<img src="/static/layoutspec-breakdown.png">



### Best Practices

- don't wrap everything in a staticLayoutSpec
- avoid using preferred frame size for everything - won't respond nicely to device rotation or device sizing differences 


