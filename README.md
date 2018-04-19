# Edge Disjoint Partitioning (EDP)

> Reproducing the SIGMOD paper "Graph Indexing for Shortest-Path Finding over Dynamic Sub-Graphs"

## Compilation

This code is written in C++, make sure you have a C++ compiler (e.g. `g++`, `clang++`, etc.).

To compile the program, just go into `src` directory and do

```bash
$ make
```

It will generate 2 executables, `edp_main` is used for the experiments while `edp_test` is for debugging.

## Running experiments

After compilation, just do (inside `src`)

```bash
$ ./edp_main /path/to/graph <number-of-labels> <number-of-vertices> > output.txt
```

This writes the index size after each query to the file `output.txt`. For example,

```bash
$ ./edp_main ../datasets/youtube_subset.txt 5 2000 > output.txt
```

## Datasets

Below are some details for the dataset we used.

### Subset of Youtube

- Directed graph
- |V|: 1940
- |E|: 290234
- Number of labels: 5

### Subset of Biogrid

- Undirected graph
- |V| = 8783
- |E| = 199009
- Number of labels = 7

### String

- Unidrected graph
- |V| = 4458
- |E| = 161367
- Number of labels = 6
