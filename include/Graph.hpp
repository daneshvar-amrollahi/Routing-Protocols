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
    set<int> nodes;
    map<pair<int, int>, int> weight;
public:

    void add_edge(int v, int u, int w);
    void show();
    void delete_edge(int v, int u);
    void modify_edge(int v, int u, int cost);
    Graph(string topology);
    void link_state(int source);
};

vector<string> splitByDelim(string text, char delimeter);

#endif