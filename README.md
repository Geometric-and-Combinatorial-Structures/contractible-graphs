# I-Contractible graphs
In this repository we demonstrate how to implement the algorithms employed in the article [Collapsibility and homological properties of I-contractible transformations](https://arxiv.org/abs/1808.07461), as well as in the work [Minimal graphs for contractible and dismantlable properties](https://arxiv.org/abs/2109.06729).

The following commands were executed using the operating system Debian GNU/Linux 11 and compiler `gcc (Debian 10.2.1-6) 10.2.1 20210110`. However, a graphical compiler such as [this one](https://www.embarcadero.com) can also be used.

## Connected graphs
The workflow begins by generating the family of connected graphs. To perform this task, one can use the script [Connected_graphs.cpp](./Connected_graphs.cpp). To execute one should enter the following in the command line:
```
gcc Connected_graphs.cpp -o Connected_graphs
./Connected_graphs
```
The output of the program (executable) `Connected_graphs` consists of 9 text files: `CG_num_1.txt`, ..., `CG_num_9.txt`. These files can be found in the directory [Connected-graphs](./Connected-graphs).

Each of these files contains a list of connected graphs, one file for each collection of graphs with the same number of vertices. In addition, each graph is given a numerical id along with a condensed representation of its adjacency matrix. For example, at the beginning of the file [CG_num_7.txt](./Connected-graphs/CG_num_7.txt) can be found the following:
```
11
7 6

144 1065509
145 1065510
146 1065516
147 1065528
148 1065584
149 1066544
150 1065633
151 1065696
152 1065920
153 1066880
154 1080320
...
```
We see that there are 11 connected graphs with 7 vertices and 6 edges. The numbers from 144 to 154 in the first column indicate the number assigned (**id**) to each connected graph by the script `Connected_graphs.cpp`, and each number in the second column indicates the number (in base 10) of the upper triangular part of its adjacency matrix as follows: _For example, for the graph with id 154, the number is 1080320, which in base 2 is 100000111110000000000; hence for this graph on 7 vertices, the upper triangular part of the adjacency matrix is given by:_
```
1 0 0 0 0 0
  1 1 1 1 1 
    0 0 0 0 
      0 0 0
        0 0 
          0
```
Hence, the adjacency matrix is given by:
```
0 1 0 0 0 0 0
1 0 1 1 1 1 1 
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
```
In fact, the computation performed by `Connected_graphs.cpp` relabels the vertices of each graph in such a way that the resulting binary number (as explained above) is maximal with respect to the lexicographic order.

On the other hand, the adjacency matrices of the connected graphs in the files `CG_num_1.txt`, ..., `CG_num_9.txt` can be generated using the script `CG_num_to_AdjacencyMatrix.cpp`:
```
gcc CG_num_to_AdjacencyMatrix.cpp -o CG_num_to_AdjacencyMatrix
./CG_num_to_AdjacencyMatrix
```
The output of this execution can also be found in [Connected-graphs](./Connected-graphs), under the names: `CG_AM_1.txt`, ..., `CG_AM_9.txt`. For example, for the graph with id 154 in the file [CG_AM_7.txt](./Connected-graphs/CG_AM_7.txt) described above, we have:
```
154 7 6
0 1 0 0 0 0 0 
1 0 1 1 1 1 1 
0 1 0 0 0 0 0 
0 1 0 0 0 0 0 
0 1 0 0 0 0 0 
0 1 0 0 0 0 0 
0 1 0 0 0 0 0 
```

## Strong vertex I-contractible graphs
The definition of the class of _strong vertex I-contractible graphs_ can be found in the papers referenced to at the beginning of this document.

To determine which of the connected graphs in `CG_AM_1.txt`, ..., `CG_AM_9.txt` are strong vertex I-contractible, we execute the following:
```
gcc Contractible_graphs.cpp -o Contractible_graphs -lm
./Contractible_graphs
```
This script makes an exhaustive search through the files `CG_AM_1.txt`, ..., `CG_AM_9.txt`, looking for a collapsible graph that is not strong vertex I-contractible. No such graph was found.

## Reduced graphs by I-contractible transformations
As discussed in [Collapsibility and homological properties of I-contractible transformations](https://arxiv.org/abs/1808.07461) (_Algorithm 2_), the algorithm `Contractible_reduction` as implemented in the script `Contractible_reduction.cpp` removes the 'strong vertex I-contractible' vertices in order. In this way we obtain a graph with fewer vertices and edges, but preserve the homotopy type (and hence homology groups) of the underlying clique complexes. The executable file can be compiled from the source file as follows:
```
gcc Contractible_reduction.cpp -o Contractible_reduction
./Contractible_reduction
```
One can execute the program `Contractible_reduction` in the same directory as the file `graph.txt`, where the adjacency matrix is stored. For example, one can use the file [graph.txt](./Examples/graph.txt), which contains a graph on 140 vertices.

The output of the program `Contractible_reduction` is a list of vertices that remain after deleting those that are strong vertex I-contractible:
```
100 104 110 117 121 129 131 133 134 140
```
In the figure below, on the left we depict the original graph and on the right the result of applying these reductions.

![image](https://user-images.githubusercontent.com/81319528/165278908-6b3b78e8-16e9-4840-8623-59f33b791744.png)

## Application to topological data analysis
In the following animations we illustrate how the reduced graphs, from a family of graphs in a filtration, look like after the contractible reductions. Such filtered graphs and its clique complexes correspond to the filtered Vietoris-Rips complex commonly used in topological data analysis. The mathematical foundations about the compatibility of the I-contractible reductions and the computing of persistent homology was established in [Collapsibility and homological properties of I-contractible transformations](https://arxiv.org/abs/1808.07461).

https://user-images.githubusercontent.com/81319528/165279252-9696b62e-87dd-4db2-88d4-6de667ece0d3.mp4


https://user-images.githubusercontent.com/81319528/165279284-bfc1f690-c1b1-420e-9a8f-f90ed2bec3c4.mp4
