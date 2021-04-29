#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include <iostream>
#include "RSDL/src/rsdl.hpp"
#include "Vector2D.hpp"

class Piece
{
public:
    Piece(double m, Vector2D p, Vector2D v, double r, int t);
    bool has_point(Point p);
    void update();
    void draw(Window* window, std::string src);
    Vector2D get_position();
    void set_position(Vector2D pi);
    double get_mass();
    void set_velocity(Vector2D vi);
    Vector2D get_velocity();
    double get_radius();
    bool collides_with(Piece* b);
    int is_scored();
    void reflect_if_needed();
private:
    double mass;
    Vector2D position;
    Vector2D velocity;
    double radius;
    int type;
};

#endif