/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <string>

#include "inroadsGame.h"
#include "graphAlgorithms.h"


using namespace std;

// TODO: implement your InroadsGame class constructor and methods here

InroadsGame::InroadsGame(Graph<string, bool, int>* graph){

    this->graph = graph;

    this->places = this->graph->getVertices();   // all of the places on the map
    for(int i=0; i<this->places.size(); i++){
        string place = places[i];
        if(place[0] == 'R'){
            this->residentials.push_back(place);  // residential areas;
        } else if(place[0] == 'L'){
            this->library = place;                // a library
        } else if(place[0] == 'S'){
            this->stores.push_back(place);        // stores
        } else if(place[0] == 'M'){
            this->medicals.push_back(place);      // medical locations
        }
    }

}

InroadsGame::~InroadsGame(){
    delete this->graph;
}




void InroadsGame::updateGraph(pair<string,string> input){

    string src = input.first;
    string dst = input.second;

    Edge<string, bool, int> updatedEdge = this->graph->getEdge(src, dst); // this is a copy

    if(updatedEdge.getLabel() == true){
        throw runtime_error("this edge is already improved");
    }

    this->graph->removeEdge(src, dst);
    this->graph->insertEdge(src, dst, true, updatedEdge.getWeight());  // replace the edge with the improved one

}


int InroadsGame::getCalcScoreLib(){

    int scoreLib = 0;

    for(int i=0; i<this->residentials.size(); i++){             // iterate through all residential areas
        string res = this->residentials[i];
        if(gameReachableDFS(res, this->library, this->graph)){  // if the library is reachable get 15 pts
            scoreLib += 15;
        }
    }

    return scoreLib;

 }


int InroadsGame::getCalcScoreStore(){

    int scoreStore = 0;

    for(int i=0; i<this->residentials.size(); i++){    // iterate through all residential areas
        string res = this->residentials[i];
        for(int j=0; j<this->stores.size(); j++){      // iterate through all stores
            string store = this->stores[j];
            vector<string> path = gameShortestLengthPathBFS(res, store, this->graph);  // get the shortest path
            if(path.size() < 5 && path.size() >= 2){  // if the path exists(=path contains src & dst) and <5
                scoreStore += 10;
            }
        }
    }

    return scoreStore;

}

int InroadsGame::getCalcScoreMed(){

    int scoreMed = 0;

    for(int i=0; i<this->residentials.size(); i++){
        string res = this->residentials[i];
        // Dictionary: key= vertices, value= the cost to get there from res
        Dictionary<string, int>* shortestPathes = gameShortestTimePathes(res, this->graph);
        string med;
        int minPath = 2147483647;   // the biggest integer in C++ so that it works as the initial value
        for(int i = 0; i<this->medicals.size(); i++){
            med = this->medicals[i];
            if(shortestPathes->contains(med)){
                if(shortestPathes->get(med) < minPath){
                    minPath = shortestPathes->get(med);
                }
            }
        }
        scoreMed += (420/minPath);
        delete shortestPathes;
    }

    return scoreMed;

}
