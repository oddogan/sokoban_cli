/*
 * ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * Onat Deniz Dogan <oddogan@protonmail.com> wrote this code. As long as you retain this 
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 */

#include "sokoban.h"
#include <iostream>
using namespace std;

/* The implementations for class Sokoban */
Sokoban::Sokoban()
{
    // Create the map with 6x8 dimensions
    sokoban_map = new char *[6];
    for(int i = 0; i < 6; i++)
        sokoban_map[i] = new char[8];

    // Create the target points' map with 6x8 dimensions
    target_points = new int *[6];
    for(int i = 0; i < 6; i++)
        target_points[i] = new int[8];
}

Sokoban::Sokoban(char **input_map)
{
    // Create the map with 6x8 dimensions
    sokoban_map = new char *[6];
    for(int i = 0; i < 6; i++)
        sokoban_map[i] = new char[8];

    // Create the target points' map with 6x8 dimensions
    target_points = new int *[6];
    for(int i = 0; i < 6; i++)
        target_points[i] = new int[8];

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<8; j++)
        {
            // Transfer the data to the member map
            sokoban_map[i][j] = input_map[i][j];
            // Get the initial player position
            if(sokoban_map[i][j] == '@')
            {
                player_x = i;
                player_y = j;
            }
            // Mark the target points with 1 in map, 0 otherwise
            else if(sokoban_map[i][j] == '.')
                target_points[i][j] = 1;
            else
                target_points[i][j] = 0;
        }
    }
}

Sokoban::Sokoban(const Sokoban &obj)
{
    // Create the map with 6x8 dimensions
    sokoban_map = new char *[6];
    for(int i = 0; i < 6; i++)
        sokoban_map[i] = new char[8];

    // Create the target points' map with 6x8 dimensions
    target_points = new int *[6];
    for(int i = 0; i < 6; i++)
        target_points[i] = new int[8];

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<8; j++)
        {
            // Transfer the data to the member map
            sokoban_map[i][j] = obj.get_map()[i][j];
            // Get the initial player position
            if(sokoban_map[i][j] == '@')
            {
                player_x = i;
                player_y = j;
            }
            // Mark the target points with 1 in map, 0 otherwise
            else if(sokoban_map[i][j] == '.')
                target_points[i][j] = 1;
            else
                target_points[i][j] = 0;
        }
    }
}

Sokoban&Sokoban::operator=(const Sokoban &state)
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<8; j++)
        {
            // Transfer the data to the member map
            sokoban_map[i][j] = state.get_map()[i][j];
            // Get the initial player position
            if(sokoban_map[i][j] == '@')
            {
                player_x = i;
                player_y = j;
            }
            // Mark the target points with 1 in map, 0 otherwise
            else if(sokoban_map[i][j] == '.')
                target_points[i][j] = 1;
            else
                target_points[i][j] = 0;
        }
    }
}

bool Sokoban::move_up()
{
    char next_position = sokoban_map[player_x-1][player_y];

    switch(next_position)
    {
    case '#':
        cerr << "Map boundary on top!" << endl; // If not movable, throw error
        return false;
        break;
    case '*': // If *, behave same as a box
    case '$':
        if(sokoban_map[player_x-2][player_y] == ' ' || sokoban_map[player_x-2][player_y] == '.') // If the box is pushable
        {
            sokoban_map[player_x-2][player_y] = '$'; // Change the char in the new box position
            sokoban_map[player_x-1][player_y] = '@'; // Change the char in the new player position
            if(target_points[player_x][player_y])
                sokoban_map[player_x][player_y] = '.'; // If the emptied point is a target point, change with a '.' char
            else
                sokoban_map[player_x][player_y] = ' '; // If it is not a target, change with blank space
            player_x--; // Update player position
            return true;
            break;
        }
        else
        {   // If the box is not pushable, throw errors
            if(sokoban_map[player_x-2][player_y] == '$') cerr << "Cannot move consecutive boxes!" << endl;
            else cerr << "Map boundary on top!" << endl;
            return false;
            break;
        }
    default:
        // Move the player to a blank space
        sokoban_map[player_x-1][player_y] = '@';
        if(target_points[player_x][player_y])
                sokoban_map[player_x][player_y] = '.';
        else
            sokoban_map[player_x][player_y] = ' ';
        player_x--;
        return true;
        break;
    }
}

