#include "graph.h"

Graph::Graph(const container_type& graph) : graph(graph) {}

void Graph::addVertex(int v) {
	graph.insert({ v, {} });
}

void Graph::connect(int v, int u) {
	graph[v].insert(u);
	graph[u].insert(v);
}

void Graph::removeVertex(int v) {
	graph.erase(v);
	for (auto& [_, avs] : graph)
		if (avs.contains(v))
			avs.erase(v);
}

void Graph::disconnect(int v, int u) {
	graph[v].erase(u);
	graph[u].erase(v);
}

bool Graph::areConnected(int v, int u) const {
	return graph.at(v).contains(u);
}

bool Graph::empty() const {
	return graph.empty();
}

size_t Graph::size() const {
	return graph.size();
}

Graph::const_iterator Graph::begin() const {
	return graph.begin();
}

Graph::const_iterator Graph::end() const {
	return graph.end();
}

Graph::iterator Graph::begin() {
	return graph.begin();
}

Graph::iterator Graph::end() {
	return graph.end();
}

//std::set<int>& Graph::operator[](int k) {
//	return const_cast<std::set<int>&>((*static_cast<const Graph*>(this)).operator[](k)); 
//}

const std::set<int>& Graph::operator[](int k) const {
	return graph.at(k);
}