/*
1) реализовать алгоритмы Крускала и Прима
2) реализовать pre-oreder обход не забудь обойти всех потомков
3) реализовать полный перебор
4) реализовать генерацию рандомных точек убедится, что неравенство триугольника всегда выполняется
5) соеденить все вместе сделать вывод ско и ср знач
*/
#include <iostream>
#include <vector>
#include "TSP_approximate.h"
#include "TSP_brute_force.h"
#include "Graps.h"
#include "Point.h"

int main(int argc, const char* argv[]) {
    for (int N =5; N<11;N++)
    {
		std::vector<double> X;
		int K = 50;
        for (size_t i = 0; i < K; i++)
        {
			ArcGraph arcGraph(N);
			MatrixGraph Matrix(N);
			std::vector<Point> points = GeneratePoint(N);
			for (size_t i = 0; i < N; i++)
			{
				//std::cout << points[i].x << ' ' << points[i].y;
				for (size_t j = i+1; j < N; j++)
				{
					double distance = GetDistance(points[i], points[j]);
					arcGraph.AddEdge(i, j, distance);
					Matrix.AddEdgeTwice(i, j, distance);
					
				}
				//std::cout << std::endl;
			}
			//std::cout << "TSP:"<<std::endl;
			double C = TSP_approximate(arcGraph, Matrix);
			double C0 = TSP_brute_force(Matrix);
			//std::cout << C << ' ' << C0 << std::endl;
			double x = std::max(C / C0, C0 / C);
			//std::cout << x << std::endl;
			X.push_back(x);
			
        }
		double sum = 0;
		for (double val : X)
		{
			sum += val;
		}
		double sr = sum / K;
		double sko_sum = 0;
		for (double val : X)
		{
			sko_sum += (val - sr) * (val - sr);
		}
		double sko = std::sqrt(sko_sum / (K-1));
		std::cout << "N:" << N << std::endl;
		std::cout << "SR:" << sr << std::endl;
		std::cout << "SKO:" << sko << std::endl;
    }
    return 0;
}
