/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <string>
#include "adts/graph.h"

using namespace std;


/**
 * An instance of this class represents a single game of Inroads.  An object of
 * type InroadsGame does not represent the user interface, but does represent
 * the idea of a game of Inroads, including the state of the board and all of
 * the information pertaining to the player.  It also includes the logic for
 * making moves in the game and enforces the game's rules.
 */
class InroadsGame {
  public:
    // TODO: write your InroadsGame constructor and method declarations here
    InroadsGame(Graph<string, bool, int>* graph);
    ~InroadsGame();

    void updateGraph(pair<string,string> input);
    int getCalcScoreTotal();
    int getCalcScoreLib();
    int getCalcScoreStore();
    int getCalcScoreMed();

  private:
    // TODO: write your InroadsGame fields here
    Graph<string, bool, int>* graph;
    // int scoreTotal;
    // int scoreLib;
    // int scoreStore;
    // int scoreMed;

    vector<string> places;
    vector<string> residentials;
    string library;
    vector<string> stores;
    vector<string> medicals;


};
