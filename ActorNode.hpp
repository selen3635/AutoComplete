#include <iostream>
#include <limits>
#include <vector>

using namepace std;

struct Vertex
{
  // The adjacency list
  vetor<int> adj;

  // The distance from the source
  int dist;

  // The index of this vertex
  int index;

  // The index of the vertex previous in the path
  int prev;

} myStruct;

vector<Vertex*> createGraph;

/** Traverse the graph using BFS */
void BFSTraverse( vector<Vertex*> theGraph, int from);
