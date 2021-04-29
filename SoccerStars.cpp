#include "SoccerStars.hpp"
using namespace std;

const int FIELD_WIDTH = 800;
const int WINDOW_WIDTH = FIELD_WIDTH;
const int FIELD_HEIGHT = 480;
const int SCOREBOARD_HEIGHT = 100;
const int WINDOW_HEIGHT = FIELD_HEIGHT + SCOREBOARD_HEIGHT;
const int TEAM_SIZE = 5;
const int TEAM_1 = 1;
const int TEAM_2 = 2;
const int R_BALL = 12;
const int R_PLAYER = 25;
const int NONE = 0;
const int BALL_MASS = 1;
const int PLAYER_MASS = 2;
const int RESET = 1;
const int MUSIC = 2;
const int FONT_SIZE = 40;
const int FONT_SIZE_2 = 56;
const int PLAYER = 2;
const int BALL = 1;
const int DELAY_TIME = 15;
const double WALL_THRESHOLD = 0;
const double MAX_INITIAL_SPEED = 500;
const double THROW_RADIUS = 60;
const string WINDOW_TITLE = "Soccer Stars";
const string FIELD_JPG = "Assets/field.jpg";
const string BALL_PNG = "Assets/ball.png";
const string PLAYER1_PNG = "Assets/germany.png";
const string PLAYER2_PNG = "Assets/brazil.png";
const string SCOREBOARD_PNG = "Assets/scoreboard.png";
const string RING_PNG = "Assets/ring.png";
const string ARROW_PNG = "Assets/arrow.png";
const string MUSIC_ON_PNG = "Assets/loud.png";
const string MUSIC_OFF_PNG = "Assets/mute.png";
const string RESET_PNG = "Assets/reset.png";
const string MUSIC_MP3 = "Killrude.mp3";
const string FONT_FAMILY = "FreeSans.ttf";
const string GOAL_WAV = "goal.wav";
const string APPLAUSE_WAV = "applause.wav";
const string CHEER_WAV = "cheer.wav";
const Point ROUNDS_1_POINT (50, 25);
const Point GOALS_1_POINT (300, 25);
const Point ROUNDS_2_POINT (WINDOW_WIDTH - 75, 25);
const Point GOALS_2_POINT (WINDOW_WIDTH - 310, 25);
const Point RESET_ICON_TOP_LEFT (340, 50);
const Point RESET_ICON_BOTTOM_RIGHT (390, 100);
const Point MUSIC_ICON_TOP_LEFT (410, 50);
const Point MUSIC_ICON_BOTTOM_RIGHT (460, 100);
const Point WINNER_MSG_POINT (240, 300);

const vector <Vector2D> FORMATION_1 =
{
    Vector2D(2 * R_PLAYER + WALL_THRESHOLD, FIELD_HEIGHT / 2 + SCOREBOARD_HEIGHT),
    Vector2D(160, 120 + SCOREBOARD_HEIGHT),
    Vector2D(160, FIELD_HEIGHT - 120 + SCOREBOARD_HEIGHT),
    Vector2D(320, 160 + SCOREBOARD_HEIGHT),
    Vector2D(320, FIELD_HEIGHT - 160 + SCOREBOARD_HEIGHT)
};
const vector <Vector2D> FORMATION_2 =
{
    Vector2D(FIELD_WIDTH - 2 * R_PLAYER - WALL_THRESHOLD, FIELD_HEIGHT / 2 + SCOREBOARD_HEIGHT),
    Vector2D(FIELD_WIDTH - 160, 120 + SCOREBOARD_HEIGHT),
    Vector2D(FIELD_WIDTH - 160, FIELD_HEIGHT - 120 + SCOREBOARD_HEIGHT),
    Vector2D(FIELD_WIDTH - 320, 160 + SCOREBOARD_HEIGHT),
    Vector2D(FIELD_WIDTH - 320, FIELD_HEIGHT - 160 + SCOREBOARD_HEIGHT)
};
const Vector2D BALL_INITIAL_POSITION(FIELD_WIDTH / 2, FIELD_HEIGHT / 2 + SCOREBOARD_HEIGHT);

Vector2D to_vector(Point p)
{
    Vector2D v;
    v.x = (double) p.x;
    v.y = (double) p.y;
    return v;
}

void SoccerStars::line_up(int team_no, const vector <Vector2D>& formation)
{
    for (int i = 0; i < TEAM_SIZE; i ++)
    {
        Piece* player = new Piece(PLAYER_MASS, formation[i], Vector2D(0, 0), R_PLAYER, PLAYER);
        if (team_no == TEAM_1)
            team_1.push_back(player);
        else
            team_2.push_back(player);
    }
}

void SoccerStars::init(int n, int m)
{
    is_running = true;
    game_over = false;
    rounds_to_win = n;
    goals_to_win = m;
    round = 1;
    turn = TEAM_1;
    goals_count = vector <int> {0, 0, 0};
    rounds_count = vector <int> {0, 0, 0};
    selected_player = nullptr;
    mouse_released = false;
    winner_team_no = NONE;
    mouse_position = Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    line_up(TEAM_1, FORMATION_1);
    line_up(TEAM_2, FORMATION_2);
    ball = new Piece(BALL_MASS, BALL_INITIAL_POSITION, Vector2D(0, 0), R_BALL, BALL);
    window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    silent_mode = false;
    option_type = NONE;
}

