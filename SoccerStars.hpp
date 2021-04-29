#ifndef __SOCCERSTARS_HPP__
#define __SOCCERSTARS_HPP__

#include <iostream>
#include "RSDL/src/rsdl.hpp"
#include "Vector2D.hpp"
#include "Piece.hpp"
#include <vector>

class SoccerStars
{
public:
    void line_up(int team_no, const std::vector <Vector2D>& formation);
    void init(int n, int m);
    void draw_team(int team_no);
    void draw_scoreboard();
    void draw();
    void select_player();
    Vector2D calculate_velocity(Vector2D d);
    void move_selected_player();
    int specify_option_type();
    void reset();
    void reset_all();
    void handle_events();
    void update_team(int team_no);
    void handle_collision(Piece* a, Piece* b);
    std::vector <Piece*> get_pieces();
    void handle_collisions();
    void switch_turns();
    void place_the_ball();
    void update_scores();
    void update();
    void start();
private:
    Window* window;
    std::vector <Piece*> team_1;
    std::vector <Piece*> team_2;
    int turn;
    Piece* ball;
    int round;
    int rounds_to_win, goals_to_win;
    std::vector <int> goals_count;
    std::vector <int> rounds_count;
    bool is_running;
    Piece* selected_player;
    bool mouse_released;
    int winner_team_no;
    Point mouse_position;
    int scorer_team_no;
    bool game_over;
    bool silent_mode;
    int option_type;
};

#endif