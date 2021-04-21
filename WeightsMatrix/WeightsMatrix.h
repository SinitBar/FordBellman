#pragma once
#include "Queue.h"
#include <fstream>
#include <stdexcept>
#include <float.h>
#define INF (DBL_MAX) // to declare infinity value for not-existing nodes
using namespace std;
class WeightsMatrix
{
	size_t Size; // amount of cities, size^2 = size of weights matrix
	string* Cities; // an array of declared cities // indexes of cities are like their keys 
	double** Weights; // a matrix of weights // indexes means cities, i - from what city, j - to what city
	void set_size(size_t);
	void set_cities(string*);
	void set_weights(double**);
	WeightsMatrix();
public:
	WeightsMatrix(string); // parameter = name of the file with data in required format
	size_t get_size();
	string* get_cities();
	double** get_weights();
	size_t get_city_index(string);
	double FordBellman(string, string); // parameters = city from and to where between which the minimum distance is searched
};