void SoccerStars::draw_team(int team_no)
{
    vector <Piece*> team = team_no == TEAM_1 ? team_1 : team_2;
    string src = team_no == TEAM_1 ? PLAYER1_PNG : PLAYER2_PNG;
    for (Piece* player : team)
    {
        if (player == selected_player && mouse_released == false)
        {
            Point pawn_position = player->get_position().to_point();
            double l = (to_vector(pawn_position) - to_vector(mouse_position)).length();
            double r = l > THROW_RADIUS ? THROW_RADIUS : l;
            window->draw_img(RING_PNG, Rectangle((to_vector(pawn_position) - r).to_point(), 2 * r, 2 * r));
            window->draw_line(pawn_position, mouse_position, BLACK);
            window->draw_line(pawn_position, 2 * pawn_position - mouse_position, BLACK);
        }
        player->draw(window, src);
    }
}

void SoccerStars::draw_scoreboard()
{
    window->draw_img(SCOREBOARD_PNG, Rectangle(0, 0, FIELD_WIDTH, SCOREBOARD_HEIGHT));
    RGB color_1 = turn == TEAM_1 ? RED : BLACK;
    RGB color_2 = turn == TEAM_2 ? GREEN : BLACK;
    window->show_text(to_string(rounds_count[TEAM_1]), ROUNDS_1_POINT, color_1, FONT_FAMILY, FONT_SIZE);
    window->show_text(to_string(rounds_count[TEAM_2]), ROUNDS_2_POINT, color_2, FONT_FAMILY, FONT_SIZE);
    window->show_text(to_string(goals_count[TEAM_1]), GOALS_1_POINT, WHITE, FONT_FAMILY, FONT_SIZE);
    window->show_text(to_string(goals_count[TEAM_2]), GOALS_2_POINT, WHITE, FONT_FAMILY, FONT_SIZE);
    window->draw_img(RESET_PNG,
        Rectangle(RESET_ICON_TOP_LEFT, RESET_ICON_BOTTOM_RIGHT), NULL_RECT);
    if (silent_mode)
        window->draw_img(MUSIC_ON_PNG, Rectangle(MUSIC_ICON_TOP_LEFT, MUSIC_ICON_BOTTOM_RIGHT));
    else
        window->draw_img(MUSIC_OFF_PNG, Rectangle(MUSIC_ICON_TOP_LEFT, MUSIC_ICON_BOTTOM_RIGHT));
}

void SoccerStars::draw()
{
    window->clear();
    window->draw_img(FIELD_JPG, Rectangle(0, SCOREBOARD_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT));
    if (game_over == false)
    {
        ball->draw(window, BALL_PNG);
        draw_team(TEAM_1);
        draw_team(TEAM_2);
    }
    else
        window->show_text("Team " + to_string(winner_team_no) + " Won.", WINNER_MSG_POINT, BLACK, FONT_FAMILY, FONT_SIZE_2);
    draw_scoreboard();
    window->update_screen();
}

void SoccerStars::select_player()
{
    if (selected_player == nullptr)
    {
        vector <Piece*> team = turn == TEAM_1 ? team_1 : team_2;
        for (Piece* player : team)
            if (player->has_point(mouse_position))
                selected_player = player;
    }
}

Vector2D SoccerStars::calculate_velocity(Vector2D d)
{
    Vector2D v;
    if (d.length() < THROW_RADIUS)
        v = d * (-MAX_INITIAL_SPEED/THROW_RADIUS);
    else
        v = d * (-MAX_INITIAL_SPEED/d.length());
    return v;
}

void SoccerStars::move_selected_player()
{
    Vector2D mp = to_vector(mouse_position);
    Vector2D pawn_position = selected_player->get_position();
    Vector2D d = mp - pawn_position;
    Vector2D v = calculate_velocity(d);
    selected_player->set_velocity(v);
    mouse_released = true;
}

int SoccerStars::specify_option_type()
{
    Vector2D v = to_vector(mouse_position);
    bool reset = (v > to_vector(RESET_ICON_TOP_LEFT)) == Vector2D(1, 1) &&
        (v < to_vector(RESET_ICON_BOTTOM_RIGHT)) == Vector2D(1, 1);
    bool music = (v > to_vector(MUSIC_ICON_TOP_LEFT)) == Vector2D(1, 1) &&
        (v < to_vector(MUSIC_ICON_BOTTOM_RIGHT)) == Vector2D(1, 1);
    if (reset)
        return RESET;
    if (music)
        return MUSIC;
    return NONE;
}

void SoccerStars::reset()
{
    team_1.clear();
    team_2.clear();
    line_up(TEAM_1, FORMATION_1);
    line_up(TEAM_2, FORMATION_2);
    place_the_ball();
    scorer_team_no = NONE;
}

