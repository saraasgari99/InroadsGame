/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include "adts/stlHashTable.h"
#include <string>

using namespace std;

template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g) {
    // throw runtime_error("Not yet implemented: reachableDFS");
    Stack<V>* frontier = new STLStack<V>();
    frontier->insert(src);
    Dictionary<V, int>* visited = new STLHashTable<V, int>();
    visited->insert(src, 0);

    V current;
    vector<V> neighbors;
    V neighbor;

    while(!frontier->isEmpty()){
        current = frontier->remove();
        if(current == dest){
            delete frontier;
            delete visited;
            return true;
        }
        neighbors = g->getNeighbors(current);
        for(int i=0; i<neighbors.size(); i++){
            neighbor = neighbors[i];
            if(!visited->contains(neighbor)){
                frontier->insert(neighbor);
                visited->insert(neighbor, 0);
            }
        }
    }

    delete frontier;
    delete visited;

    return false;

}


template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g) {
    // throw runtime_error("Not yet implemented: shortestLengthPathBFS");
    Queue<V>* frontier = new STLQueue<V>();
    frontier->insert(src);
    Dictionary<V, V>* prev = new STLHashTable<V, V>();
    prev->insert(src, src);

    V current;
    vector<V> neighbors;
    V neighbor;

    while(!frontier->isEmpty()){

        current = frontier->remove();

        if(current == dest){
            V cursor = current;
            vector<V> temppath;         // temporary vectore to store backward path (dest->src)
            temppath.push_back(current);
            while(cursor != prev->get(cursor)){
                cursor = prev->get(cursor);
                temppath.push_back(cursor);
            }
            vector<V> path = temppath;
            for(int i=0; i<path.size(); i++){
                path[i] = temppath[path.size()-1 -i];  // reverse the order so that path is src->dest
            }
            delete frontier;
            delete prev;
            return path;
        }

        neighbors = g->getNeighbors(current);
        for(int i=0; i<neighbors.size(); i++){
            neighbor = neighbors[i];
            if(!prev->contains(neighbor)){
                prev->insert(neighbor, current);
                frontier->insert(neighbor);
            }
        }
    }

    delete frontier;
    delete prev;

    throw runtime_error("no path between these two vertices");

}


template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g) {
    // throw runtime_error("Not yet implemented: singleSourceShortestPath");
    PriorityQueue<W, V>* frontier = new STLMinPriorityQueue<W, V>();
    frontier->insert(0, src);
    Dictionary<V, W>* cost = new STLHashTable<V, W>();
    cost->insert(src, 0);

    V current;
    V neighbor;
    vector<Edge<V, E, W>> edges;
    int total;

    while(!frontier->isEmpty()){
        current = frontier->remove();
        edges = g->getOutgoingEdges(current);
        for(int i=0; i<edges.size(); i++){
            Edge<V, E, W> edge = edges[i];
            neighbor = edge.getDestination();
            total = cost->get(current) + edge.getWeight();
            if(!cost->contains(neighbor)){
                cost->insert(neighbor, total);
                frontier->insert(total, neighbor);
            } else if(cost->get(neighbor) > total) {
                cost->update(neighbor, total);
                frontier->insert(total, neighbor);
            }
        }
    }

    delete frontier;

    return cost;

}



// ---------------------------------------------------------------


// returns boolean whether it's reachable only with improved roads

bool gameReachableDFS(string src, string dest, Graph<string, bool, int>* g) {
    // throw runtime_error("Not yet implemented: reachableDFS");
    Stack<string>* frontier = new STLStack<string>();
    frontier->insert(src);
    Dictionary<string, int>* visited = new STLHashTable<string, int>();
    visited->insert(src, 0);

    string current;
    vector<string> neighbors;
    string neighbor;


    while(!frontier->isEmpty()){
        current = frontier->remove();
        if(current == dest){
            delete frontier;
            delete visited;
            return true;
        }
        neighbors = g->getNeighbors(current);
        for(int i=0; i<neighbors.size(); i++){
            neighbor = neighbors[i];

            if(!visited->contains(neighbor) && g->getEdge(current, neighbor).getLabel()){        // change something HERE
                frontier->insert(neighbor);
                visited->insert(neighbor, 0);
            }
        }
    }

    delete frontier;
    delete visited;

    return false;

}


vector<string> gameShortestLengthPathBFS(string src, string dest, Graph<string, bool, int>* g) {
    // throw runtime_error("Not yet implemented: shortestLengthPathBFS");
    Queue<string>* frontier = new STLQueue<string>();
    frontier->insert(src);
    Dictionary<string, string>* prev = new STLHashTable<string, string>();
    prev->insert(src, src);

    string current;
    vector<string> neighbors;
    string neighbor;

    while(!frontier->isEmpty()){

        current = frontier->remove();

        if(current == dest){
            string cursor = current;
            vector<string> temppath;         // temporary vectore to store backward path (dest->src)
            temppath.push_back(current);
            while(cursor != prev->get(cursor)){
                cursor = prev->get(cursor);
                temppath.push_back(cursor);
            }
            vector<string> path = temppath;
            for(int i=0; i<path.size(); i++){
                path[i] = temppath[path.size()-1 -i];  // reverse the order so that path is src->dest
            }
            delete frontier;
            delete prev;
            return path;
        }

        neighbors = g->getNeighbors(current);
        for(int i=0; i<neighbors.size(); i++){
            neighbor = neighbors[i];
            if(!prev->contains(neighbor) && g->getEdge(current, neighbor).getLabel()){
                prev->insert(neighbor, current);
                frontier->insert(neighbor);
            }
        }
    }

    delete frontier;
    delete prev;

    vector<string> emppath;
    return emppath;

}

Dictionary<string, int>* gameShortestTimePathes(string src, Graph<string, bool, int>* g) {
    // throw runtime_error("Not yet implemented: singleSourceShortestPath");
    PriorityQueue<int, string>* frontier = new STLMinPriorityQueue<int, string>();
    frontier->insert(0, src);
    Dictionary<string, int>* cost = new STLHashTable<string, int>();
    cost->insert(src, 0);

    string current;
    string neighbor;
    vector<Edge<string, bool, int>> edges;
    int total;

    while(!frontier->isEmpty()){
        current = frontier->remove();
        edges = g->getOutgoingEdges(current);
        for(int i=0; i<edges.size(); i++){
            Edge<string, bool, int> edge = edges[i];
            if(edge.getLabel()){
                neighbor = edge.getDestination();
                total = cost->get(current) + edge.getWeight();
                if(!cost->contains(neighbor)){
                    cost->insert(neighbor, total);
                    frontier->insert(total, neighbor);
                } else if(cost->get(neighbor) > total) {
                    cost->update(neighbor, total);
                    frontier->insert(total, neighbor);
                }
            }

        }
    }

    delete frontier;

    return cost;

}



// if(!cost->contains(neighbor) && edge.getLabel()){
//     cost->insert(neighbor, total);
//     frontier->insert(total, neighbor);
// } else if(cost->get(neighbor) > total) {
//     cost->update(neighbor, total);
//     frontier->insert(total, neighbor);
// }
