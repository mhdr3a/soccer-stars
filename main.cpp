#include <iostream>
#include <vector>
#include "RSDL/src/rsdl.hpp"
#include "Vector2D.hpp"
#include "Piece.hpp"
#include "SoccerStars.hpp"
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    SoccerStars ss;
    ss.init(n, m);
    ss.start();
    return 0;
}