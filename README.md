# I-Contractible graphs
In this repository is shown how to implement the algorithms used in the article [Collapsibility and homological properties of I-contractible transformations](https://arxiv.org/abs/1808.07461), as well as in the work [Minimal graphs for contractible and dismantlable properties](https://arxiv.org/abs/2109.06729).

The following commands were executed under the operative system Debian GNU/Linux 11 and compiler `gcc (Debian 10.2.1-6) 10.2.1 20210110`. However, a graphical compiler like [this one](https://www.embarcadero.com) can be used.

## Connected graphs
The workflow starts generating the family of connected graphs. To perform this task, can be used the script [Connected_graphs.cpp](./Connected_graphs.cpp). Execute in the command line the following:
```
gcc Connected_graphs.cpp -o Connected_graphs
./Connected_graphs
```
The output of the program (executable) `Connected_graphs` consist of 9 text files: `CG_num_1.txt`, ..., `CG_num_9.txt`. Such files can be found in the directory [Connected-graphs](./Connected-graphs).

Each of these files contains a list of connected graphs, one file for each group of graphs with the same number of vertices, as well as an id for each connected graph and a condensed representation of its adjacency matrix. For example, at the beginning of the file [CG_num_7.txt](./Connected-graphs/CG_num_7.txt) can be found the following:
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
It means that there are 11 connected graphs with 7 vertices and 6 edges. The numbers from 144 to 154 at the first column indicates the number assigned (**id**) to each connected graph by the script `Connected_graphs.cpp`, and each number at the left (second column) indicates the number in base 10 of the upper triangular part of its adjacency matrix as follow: _For example, for the graph with id 154, its number is 1080320, which in base 2 is 100000111110000000000; then, for a graph on 7 vertices, such upper triangular part of the adjacency matrix is:_
```
1 0 0 0 0 0
  1 1 1 1 1 
    0 0 0 0 
      0 0 0
        0 0 
          0
```
Hence, the adjacency matrix is:
```
0 1 0 0 0 0 0
1 0 1 1 1 1 1 
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
```
Actually, the computation made by `Connected_graphs.cpp` performs a relabeling of the vertices on each graph in such a way that the formed binary number (as we explained before) is maximal with respect to the lexicographic order.

On the other hand, the adjacency matrices of the connected graphs in the files `CG_num_1.txt`, ..., `CG_num_9.txt` can be generated with the script `CG_num_to_AdjacencyMatrix.cpp`:
```
gcc CG_num_to_AdjacencyMatrix.cpp -o CG_num_to_AdjacencyMatrix
./CG_num_to_AdjacencyMatrix
```
The output of such execution can be found also in [Connected-graphs](./Connected-graphs), under the names: `CG_AM_1.txt`, ..., `CG_AM_9.txt`. For example, for the graph with id 154 in the file [CG_AM_7.txt](./Connected-graphs/CG_AM_7.txt) described before, we have:
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
The definition of the class of _strong vertex I-contractible graphs_ can be found in the papers pointed out at the beginning of this document.

To verify which of the connected graphs in `CG_AM_1.txt`, ..., `CG_AM_9.txt` is strong vertex I-contractible, execute the following:
```
gcc Contractible_graphs.cpp -o Contractible_graphs -lm
./Contractible_graphs
```
Such script makes an exhaustive search in the files `CG_AM_1.txt`, ..., `CG_AM_9.txt`, looking for a collapsible graph but not a strong vertex I-contractible. No graph with such characteristics were found.

## Reduced graphs by I-contractible transformations
As was stated in [Collapsibility and homological properties of I-contractible transformations](https://arxiv.org/abs/1808.07461) (_Algorithm 2_), the algorithm `Contractible_reduction` developed in the script ``Contractible_reduction`.cpp` reduce the 'strong vertex I-contractible' vertices in order to obtain another graph, with less vertices and edges but the same homotopy type (and same homology groups). Generate the executable as follows:
```
gcc Contractible_reduction.cpp -o Contractible_reduction
./Contractible_reduction
```
Execute the program `Contractible_reduction` in the same directory as the file `graph.txt`, in which an adjacency matrix is stored. For example, can be used the file [graph.txt](./Examples/graph.txt), which contains a graph on 140 vertices.

The output of the program `Contractible_reduction` is a list of the vertices that remain after deleting the strong vertex I-contractible ones:
```
100 104 110 117 121 129 131 133 134 140
```
At the left in the next picture is the original graph, and at the right the reduced one:

![image](https://user-images.githubusercontent.com/81319528/165278908-6b3b78e8-16e9-4840-8623-59f33b791744.png)

## Application to topological data analysis
In the following animations is shown how the reduced graphs, from a family of graphs in a filtration, look like after the contractible reductions. Such filtered graphs and its clique complexes correspond to the filtered Vietoris-Rips complex commonly used in topological data analysis.

https://user-images.githubusercontent.com/81319528/165279252-9696b62e-87dd-4db2-88d4-6de667ece0d3.mp4


https://user-images.githubusercontent.com/81319528/165279284-bfc1f690-c1b1-420e-9a8f-f90ed2bec3c4.mp4
