---
title: Corner Rounding
layout: docs
permalink: /docs/corner-rounding.html
prevPage: drawing-priority.html
nextPage: hit-test-slop.html
---

If you’ve worked with Scott Goodson before, you’ll know one of his pet peeves is use of CALayer’s "disasterously inefficient" .cornerRadius property. This post will cover

<ul>
<li>why you shouldn’t use CALayer’s .cornerRadius if you care about performance.*</li>
<li>acceptable corner round strategies & and when to use them</li>
<li>a flow chart for choosing your ideal corner rounding strategy</li>
</ul>

##

## 


## Performant Corner Rounding Flowchart

To wrap this all up, here's a flowchart to guide you to the best strategy for a particular set of rounded corner. 

<img src="/static/corner-rounding-flowchart.png" alt="corner rounding strategy flowchart">