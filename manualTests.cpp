/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <string>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "inroadsGUI.h"
#include "ioUtils.h"

#include "inroadsGame.h"

using namespace std;

int main(int argc, char** argv) {
    // You can use this main to experiment with the code you have written

    string mapFilename = string(argv[1]);

    pair<Graph<string, bool, int>*, Dictionary<string, pair<int, int>>*>
        mapFileContents;
    try {
        mapFileContents = readInroadsMap(mapFilename);
    } catch (exception e) {
        cout << "Could not read Inroads map file " << mapFilename << ": "
             << e.what() << endl;
    }
    // The map file contained the graph representing the map.  It also contained
    // the vertex positions (so we know where each vertex goes on the map).
    Graph<string, bool, int>* graph = mapFileContents.first;
    Dictionary<string, pair<int, int>>* vertexPositions =
        mapFileContents.second;

    // Create the GUI object here.  This is statically allocated, so the GUI
    // will disappear the moment your program leaves the main function.
    // The GUI object should only be used by main, and not by any other function
    // or object; do NOT change the type of this variable.
    InroadsGUI gui(vertexPositions, mapFilename);

    // Tell the GUI about the graph we have.
    gui.updateInroadsMap(graph);
    gui.updateScoreText("Score: 0");
    //gui.updateTurnText("Turn: 1");

    cout << "the code above is from main.cpp" << endl;

    InroadsGame game = InroadsGame(graph);
    cout << "scorelib  : " << game.getCalcScoreLib() << endl;
    cout << "scorestore: " << game.getCalcScoreStore() << endl;
    cout << "scoremed: " << game.getCalcScoreMed() << endl;


    pair<string, string> input = gui.getNextMove();
    int turn = 1;

    while(turn < 6){
        try{
            input = gui.getNextMove();
            game.updateGraph(input);
            gui.updateInroadsMap(graph);

            cout << "scorelib  : " << game.getCalcScoreLib() << endl;
            cout << "scorestore: " << game.getCalcScoreStore() << endl;
            cout << "scoremed: " << game.getCalcScoreMed() << endl;
            turn++;
        }catch(runtime_error e){}

    }







    return 0;
}
