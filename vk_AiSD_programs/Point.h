#pragma once
struct Point
{
public:
    Point(double x, double y);
    double x;
    double y;
};
double GetDistance(Point a, Point b);
std::vector<Point> GeneratePoint(int N);


