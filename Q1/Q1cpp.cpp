#include<bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> Graph;


void find(Graph G){
    vector<int> marked(G.size(), 0);
    vector<int> parent(G.size(), -1);
    queue<int> s;

    s.push(0);
    marked[0] = 1;
    parent[0] = -1;

    while(!s.empty()){
        int v = s.front();
        s.pop();

        for(int u : G[v]){
            if(!marked[u]){
                marked[u] = 1;
                s.push(u);
            }
        }

    }
}

int get(int v, int i){
    return 4 * (v + 1) + i;
}

int num(int c){
    return (c / 4) - 1;
}



int main() {



}