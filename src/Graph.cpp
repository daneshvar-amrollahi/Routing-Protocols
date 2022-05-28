#include "Graph.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

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
            if (weight.find(make_pair(v, u)) == weight.end())
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