void SoccerStars::reset_all()
{
    reset();
    goals_count[TEAM_1] = 0;
    goals_count[TEAM_2] = 0;
    rounds_count[TEAM_1] = 0;
    rounds_count[TEAM_2] = 0;
    game_over = false;
    turn = TEAM_1;
}

void SoccerStars::handle_events()
{
    if (window->has_pending_event())
    {
        Event e = window->poll_for_event();
        switch (e.get_type())
        {
            case Event::EventType::QUIT:
            {
                is_running = false;
                break;
            }
            case Event::LCLICK:
            {
                mouse_position = e.get_mouse_position();
                option_type = specify_option_type();
                switch (option_type)
                {
                    case RESET:
                    {
                        reset_all();
                        break;
                    }
                    case MUSIC:
                    {
                        if (silent_mode)
                        {
                            window->play_music(MUSIC_MP3);
                            silent_mode = false;
                        }
                        else
                        {
                            window->pause_music();
                            silent_mode = true;
                        }
                    }
                    default:
                    {
                        select_player();
                        break;
                    }
                }
                break;
            }
            case Event::LRELEASE:
            {
                mouse_position = e.get_mouse_position();
                if (selected_player != nullptr)
                    move_selected_player();
                break;
            }
            case Event::MMOTION:
            {
                if (selected_player != nullptr)
                    mouse_position = e.get_mouse_position();
                break;
            }
        }
    }
}

void SoccerStars::update_team(int team_no)
{
    vector <Piece*> team = team_no == TEAM_1 ? team_1 : team_2;
    for (Piece* player : team)
        player->update();
}

void SoccerStars::handle_collision(Piece* a, Piece* b)
{
    Vector2D v1 = a->get_velocity();
    Vector2D v2 = b->get_velocity();
    Vector2D dv1 = v1 - v2;
    Vector2D dv2 = v2 - v1;
    Vector2D x1 = a->get_position();
    Vector2D x2 = b->get_position();
    Vector2D dx1 = x1 - x2;
    Vector2D dx2 = x2 - x1;
    double l1 = dx1.length();
    double l2 = dx2.length();
    double d1 = dv1 % dx1;
    double d2 = dv2 % dx2;
    double m1 = a->get_mass();
    double m2 = b->get_mass();
    double c1 = (2 * m2)/(m1 + m2);
    double c2 = (2 * m1)/(m1 + m2);
    Vector2D v1p = v1 - dx1 * (c1*d1/pow(l1, 2));
    Vector2D v2p = v2 - dx2 * (c2*d2/pow(l2, 2));
    a->set_velocity(v1p);
    b->set_velocity(v2p);
}

vector <Piece*> SoccerStars::get_pieces()
{
    vector <Piece*> pieces;
    for (Piece* player : team_1)
        pieces.push_back(player);
    for (Piece* player : team_2)
        pieces.push_back(player);
    pieces.push_back(ball);
    return pieces;
}

void SoccerStars::handle_collisions()
{
    vector <Piece*> pieces = get_pieces();
    for (int i = 0; i < pieces.size(); i ++)
    {
        pieces[i]->reflect_if_needed();
        for (int j = i + 1; j < pieces.size(); j ++)
            if (pieces[i]->collides_with(pieces[j]))
                handle_collision(pieces[i], pieces[j]);
    }
}

void SoccerStars::switch_turns()
{
    turn = turn == 1 ? 2 : 1;
}

void SoccerStars::place_the_ball()
{
    ball->set_position(BALL_INITIAL_POSITION);
    ball->set_velocity(Vector2D(0, 0));
}

void SoccerStars::update_scores()
{
    if (scorer_team_no == TEAM_1 || scorer_team_no == TEAM_2)
    {
        goals_count[scorer_team_no] ++;
        window->play_sound_effect(GOAL_WAV);
        if (turn == scorer_team_no)
            switch_turns();
        if (goals_count[scorer_team_no] == goals_to_win)
        {
            rounds_count[scorer_team_no] ++;
            window->play_sound_effect(APPLAUSE_WAV);
            goals_count[TEAM_1] = 0;
            goals_count[TEAM_2] = 0;
            if (rounds_count[scorer_team_no] >= rounds_to_win / 2.0)
            {
                winner_team_no = scorer_team_no;
                window->play_sound_effect(CHEER_WAV);
                turn = scorer_team_no;
                game_over = true;
            }
        }
        reset();
    }
    else
        switch_turns();
}

void SoccerStars::update()
{
    handle_collisions();
    update_team(TEAM_1);
    update_team(TEAM_2);
    ball->update();
    if (mouse_released && selected_player->get_velocity() == Vector2D(0, 0))
    {
        selected_player = nullptr;
        mouse_released = false;
        scorer_team_no = ball->is_scored();
        update_scores();
    }
}

void SoccerStars::start()
{
    window->play_music(MUSIC_MP3);
    while (is_running)
    {
        handle_events();
        update();
        draw();
        delay(DELAY_TIME);
    }
}