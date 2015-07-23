# htgen

Generator of hypertorus Petri net models


Description:
------------

A hypertorus is obtained from a hypercube via closing (connecting) opposite facets in each dimension. 
Each cell represents a packet switching device with ports situated on facets of the unit-sized hypercube.
A device works in full-duplex mode based on store-and-forward principle with limited capacity of buffer.
Neighboring cells are connected via merging contact places situated on common facets. 


Command line format:
--------------------

>htgen d k p b > ht_model.net


Parameters:
-----------

d   the number of dimensions;
k   the hypertorus size, actually k x k x k x ... x k - d times;
p   the number of packets in each section of the internal buffer;
b   the internal buffer available sise.


Output (file) format:
---------------------

.net  Time Petri nets textual format according to www.laas.fr/tina


Tools to display, edit, visualize, and analyse generated models:
----------------------------------------------------------------

Tina Toolbox for analysis of Petri nets and Time Petri nets www.laas.fr/tina

Exported from Tina in .pnml format models are opened with other tools for Petri nets.


An example:
-----------

>htgen 3 2 1 6 > ht3d2k1p6b.net

- Generate a model a hypertorus with 3 dimensions of size 2 with 1 packets in each buffer section and 
available size of buffer 6.

>nd ht3d2k1p6b.net

- Load the model into graphical environment of Tina. 

Menue: "Edit - Draw - Nearto"

- Visualize the model. 

Menue: "Tools - Reachability Analysis - Marking Graph"

- Build the marking graph.


References:
-----------

Zaitsev D.A., Shmeleva T.R. Hypercube communication structures analysis via parametric Petri nets.
Proceedings of 24th UK Performance Engineering Workshop (UKPEW 2008), 3-4 July 2008. 
http://ukpew.org/2008/papers/hypercube-petri-nets

Zaitsev D.A. Generators of Petri Net Models. Computer Communication & Collaboration, Vol. 2, Issue 2, 2014, 12-25. 
http://www.bapress.ca/ccc/ccc2014_2/2_14011024.pdf

Zaitsev D.A. Verification of Computing Grids with Special Edge Conditions by Infinite Petri Nets, 
Automatic Control and Computer Sciences, 2013, Vol. 47, No. 7, pp. 403–412. DOI: 10.3103/S0146411613070262 


------------
daze@acm.org
------------




