# I-Contractible graphs
Generate the connected grphs

```
gcc Connected_graphs.cpp -o Connected_graphs
./Connected_graphs
```
The output of the program `Connected_graphs` consist in 9 text files: `CG_num_1.txt`, ..., `CG_num_9.txt`.

For example, at the begining of the file CG_num_7.txt can be found the following:
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
It means that there are 11 connected graphs with 7 vertices and 6 edges. The numbers from 144 to 154 at the first column indicates the number asigned to each connected grph by our algorithm, and the number at the left (second column) indicates the number in base 10 of the upper triangular part of its adyacency matrix as follow: For example, for the graph with id 154, its number is 1080320, which in base 2 is 100000111110000000000; then, for a graph on 7 vertices, such upper triangular part of the adyacency matrix is:
```
1 0 0 0 0 0
  1 1 1 1 1 
    0 0 0 0 
      0 0 0
        0 0 
          0
```
Hence, the adyacency matrix is:
```
0 1 0 0 0 0 0
1 0 1 1 1 1 1 
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
0 1 0 0 0 0 0
```
Actually, the computation made by `Connected_graphs` performs a relabeling of the vertices for each graph, in such way that the formed binary number (as we explained before) is maximal with respect to the lexicographic order.

In order to generate the adjacency matrices of the connected graphs, we use the script `CG_num_to_AdjacencyMatrix.cpp`:
```
gcc CG_num_to_AdjacencyMatrix.cpp -o CG_num_to_AdjacencyMatrix
./CG_num_to_AdjacencyMatrix
```


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



Can be checked that the adjacency matrix with id 154 in the output file CG_AM_7.txt corresponds to the above adjacency matrix. 

The following script verify is every connected graph up to 9 vertices is strong I-contractible vertice
```
gcc Contractible_graphs.cpp -o Contractible_graphs -lm
./Contractible_graphs
```

As is mentioned in [REFERENCE], we can iterate the algorithm for reduce I-contractible vertices in order to have another graph (same homotopy type) but fewer vertices and edges. The script 

```
gcc Reduce_contractible.cpp -o Reduce_contractible
./Reduce_contractible
```
Can be used this file `graph.txt` in the same directory that `Reduce_contractible`, to obtain the fail `reduced_graph.txt` with the vertices that remain after deleting contractible vertices:
```
100 104 110 117 121 129 131 133 134 140
```
![image](https://user-images.githubusercontent.com/81319528/165278908-6b3b78e8-16e9-4840-8623-59f33b791744.png)


https://user-images.githubusercontent.com/81319528/165279252-9696b62e-87dd-4db2-88d4-6de667ece0d3.mp4


https://user-images.githubusercontent.com/81319528/165279284-bfc1f690-c1b1-420e-9a8f-f90ed2bec3c4.mp4


