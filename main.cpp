#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#include "graph.h"
#include "graph_util.h"

using namespace std;

Graph graphFromFile(const string& fileName) {
	ifstream file{ fileName };
	Graph graph;
	for (string line; getline(file, line);) {
		istringstream iss(line);
		int vertex;
		iss >> vertex;
		iss.ignore(numeric_limits<streamsize>::max(), '|');
		std::vector<int> v{
			std::istream_iterator<int>{ iss },
			std::istream_iterator<int>{}
		};
		graph.connect(vertex, v.begin(), v.end());
	}
	return graph;
}

int main() {
	auto fileName = "input.txt";
	auto g = graphFromFile(fileName);
	if (isConnected(g))
		cout << "Graph is connected" << endl;
	else {
		cout << "Graph is not connected" << endl;
		cout << "Graph's connected components are: " << endl;
		for (const auto& component : connectedComponents(g)) {
			for (const auto& vertex : component)
				cout << vertex << ' ';
			cout << endl;
		}
	}
}
