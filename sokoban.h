/*
 * ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * Onat Deniz Dogan <oddogan@protonmail.com> wrote this code. As long as you retain this 
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 */

#ifndef sokoban
#define sokoban

class Sokoban
{
    private:
        // Create a char array which will store the map state
        char **sokoban_map;
        int **target_points;
        // Hold the player's position in memory
        int player_x, player_y;
    public:
        Sokoban();
        Sokoban(char **input_map);
        Sokoban(const Sokoban &obj);
        Sokoban&operator=(const Sokoban &state);
        bool move_up();
        bool move_down();
        bool move_left();
        bool move_right();
        bool is_solved();
        void print_puzzle() const;
        char** get_map() const;
};

#endif
