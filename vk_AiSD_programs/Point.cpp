
#include <random>
#include <cmath>
#include "Point.h"
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dist(-1.0, 1.0);
Point::Point(double x, double y) : x(x), y(y)
{
}
std::vector<Point> GeneratePoint(int N)
{
    std::vector<Point> points;
    while (points.size() < N)
    {
        double u = dist(gen);
        double v = dist(gen);
        double s = u * u + v * v;
        if (s != 0 && s <= 1)
        {
            double cor = std::sqrt(-2 * std::log(s) / s);
            u = u * cor;
            v = v * cor;
            points.push_back(Point(u, v));
        }
    }
    return points;
}
double GetDistance(Point a, Point b)
{
    double del_x = a.x - b.x;
    double del_y = a.y - b.y;
    return std::sqrt((del_x * del_x + del_y * del_y));
}

