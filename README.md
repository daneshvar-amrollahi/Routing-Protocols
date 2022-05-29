## Routing-Protocols
We simulated two routing protocols, distance vector and link state, as a computer assignment for computer networks course.

## How to run
run the following commands in terminal:
```
make
./main.out
```

## Commands

### topology
With this command, you can define a new topology. this definition includes the nodes and the edges. the format is as follows:

```
topology s1-d1-c1 s2-d2-c2 ...
```
where $s_n$ and $d_n$ are nodes and $c_n$ is the cost of the edge that connects them. note that the graph is undirected. example:
```
topology 1-2-19 1-3-9 2-4-3
```

### show
This commant prints the adjacency matrix of the graph. the number on row $i$ and column $j$ shows the cost of the edge from $i$ to $j$, this number would be $-1$ if no edge connects $i$ and $j$. the format is as follows:
```
show
```
sample output:
```
u|v |   1|   2|   3|   4|
-------------------------
   1|   0|  19|   9|  -1|
   2|  19|   0|  -1|   3|
   3|   9|  -1|   0|  -1|
   4|  -1|   3|  -1|   0|
```

### remove
This command removes the edge between two nodes. the format is as follows:
```
remove s-d
```
where $s$ and $d$ are the nodes whose connection we want to remove. example:
```
remove 1-3
```

### modify
This command modifies the cost of an edge. if no edge exists between given nodes, a new one will be created. the format is as follows:
```
modify s-d-c
```
where $(s,d)$ is the edge we want to change and $c$ is the new cost. example:
```
modify 1-3-4
```

### lsrp
This command runs the link state routing protocol on the network for a given node and prints the nodes table after each iteration. the final tables shows the shortest path from given node to all nodes in network. the format is as follows:
```
lsrp s
```
where s is the source node. example:
```
lsrp 1
```
output:
```
   |Iter 1:
Dest|   1|   2|   3|   4|
Cost|   0|  19|   9|  -1|
-------------------------
   |Iter 2:
Dest|   1|   2|   3|   4|
Cost|   0|  19|   9|  -1|
-------------------------
   |Iter 3:
Dest|   1|   2|   3|   4|
Cost|   0|  19|   9|  22|
-------------------------

Path: [s] -> [d]         Min-Cost         Shortest Path
---------------------------------------------------------
    [1] -> [2]              19             1 -> 2
    [1] -> [3]              9              1 -> 3
    [1] -> [4]              22             1 -> 2 -> 4
```

### dvrp
This command runs the distance vector routing protocol on the network for a given node. the printed tables shows the shortest path from given node to all nodes in network. the format is as follows:
```
dvrp s
```
where s is the source node. example:
```
dvrp 1
```
output:
```
Dest         NextHop         Dist         Shortest Path
---------------------------------------------------------
2              2              19          1 -> 2
3              3              9           1 -> 3
4              2              22          1 -> 2 -> 4
```