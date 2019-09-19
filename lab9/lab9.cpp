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

set<int> comp;
 
void dfs (int v) {
    vertices[v].Color = false;
    comp.insert (v);
    for (size_t i = 0; i < vertices[v].Edges.size(); ++i) {
        int to = vertices[v].Edges[i];
        if ( vertices[to].Color) {
            dfs (to);
        }
    }
}
 
void FindComps() {
    for (int i=0; i < vertices.size(); ++i)
        if (vertices[i].Color) {
            comp.clear();
            dfs (i);
            int i = 0;
            for (const int &number : comp) {
                if( i != 0) {
                    cout << ' ';
                }
                cout << number + 1;
                i++;
            }
            cout << endl;
        }
}

int main(int argc, char *argv[]) {
    int n, m = 0;
    cin >> n >> m;
    for( int i = 0; i < n; i++) {
        vertices.push_back(TVertex());
    }
    for( int i = 0; i < m; i++) {
        int first, second = 0;
        cin >> first >> second;
        vertices[first-1].Edges.push_back(second-1);
        vertices[second-1].Edges.push_back(first-1);
    }
    FindComps();
}