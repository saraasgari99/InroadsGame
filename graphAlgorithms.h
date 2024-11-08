/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <vector>
using std::vector;

#include "adts/dictionary.h"
#include "adts/edge.h"
#include "adts/graph.h"

#include <string>
#include "adts/stlStack.h"
#include "adts/stlQueue.h"
#include "adts/stlMinPriorityQueue.h"

using namespace std;

/**
 * Returns whether vertex dest is reachable from vertex src in the graph g using
 * depth-first search.
 * @param src The source vertex.
 * @param dest The destination vertex.
 * @param g A pointer to the Graph object.
 * @return true if a path exists
 */
template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g);

/**
 * Returns the shortest length path found from the vertex src
 * to the vertex dest, using an unweighted breadth-first search of the graph.
 * @param src - source vertex
 * @param dest - destination vertex
 * @param g - pointer to Graph object
 * @return vector<V> - sequence of vertices in path from src to dest
 * @error throws runtime_error if no path exists
 */
template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g);

/**
 * dijkstra calculates the single source minimum distance to all other
 *   vertices in the graph from a src node
 * @param src - source vertex
 * @param g - pointer to Graph object to search
 * @return Dictionary<V,W> - Dictionary of vertices and their distance
 *    from src.  Only reachable vertices should appear in this dictionary.
 */
template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g);


bool gameReachableDFS(string src, string dest, Graph<string, bool, int>* g);
vector<string> gameShortestLengthPathBFS(string src, string dest, Graph<string, bool, int>* g);

#include "graphAlgorithms-inl.h"
