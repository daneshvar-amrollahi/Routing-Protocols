#include "Graph.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std;

const int INF = 1e9;

vector<string> splitByDelim(string text, char delimeter)
{
    string cur = "";
    vector<string> words;
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == delimeter)
        {
            words.push_back(cur);
            cur = "";
        }
        else
        cur += text[i];
    }
    words.push_back(cur);
    return words;
}

Graph::Graph(string topology) 
{
    vector<string> words = splitByDelim(topology, ' ');
    for (auto word: words)
    {
        vector<string> edge = splitByDelim(word, '-');
        int v = stoi(edge[0]);
        int u = stoi(edge[1]);
        int w = stoi(edge[2]);

        add_edge(v, u, w);
        add_edge(u, v, w);
        nodes.insert(v);
        nodes.insert(u);
    }
}

void Graph::add_edge(int v, int u, int w)
{   
    weight[make_pair(v, u)] = w;
    weight[make_pair(u, v)] = w;
}

int getDigitCount(int x)
{
    if (x == 0)
        return 1;
    int res = 0;
    while (x)
    {
        x /= 10;
        res++;
    }
    return res;
}

void Graph::show()
{
    cout << "u|v |";
    for (auto node: nodes)
    {
        int col = 4 - getDigitCount(node);
        for (int i = 0; i < col; i++)
            cout << " ";
        cout << node;
        cout << "|";
    }
    cout << endl;
    //(nodes.size() + 1) * 5: row count

    for (int i = 0; i < (nodes.size() + 1) * 5; i++)
        cout << "-";
    cout << endl;

    for (auto v: nodes)
    {
        for (int i = 0; i < 4 - getDigitCount(v); i++)
            cout << " ";
        cout << v << "|";

        for (auto u: nodes)
        {
            int w, col;
            if(u == v)
            {
                col = 3;
                w = 0;
            }
            else if (weight.find(make_pair(v, u)) == weight.end())
            {
                col = 2;
                w = -1;
            }
            else
            {
                w = weight[make_pair(v, u)];
                col = 4 - getDigitCount(w);
                if (w <= 0)
                    col--;
            }
            
            for (int i = 0; i < col; i++)
                cout << " ";
            cout << w << "|";
        }
        cout << endl;
    }
}

void Graph::delete_edge(int v, int u){
    weight.erase(make_pair(u,v));
    weight.erase(make_pair(v,u));
}

void Graph::modify_edge(int v, int u, int cost){
    weight[make_pair(v,u)]=cost;
    weight[make_pair(u,v)]=cost;
}

void Graph::link_state(int source)
{
    auto start = std::chrono::steady_clock::now();

    int n = nodes.size();
    vector<bool> mark(n + 1, false);
    vector<int> dist(n + 1, INF);
    vector<int> par(n + 1, -1);

    for (auto v: nodes)
    {
        if (weight.find(make_pair(source, v)) != weight.end())
        {
            dist[v] = weight[make_pair(source, v)];
            par[v] = source;
        }
        else
            dist[v] = INF;
    }

    mark[source] = true;
    dist[source] = 0;
    int sz = 1;
    while (sz < n)
    {
        int mn = INF, v;
        for (auto node: nodes)
        {
            if (mark[node])
                continue;
            if (dist[node] < mn)
            {
                mn = dist[node];
                v = node;
            }
        }

        cout << "   |Iter " + to_string(sz) << ":" << endl;
        cout << "Dest|";
        for (auto node: nodes)
        {
            int col = 4 - getDigitCount(node);
            for (int i = 0; i < col; i++)
                cout << " ";
            cout << node << "|";
        }
        cout << endl;
        cout << "Cost|";
        for (auto node: nodes)
        {
            int col = 4 - getDigitCount(dist[node]);
            if (dist[node] == INF)
                col = 2;
            for (int i = 0; i < col; i++)
                cout << " ";
            cout << (dist[node] == INF ? -1 : dist[node]) << "|";
        }
        cout << endl;
        for (int i = 0; i < (nodes.size() + 1) * 5; i++)
            cout << "-";
        cout << endl;

        mark[v] = true;
        sz += 1;
        for (auto node: nodes)
        {
            if (mark[node])
                continue;
            if (weight.find(make_pair(v, node)) == weight.end())
                continue;
            if (dist[v] + weight[make_pair(v, node)] < dist[node])
            {
                dist[node] = dist[v] + weight[make_pair(v, node)];
                par[node] = v;
            }
        }  
    }


    string path;
    cout<<"\nPath: [s] -> [d]         Min-Cost         Shortest Path"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for (auto node: nodes)
    {
        path="";
        if (node == source)
            continue;
        cout << "    [" << source << "] -> [" << node << "]";
        int col = 15 - getDigitCount(node);
        for (int i = 0; i < col; i++)
            cout << " ";
        cout<<dist[node];
        col= 15 - getDigitCount(dist[node]);
        for (int i = 0; i < col; i++)
                cout << " ";
        int p = node;
        while (par[p] != -1)
        {   
            path=" -> "+to_string(p)+path;
            p = par[p];
        }
        cout << to_string(source) << path << endl;
    }

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();
    cout << "Elapsed: " << elapsed_seconds << endl;
}

void Graph::distance_vector(int source)
{
    auto start = std::chrono::steady_clock::now(); 

    int n = nodes.size();
    vector<bool> mark(n + 1, false);
    vector<int> dist(n + 1, INF);
    vector<int> par(n + 1, -1);

    dist[source] = 0;


    while (1)
    {
        bool updated = false;
        for (map<pair<int, int>, int> :: iterator it = weight.begin(); it != weight.end(); it++)
        {
            int v = it->first.first, u = it->first.second, w = it->second;
            if (dist[v] + w < dist[u])
            {
                dist[u] = dist[v] + w;
                par[u] = v;
                updated = true;
            }
        }
        if (!updated)
            break;
    }


    string path;
    int prev_p;
    cout<<"\nDest         NextHop         Dist         Shortest Path"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for (auto node: nodes)
    {
        path="";
        if (node == source)
            continue;
        cout <<  node ;
        int col = 15 - getDigitCount(node);
        for (int i = 0; i < col; i++)
            cout << " ";
        int p = node;
        while (par[p] != -1)
        {   
            path=" -> "+to_string(p)+path;
            prev_p=p;
            p = par[p];
        }

        cout<<prev_p;
        col= 15 - getDigitCount(prev_p);
        for (int i = 0; i < col; i++)
                cout << " ";

        cout<<dist[node];
        col= 12 - getDigitCount(dist[node]);
        for (int i = 0; i < col; i++)
                cout << " ";

        cout << to_string(source) << path << endl;
    }

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();
    cout << "Elapsed: " << elapsed_seconds << endl;
}