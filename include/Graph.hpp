#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <vector>
#include <utility>
#include <string>
#include <set>
#include <map>

using namespace std;

class Graph
{
private:
    const static int maxNodes = 1e5 + 10;
    set<int> nodes;
    map<pair<int, int>, int> weight;
public:

    void add_edge(int v, int u, int w);
    void show();
    Graph(string topology);
};

#endif