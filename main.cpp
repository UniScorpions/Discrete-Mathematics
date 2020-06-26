#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#include "graph.h"
#include "graph_util.h"

using namespace std;

//namespace scorp {
//	string preprocess(string str) {
//		regex pattern{ "(\\w+)\\.(\\w+)\\((.+)\\)" };
//		while (regex_search(str, pattern)) 
//			str = regex_replace(str, pattern, "$2($1, $3)");
//		return str;
//	}
//}

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
	//string str = "g.connect(4, 3); g.connect(54, 5); f = g;";
	//regex reg{ R"(\s*;\s*)" };
	//std::vector<std::string> statements;
	//std::copy(std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
	//	std::sregex_token_iterator(),
	//	std::back_inserter(statements));
	//string token = R"((\d+)|(\w))";
	//const auto parser = make_parser(operators, functions, token);
	//for (const auto statement : statements)
	//	cout << parser.toPostfix(scorp::preprocess(statement)) << endl;
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