#pragma once
#include <type_traits>
#include <iterator>
#include <set>
#include <map>

// sorting by adjacent length makes finding if connected most likely faster

class Graph {
public:
	using value_type = int;
	using container_type = std::map<int, std::set<int>>;
	using iterator = container_type::iterator;
	using const_iterator = container_type::const_iterator;

	Graph() = default;
	Graph(const container_type&);

	// methods
	template<typename InputIt>
	void connect(int, InputIt, InputIt);
	void connect(int, int);
	void addVertex(int);
	void removeVertex(int);
	void disconnect(int, int);
	bool areConnected(int, int) const;
	bool empty() const;
	size_t size() const;

	// iterators
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	// operators
	bool operator==(const Graph&) const = default;
	const std::set<int>& operator[](int) const;
	//std::set<int>& operator[](int);
private:
	std::map<int, std::set<int>> graph;
};

template<typename InputIt>
inline void Graph::connect(int at, InputIt first, InputIt last) {
	static_assert(is_same_v<value_type, iterator_traits<InputIt>::value_type>, "Value types should match");

	graph[at].insert(first, last);
	while (first != last) 
		graph[*first++].insert(at);
}
