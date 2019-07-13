#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

struct TVertex {
    bool Color = 1;
    vector<int> Edges;
};

vector<TVertex> vertices;

set<int> DFS(TVertex u) {
    set<int> result;
    for(int i = 0; i < u.Edges.size(); i++) {
        if(vertices[u.Edges[i]].Color) {
            vertices[u.Edges[i]].Color = 0;
            result.insert(u.Edges[i] + 1);
            set<int> subResult = DFS(vertices[u.Edges[i]]);
            result.insert(subResult.begin(), subResult.end());
        }
    }
    return result;
}

vector<set<int>> FindComponents() {
    vector<set<int>> result;
    for( int i = 0; i < vertices.size(); i++) {
        if(vertices[i].Color) {
            set<int> component = DFS(vertices[i]);
            component.insert(i + 1);
            vertices[i].Color = 0;
            result.push_back(component);
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
	ifstream inFile(argv[1]);
    int n, m = 0;
    inFile >> n >> m;
    for( int i = 0; i < n; i++) {
        vertices.push_back(TVertex());
    }
    for( int i = 0; i < m; i++) {
        int first, second = 0;
        inFile >> first >> second;
        vertices[first-1].Edges.push_back(second-1);
        vertices[second-1].Edges.push_back(first-1);
    }
    inFile.close();
    vector<set<int>> result = FindComponents();
    ofstream outFile(argv[2]); 
    for( int i = 0; i < result.size(); i++) {
        set<int>::iterator it;
        for (it = result[i].begin(); it != result[i].end(); ++it) {
            outFile << *it << ' ';
        }
        outFile << endl;
    }
    outFile.close();
}