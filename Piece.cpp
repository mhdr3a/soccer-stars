#include "Piece.hpp"
using namespace std;

const int FIELD_WIDTH = 800;
const int WINDOW_WIDTH = FIELD_WIDTH;
const int FIELD_HEIGHT = 480;
const int SCOREBOARD_HEIGHT = 100;
const int WINDOW_HEIGHT = FIELD_HEIGHT + SCOREBOARD_HEIGHT;
const int PLAYER = 2;
const int BALL = 1;
const int TEAM_1 = 1;
const int TEAM_2 = 2;
const int NONE = 0;
const int R_BALL = 12;
const int DELAY_TIME = 15;
const double FRICTION = 300;
const double WALL_THRESHOLD = 0;
const double GOAL_THRESHOLD = 10;
const double VELOCITY_THRESHOLD = 5;

Piece::Piece(double m, Vector2D p, Vector2D v, double r, int t)
{
    mass = m;
    position = p;
    velocity = v;
    radius = r;
    type = t;
}

bool Piece::has_point(Point p)
{
    return pow(p.x - position.x, 2) + pow(p.y - position.y, 2) <= pow(radius, 2);
}

void Piece::update()
{
    if (velocity.length() < VELOCITY_THRESHOLD)
        velocity = Vector2D(0, 0);
    else
    {
        position += velocity * (DELAY_TIME / 1000.0);
        velocity += velocity.sgn() *
            Vector2D(-abs(velocity.x) / velocity.length(), -abs(velocity.y) / velocity.length()) *
            (FRICTION * DELAY_TIME / 1000.0);
    }  
}

void Piece::draw(Window* window, string src)
{
    window->draw_img(src,
        Rectangle(position.x - radius, position.y - radius, 2 * radius, 2 * radius));
}

Vector2D Piece::get_position()
{
    return position;
}

void Piece::set_position(Vector2D pi)
{
    position = pi;
}

double Piece::get_mass()
{
    return mass;
}

void Piece::set_velocity(Vector2D vi)
{
    velocity = vi;
}

Vector2D Piece::get_velocity()
{
    return velocity;
}

double Piece::get_radius()
{
    return radius;
}

bool Piece::collides_with(Piece* b)
{
    return (position - b->position).length() < radius + b->get_radius();
}

int Piece::is_scored()
{
    double x = position.x, y = position.y;
    if (x + radius <= GOAL_THRESHOLD)
        return TEAM_2;
    else if (x - radius >= WINDOW_WIDTH - GOAL_THRESHOLD)
        return TEAM_1;
    return NONE;
}

void Piece::reflect_if_needed()
{
    double x = position.x, y = position.y;
    if (x - radius < WALL_THRESHOLD || x + radius > (WINDOW_WIDTH - WALL_THRESHOLD))
        if (type != BALL
            || y > WINDOW_HEIGHT - FIELD_HEIGHT + 320 - radius
            || y < WINDOW_HEIGHT - FIELD_HEIGHT + 160 + radius)
            velocity.x = -(velocity.x);
    if (y - radius < (SCOREBOARD_HEIGHT + WALL_THRESHOLD) || y + radius > (WINDOW_HEIGHT - WALL_THRESHOLD))
        velocity.y = -(velocity.y);
}