// Almost same with the move_up above
bool Sokoban::move_down()
{
    char next_position = sokoban_map[player_x+1][player_y];

    switch(next_position)
    {
    case '#':
        cerr << "Map boundary on bottom!" << endl;
        return false;
        break;
    case '*':
    case '$':
        if(sokoban_map[player_x+2][player_y] == ' ' || sokoban_map[player_x+2][player_y] == '.')
        {
            sokoban_map[player_x+2][player_y] = '$';
            sokoban_map[player_x+1][player_y] = '@';
            if(target_points[player_x][player_y])
                sokoban_map[player_x][player_y] = '.';
            else
                sokoban_map[player_x][player_y] = ' ';
            player_x++;
            return true;
            break;
        }
        else
        {
            if(sokoban_map[player_x+2][player_y] == '$' || sokoban_map[player_x+2][player_y] == '*') cerr << "Cannot move consecutive boxes!" << endl;
            else cerr << "Map boundary on bottom!" << endl;
            return false;
            break;
        }
    default:
        sokoban_map[player_x+1][player_y] = '@';
        if(target_points[player_x][player_y])
                sokoban_map[player_x][player_y] = '.';
        else
            sokoban_map[player_x][player_y] = ' ';
        player_x++;
        return true;
        break;
    }
}

// Almost same with the move_up above
bool Sokoban::move_left()
{
    char next_position = sokoban_map[player_x][player_y-1];

    switch(next_position)
    {
    case '#':
        cerr << "Map boundary on left!" << endl;
        return false;
        break;
    case '*':
    case '$':
        if(sokoban_map[player_x][player_y-2] == ' ' || sokoban_map[player_x][player_y-2] == '.')
        {
            sokoban_map[player_x][player_y-2] = '$';
            sokoban_map[player_x][player_y-1] = '@';
            if(target_points[player_x][player_y])
                sokoban_map[player_x][player_y] = '.';
            else
                sokoban_map[player_x][player_y] = ' ';
            player_y--;
            return true;
            break;
        }
        else
        {
            if(sokoban_map[player_x][player_y-2] == '$') cerr << "Cannot move consecutive boxes!" << endl;
            else cerr << "Map boundary on left!" << endl;
            return false;
            break;
        }
    default:
        sokoban_map[player_x][player_y-1] = '@';
        if(target_points[player_x][player_y])
                sokoban_map[player_x][player_y] = '.';
        else
            sokoban_map[player_x][player_y] = ' ';
        player_y--;
        return true;
        break;
    }
}

// Almost same with the move_up above
bool Sokoban::move_right()
{
    char next_position = sokoban_map[player_x][player_y+1];

    switch(next_position)
    {
    case '#':
        cerr << "Map boundary on right!" << endl;
        return false;
        break;
    case '*':
    case '$':
        if(sokoban_map[player_x][player_y+2] == ' ' || sokoban_map[player_x][player_y+2] == '.')
        {
            sokoban_map[player_x][player_y+2] = '$';
            sokoban_map[player_x][player_y+1] = '@';
            if(target_points[player_x][player_y])
                sokoban_map[player_x][player_y] = '.';
            else
                sokoban_map[player_x][player_y] = ' ';
            player_y++;
            return true;
            break;
        }
        else
        {
            if(sokoban_map[player_x][player_y+2] == '$') cerr << "Cannot move consecutive boxes!" << endl;
            else cerr << "Map boundary on right!" << endl;
            return false;
            break;
        }
    default:
        sokoban_map[player_x][player_y+1] = '@';
        if(target_points[player_x][player_y])
                sokoban_map[player_x][player_y] = '.';
        else
            sokoban_map[player_x][player_y] = ' ';
        player_y++;
        return true;
        break;
    }
}

void Sokoban::print_puzzle() const
{
    //system("cls");
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<8; j++)
        {
            cout << sokoban_map[i][j];
        }
        cout<<endl;
    }
}

bool Sokoban::is_solved()
{
    bool solved = true;
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(target_points[i][j]) // If the point is a target point
            {
                if(sokoban_map[i][j] == '@') sokoban_map[i][j] = '+'; // If the player is on the target, change with '+'
                else if(sokoban_map[i][j] == '$') sokoban_map[i][j] = '*'; // If the box is on the target, change with '*'
            }
            if(sokoban_map[i][j] == '.' || sokoban_map[i][j] == '+') solved = false; // If there is a target point without a box on it, it is not solved
        }
    }
    return solved; // If not changed to false, it is solved
}

char** Sokoban::get_map() const
{
    return sokoban_map;
}
