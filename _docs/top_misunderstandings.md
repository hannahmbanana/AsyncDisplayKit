---
title: Top Misunderstandings 
layout: docs
permalink: /docs/top-misunderstandings.html
prevPage: layout-engine.html
nextPage: containers-overview.html
---

### Cell Node Reusability

ASCellNodes are not reusable because they are created for all items in the data source at initialization* and last until the table node or collection node is destroyed.

They are processed in batches off the main thread. 

