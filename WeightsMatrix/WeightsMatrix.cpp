#include "WeightsMatrix.h"

void WeightsMatrix::set_size(size_t size) { Size = size; }
void WeightsMatrix::set_cities(string* cities) { Cities = cities; }
void WeightsMatrix::set_weights(double** weights) { Weights = weights; }
WeightsMatrix::WeightsMatrix()
{
	Size = 0;
	Cities = nullptr;
	Weights = nullptr;
}
WeightsMatrix::WeightsMatrix(string filename) // parameter = filename
{
	set_size(0);
	fstream in(filename);
	if (!in.is_open())
		throw invalid_argument("file doesn't exist");
	// firstly fill array of cities
	// for that use queue
	Queue<size_t, string> cities;
	string city;
	while (in.peek() != EOF)
	{
		city = "";
		while (in.peek() != ';') // read the name of the city from
			city += in.get();
		if (cities.search_key(city) == -1) // if city is still not in queue of cities
			cities.push(city); // add it to cities
		in.get(); // read ';'
		city = "";
		while (in.peek() != ';') // read the name of the city to
			city += in.get();
		if (cities.search_key(city) == -1)
			cities.push(city);
		while ((in.peek() != '\n') && (in.peek() != EOF))
			in.get();
		if (in.peek() == '\n') // read '\n'
			in.get();
	}
	set_size(cities.size());
	Cities = new string[get_size()]; //going to fill cities with cities from queue
	for (size_t i = 0; i < get_size(); i++)
		Cities[i] = cities.pop()->get_data();
	// filled Cities, now can declare the size of the weights matrix
	Weights = new double* [get_size()];
	for (size_t i = 0; i < get_size(); i++)
		Weights[i] = new double[get_size()];
	// now going to initialize weights matrix with zeros for elements on the diagonal and with INF on other positions
	for (size_t i = 0; i < get_size(); i++)
	{
		for (size_t j = 0; j < get_size(); j++)
		{
			if (i == j)
				Weights[i][j] = 0;
			else
				Weights[i][j] = INF;
		}
	}
	in.close();
	in.open(filename);
	while (in.peek() != EOF)
	{
		size_t index_from, index_to; // indexes of cities in Cities
		double forward_cost, backward_cost;
		string info = "";
		while (in.peek() != ';') // read city from
			info += in.get();
		index_from = get_city_index(info);
		in.get(); // read ';'
		info = "";
		while (in.peek() != ';') // read city to
			info += in.get();
		index_to = get_city_index(info);
		in.get(); // read ';'
		if (in.peek() == 'N')
		{
			forward_cost = INF; // unreal cost
			while (in.get() != ';') {}
		}
		else
		{
			in >> forward_cost;
			in.get(); // read ';'
		}
		if (in.peek() == 'N')
		{
			backward_cost = INF; // unreal cost
			for (int i = 0; i < 3; i++)
				in.get(); // read "N/A"
		}
		else
			in >> backward_cost;
		if (in.peek() == '\n') // read '\n'
			in.get();
		if (forward_cost < INF)
			Weights[index_from][index_to] = forward_cost;
		if (backward_cost < INF)
			Weights[index_to][index_from] = backward_cost;
		// filled weights matrix
	}
}
size_t WeightsMatrix::get_size() { return Size; }
string* WeightsMatrix::get_cities() { return Cities; }
double** WeightsMatrix::get_weights() { return Weights; }

size_t WeightsMatrix::get_city_index(string city)
{
	for (size_t i = 0; i < get_size(); i++)
	{
		if (Cities[i] == city)
			return i;
	}
	return -1; // in case of not-existing city return unreal index
}

double WeightsMatrix::FordBellman(string source_city, string target_city)
{
	ofstream out("out.txt");
	size_t source = get_city_index(source_city);
	size_t target = get_city_index(target_city);
	if (source == -1)
	{
		out << "the source city doesn't exist" << endl;
		throw invalid_argument("the source city doesn't exist");
	}
	if (target == -1)
	{
		out << "the target city doesn't exist" << endl;
		throw invalid_argument("the target city doesn't exist");
	}
	double min_cost = INF; // too big, unreal, cost of the flight between source and target cities
	size_t* marks = new size_t[get_size()]{ source }; // remember indexes that means cities from what we came to indexed here city 
	double** W = new double* [get_size()]; // create a copy of the original weights matrix to keep it safe
	for (size_t i = 0; i < get_size(); i++)
		W[i] = new double[get_size()];
	for (size_t i = 0; i < get_size(); i++)
	{
		for (size_t j = 0; j < get_size(); j++)
			W[i][j] = get_weights()[i][j];
	}
	size_t phase = 0;
	for (; phase < get_size(); phase++) // guaranteed stops after size-1 times, so the last one shouldn't be reached because of variable is_improoved 
	{
		bool is_improoved = false;
		for (size_t node = 0; node < get_size(); node++)
		{
			for (size_t to = 0; to < get_size(); to++)
			{
				if (W[source][to] > W[source][node] + W[node][to])
				{
					W[source][to] = W[source][node] + W[node][to];
					marks[to] = node;
					is_improoved = true;
				}
			}
		}
		if (!is_improoved) // if on current phase wasn't any improvements
			break;
	}
	if (phase == get_size()) // unreal, so exists a negative cycle
	{
		out << "There is a negative cycle, program stops working." << endl;
		throw invalid_argument("Found negative cycle");
	}
	min_cost = W[source][target];
	
	if (min_cost >= INF)
	{
		out << target_city << " can't be reached from " << source_city << endl;
		throw invalid_argument("path doesn't exist");
	}
	out << "minimum cost of reaching " << target_city << " from " << source_city << " is " << W[source][target] << endl;
	// going to restore the way and print it to the file
	size_t* reversed_way = new size_t[get_size()]{ source }; // an array saving indexes of cities in reversed order 
	size_t city = target;
	int i = 0;
	while (city != source)
	{
		reversed_way[i] = city;
		city = marks[city];
		i++;
	}
	reversed_way[i] = source;
	out << "the way:" << endl;
	for (int k = i; k >= 0; k--)
	{
		out << get_cities()[reversed_way[k]];
		if (k != 0)
			out << " -> ";
	}
	out.close();
	return W[source][target];
}