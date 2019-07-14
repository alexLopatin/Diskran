#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

struct TVertex {
    float X;
    float Y;
    vector<int> Edges;
    TVertex(int x, int y) {
        X = x;
        Y = y;
    }
};

vector<TVertex> vertices;

float Distance(int first, int second) {
    return sqrt((vertices[first].X-vertices[second].X)
        *(vertices[first].X-vertices[second].X)
            +(vertices[first].Y-vertices[second].Y)
            *(vertices[first].Y-vertices[second].Y));
}

float AStar(int start, int finish) {
    set<int> q; // на рассмотрении
    set<int> u; // уже рассмотренные
    map<int, float> g;
    map<int, float> f;
    q.insert(start);
    g[start] = 0;
    f[start] = g[start] + Distance(start, finish);
    while(q.size() != 0) {
        float current = 0;
        float min = numeric_limits<float>::max();
        set<int>::iterator it;
        for (it = q.begin(); it != q.end(); ++it)
        {
            if(f[*it] < min) {
                min = f[*it];
                current = *it;
            }
        }
        if(current == finish) {
            return g[current];
        }
        q.erase(current);
        u.insert(current);
        for (int i = 0; i < vertices[current].Edges.size(); i++) {
            int v = vertices[current].Edges[i];
            float tentativeScore = g[current] + Distance(current, v);
            if(u.find(v) != u.end() && tentativeScore >= g[v]) {
                continue;
            }
            if(u.find(v) == u.end() || tentativeScore < g[v]) {
                g[v] = tentativeScore;
                f[v] = g[v] + Distance(start, v);
                if(q.find(v) == q.end()) {
                    q.insert(v);
                }
            }
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
	ifstream inFile(argv[1]);
    int countOfVertices, countOfEdges = 0;
    inFile >> countOfVertices >> countOfEdges;
    for ( int i = 0; i < countOfVertices; i++) {
        float x, y = 0;
        inFile >> x >> y;
        vertices.push_back(TVertex(x, y));
    }
    for ( int i = 0; i < countOfEdges; i++) {
        int first, second = 0;
        inFile >> first >> second;
        vertices[first - 1].Edges.push_back(second - 1);
        vertices[second - 1].Edges.push_back(first - 1);
    }
    int countOfQueries = 0;
    inFile >>countOfQueries;
    ofstream outFile(argv[2]); 
    for ( int i = 0; i < countOfQueries; i++) {
        int first, second = 0;
        inFile >> first >> second;
        outFile << AStar(first - 1, second - 1) << endl;
    }
    inFile.close();
    outFile.close();
}