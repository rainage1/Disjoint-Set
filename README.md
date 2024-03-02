# Disjoint-Set
Disjoint-Set data structure in C++. Included is also an algorithm to find the connected components in a binary image using the Disjoint-Set data structure. 
File infile contains a 72 by 75 binary image 
in plain text.

In this file, a + means 1 and a space means 0.
We only consider the connected components of 1.

The total number of components is less than 26.
Therefore you can use letters from 'a' to 'z' to
identify all the components.

We use 8 connectivity for +.

Therefore ++ and + are considered connected,
                 +

and +  and  + are also considered connected.
     +     +
