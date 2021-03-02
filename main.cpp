/*
 * ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * Onat Deniz Dogan <oddogan@protonmail.com> wrote this code. As long as you retain this 
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 */

#include <iostream>
#include <cstdlib>
#include <fstream> // File stream library for file IO
#include <conio.h>
#include "sokoban.h"
#include "stackqueue.h"
#include "doublylinkedlist.h"

using namespace std;

// Path to the input file relative to the current directory.
string path = "sample_puzzle.txt";

// Store the map from the text file
char **input_map;
// Store the last input
char input;

/* The function declarations */
// Reading a map from a file
void readFromFile(string path);

int main()
{
    // User chooses to use StackQueue or Doubly-Linked List in the beginning
    cout << "Welcome. What would you like to use?" << endl << "1) StackQueue" << endl << "2) Doubly-Linked List" << endl << "Your choice: ";
    int choice = 0;
    while(true)
    {
        cin >> choice;
        if (cin.fail() || !(choice == 1 || choice == 2)) { // If the input is not 1 or 2
            cin.clear(); cin.ignore();
            cout << "Re-enter a valid value! " << endl;
        } else break;
    }

    switch(choice){
        case 1:
            {
            // Read the map from the file
            readFromFile(path);
            // Create the Sokoban object and print the initial state
            Sokoban game(input_map);
            Sokoban temp(input_map);
            cout << "You've chosen the StackQueue method! Have fun!" << endl;
            game.print_puzzle();
            // Create the StackQueue to store the states
            StackQueue<Sokoban> memory;
            //memory.push_front(game); // Initial state

            /* The loop will continue until
            the end condition is satisfied */
            while(true){
                /* Waits for keyboard input
                If there is an input, it realizes it
                without a need for a return key press */
                if (kbhit() != 0) {
                    input = getch();
                    system("cls");
                    switch(input){
                        case 'w':
                            temp = game;
                            if(game.move_up()) // If valid, move up
                                memory.push_front(temp); // Push the last state to Stackqueue
                            break;
                        case 'a':
                            temp = game;
                            if(game.move_left()) // If valid, move left
                                memory.push_front(temp); // Push the last state to Stackqueue
                            break;
                        case 's':
                            temp = game;
                            if(game.move_down()) // If valid, move down
                                memory.push_front(temp); // Push the last state to Stackqueue
                            break;
                        case 'd':
                            temp = game;
                            if(game.move_right()) // If valid, move right
                                memory.push_front(temp); // Push the last state to Stackqueue
                            break;
                        case 'z':
                            if(!memory.is_empty())  // If there are previous moves
                            {
                                cout << "Undoing the last move!" << endl;
                                game = memory.pop_front(); // Pop the last state and assign to the current game state
                            }
                            else
                            {
                                cout << "No older moves!" << endl;
                            }
                            break;
                        case 'r':
                            cout << "** Replaying **" << endl;
                            while(!memory.is_empty())
                                memory.pop_rear().print_puzzle(); // Print by order from the beginning of the game
                            game.print_puzzle();
                            exit(0);
                            break;
                        case 'q':
                            exit(0);
                        default:
                            break;
                    }
                    if(game.is_solved())
                    {
                        cout << "Puzzle is solved!" << endl;
                    }
                    game.print_puzzle();
                }
            }
            break;
            }
        case 2:
            {
            // Read the map from the file
            readFromFile(path);
            // Create the Sokoban object and print the initial state
            Sokoban game(input_map);
            Sokoban temp(input_map);
            cout << "You've chosen the Doubly-Linked List method! Have fun!" << endl;
            game.print_puzzle();
            // Create the StackQueue to store the states
            LinkedList<Sokoban> memory;

            /* The loop will continue until
            the end condition is satisfied */
            while(true){
                /* Waits for keyboard input
                If there is an input, it realizes it
                without a need for a return key press */
                if (kbhit() != 0) {
                    input = getch();
                    system("cls");
                    switch(input){
                        case 'w':
                            memory.insertNode(game);
                            game.move_up();
                            if(game.is_solved())
                            {
                                cout << "Puzzle is solved!" << endl;
                            }
                            game.print_puzzle();
                            break;
                        case 'a':
                            memory.insertNode(game);
                            game.move_left();
                            if(game.is_solved())
                            {
                                cout << "Puzzle is solved!" << endl;
                            }
                            game.print_puzzle();
                            break;
                        case 's':
                            memory.insertNode(game);
                            game.move_down();
                            if(game.is_solved())
                            {
                                cout << "Puzzle is solved!" << endl;
                            }
                            game.print_puzzle();
                            break;
                        case 'd':
                            memory.insertNode(game);
                            game.move_right();
                            if(game.is_solved())
                            {
                                cout << "Puzzle is solved!" << endl;
                            }
                            game.print_puzzle();
                            break;
                        case 'z':
                            if(!memory.listEmpty())
                            {
                                cout << "Undoing the last move!" << endl;
                                game = memory.deleteLast();
                            }
                            else
                            {
                                cout << "No older moves!" << endl;
                            }
                            if(game.is_solved())
                            {
                                cout << "Puzzle is solved!" << endl;
                            }
                            game.print_puzzle();
                            break;
                        case 'r':
                            cout << "** Replaying **" << endl;
                            memory.reset(); // Set position to head node
                            while(!memory.endOfList()) // Iterate through all the list
                            {
                                memory.data().print_puzzle(); // Print the state on the current position
                                memory.next(); // Move to next node
                            }
                            memory.data().print_puzzle();
                            game.print_puzzle();
                            exit(0);
                            break;
                        case 'q':
                            exit(0);
                        default:
                            cerr << "Please give a valid input!" << endl;
                            break;
                    }
                }
            }
            break;
            }
    }

    return 0;
}

/* Implementations for necessary functions */

void readFromFile(string path)
{
    // Create the map with 6x8 dimensions
    input_map = new char *[6];
    for(int i = 0; i < 6; i++)
        input_map[i] = new char[8];

    // Create an input file stream and open the file
    ifstream file;
    file.open(path.c_str());
    // Create the dummy char to skip newline characters
    char dummy;
    if(!file) cout << "ERROR";
    // Read the data from the file and write onto our map array
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<8; j++)
        {
            // Do not skip whitespaces!
            file >> noskipws >> input_map[i][j];
        }
        file >> noskipws >> dummy;
    }

    // Close the file for safety
    file.close();
    return;
}
