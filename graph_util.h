#pragma once
#include <functional>
#include <vector>
#include <queue>
#include <tuple>
#include "graph.h"

inline void bfs(std::tuple<const Graph&, const int, std::set<int>&> t, const std::function<void(int)>& f = [](int) {}) {
	const auto& [graph, v, visited] = t;
	std::queue<int> q{ { v } };
	visited.insert(v);
	while (!q.empty()) {
		const auto vertex = q.front();
		q.pop();
		f(vertex);
		for (const auto adjVertex : graph[vertex])
			if (visited.insert(adjVertex).second)
				q.push(adjVertex);
	}
}

inline bool isConnected(const Graph& graph) {
	if (graph.empty())
		return false;
	const auto v = graph.begin()->first;
	std::set<int> visited;
	bfs({ graph, v, visited });
	return graph.size() == visited.size();
}

inline std::vector<std::vector<int>> connectedComponents(const Graph& graph) {
	std::vector<std::vector<int>> components;
	std::set<int> visited;
	for (const auto& [vertex, _] : graph)
		if (!visited.contains(vertex)) {
			std::vector<int> vertices;
			bfs({ graph, vertex, visited }, [&vertices](int v) {
				vertices.push_back(v);
			});
			components.push_back(vertices);
		}
	return components;
}
