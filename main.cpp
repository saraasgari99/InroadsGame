/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "inroadsGUI.h"
#include "ioUtils.h"
#include "inroadsGame.h"

using namespace std;

int main(int argc, char** argv) {
    // Check command line arguments and give up if necessary.
    if (argc != 2) {
        cerr << "Expected one argument: name of map file." << endl;
        return 1;
    }

    // Initialize randomizer.  This should happen before any random numbers are
    // selected.
    srand(time(nullptr));

    // Get command-line argument.
    string mapFilename = string(argv[1]);

    // Read the Inroads map file.
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
    InroadsGame game = InroadsGame(graph);
    gui.updateInroadsMap(graph);

    int turn = 1;
    pair<string, string> input;   // a pair of the two vertices connected by the edge which user chose
    int totalScore = 0;
    string scoreText;
    string message;

    while(turn < 21){

        try{

            int medScore, libScore, storeScore, totalTurnScore;  // initialize the scores
            gui.updateTurnText("Turn: " + to_string(turn));

            input = gui.getNextMove();      // get user's input
            game.updateGraph(input);        // update the graph according to the input
            gui.updateInroadsMap(graph);    // give the GUI the updated graph

            libScore = game.getCalcScoreLib();
            storeScore = game.getCalcScoreStore();
            medScore = game.getCalcScoreMed();

            totalTurnScore = libScore + storeScore + medScore;  // the score you got in this turn
            totalScore += totalTurnScore;                       // the score you got so far

            scoreText = "Score: " + to_string(totalScore);      // show the total score
            gui.updateScoreText(scoreText);

            // create a message to show the breakdown of the score you got in this turn
            message = "Your score this turn: \n +" + to_string(libScore) + " from the library\n";
            message += "+" + to_string(storeScore) + " from stores\n";
            message += "+" + to_string(medScore) + " from medical access\n";
            message += "Total points from this turn: " + to_string(totalTurnScore);
            gui.updateMessage(message);

            turn++;

        }catch(runtime_error e){}
         // if the user choose the edge which is already improved, updateGraph() will throw a runtime_error
         // we catch this runtime error and do nothing inside the catch section
         // so that we can ignore the invalid input from the user.
    }

    gui.updateTurnText("Game Over");



    // TODO: Write code that runs the game.  You'll want to write most of your
    // game logic into the RailwayGame class and then use an object of that type
    // here to control the game and relay what it says to the GUI.  This
    // assignment is more open-ended than the previous assignments.

    // TODO: Delete the following code.  It's just here at the start of the
    // assignment to make sure that you can see what the GUI looks like.  If we
    // didn't do something here (like wait for the user to press enter on the
    // console), then the main function would stop and the GUI would instantly
    // vanish.
    //gui.~InroadsGUI();
    string deleteThisVariable;
    getline(cin, deleteThisVariable);

    // Finally, clean up and exit successfully.
    //delete graph;
    delete vertexPositions;
    return 0;
}
