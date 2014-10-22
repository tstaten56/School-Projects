Tera Staten
tns26

Abstract:
This report is for Project 2 under Dr. Duan from 3460:435 Algorithms. This project implements Union Find an algorithm which is used for traversing a graph and seeing if there is a path from 
one node to another.
		
Introduction:
We use Union Find to see if a graph Percolates. Percolation is true if there is an open path from the top of the graph to the bottom of the graph. Similar to having a medium and trying to see
if water can get from the top of the medium to the bottom of the medium, if it can the system percolates.
 
Previous Work:
There is no previous work that I have done before this project.

Novel aspects of own work:
This project starts off generating a square graph with blocked nodes based on size s. Then it unblocks nodes based on percolation probability p, which is always between 0 and 1. Then my 
implementation builds a tree based on the unblocked square graph, this tree is an array which keeps track of the parent relationships. The parent relationships are shortened as much as
possible to speed up the program. Then I use union find to see if there is a path from the top of the graph to the bottom of the graph and if there is we have a graph that percolates. I then run
this same procedure n times and divide the number of graphs that percolated by n and output that number to the screen.
The exact use cases are as follows:
·       yourProgram.exe  p n s   //program will output the number of graphs that percolate divided by n times run
·       yourProgram.exe  textfile.txt   //program will see if this input file percolates or not and will also count the number of clusters in the graph

The clusters are the nodes that are "connected" to each other N/S/E/W and that are the same value (true or false). These are counted using the parent relations array. At first I had to fix my
file reading and assigning because it was skipping the first line, but once I got that fixed I could reuse the code from the first part of the project, then just implement int CountClusters()
function. It worked with Dr Duan's test cases so hopefully it works with other files too!

Conclusions:
I have learned a lot about Percolation, Union Find, and graphs. I enjoyed writing this program, even though testing was looking at lots of graphs to see if it was behaving properly! My union-
find is faster than I thought it would be! 

References/appendices:
https://www.cs.princeton.edu/courses/archive/fall10/cos226/assignments/percolation.html
