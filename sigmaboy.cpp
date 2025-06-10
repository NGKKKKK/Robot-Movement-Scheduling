#include <bits/stdc++.h>
using namespace std;

int INF = 1e9;

//Thuật toán Floyd-Warshall O(n^3) - Tham khảo
vector<vector<int>> FW(int n, const vector<vector<int>>& adj){
    vector<vector<int>> dist(n, vector<int>(n,INF));
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (adj[i][j] == 0 || adj[i][j] == INF) continue;
            dist[i][j] = adj[i][j];
        }
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            for (int k = 0; k < n; ++k){
                if (dist[j][i] < INF && dist[i][k] < INF) dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }
    return dist;
}

void BFS(int a, int b, int c, int d, int r, const vector<vector<int>>& adj, const vector<vector<int>>& dist, int n){
    if (dist[a][b] <= r){
        cout << "Cannot!" << endl;
        return;
    }
    queue<pair<int,int>> que;
    map<pair<int,int>, pair<int,int>> trace;
    vector<vector<bool>> visited(n, vector<bool>(n,false));
    pair<int,int> start = {a,b};
    pair<int,int> end = {c,d};
    que.push(start);
    visited[a][b] = true;
    bool exist = false;
    while (!que.empty()){
        pair<int,int> cur = que.front();
        que.pop();
        int i = cur.first;
        int j = cur.second;
        if (cur == end){
            exist = true;
            break;
        }
        for (int i_new = 0; i_new < n; ++i_new){
            if (adj[i][i_new] == 0 || adj[i][i_new] == INF) continue;
            pair<int,int> nextPos = {i_new, j};
            if (visited[i_new][j] || dist[i_new][j] <= r) continue;
            visited[i_new][j] = true;
            trace[nextPos] = cur;
            que.push(nextPos);
        }
        for (int j_new = 0; j_new < n; ++j_new){
            if (adj[j][j_new] == 0 || adj[j][j_new] == INF) continue;
            pair<int,int> nextPos = {i, j_new};
            if (visited[i][j_new] || dist[i][j_new] <= r) continue;
            visited[i][j_new] = true;
            trace[nextPos] = cur;
            que.push(nextPos);
        }
    }
    if (!exist){
        cout << "Cannot!" << endl;
        return;
    }
    cout << "Movement Schedule" << endl;
    vector<pair<int,int>> path;
    pair<int,int> curr = end;
    while (curr != start){
        path.push_back(curr);
        curr = trace[curr];
    }
    path.push_back(start);
    int sz = path.size();
    for (int indx = sz-1; indx >= 0; --indx){
        cout << path[indx].first << " " << path[indx].second << endl;
    }
}

int main(){
    cout << "INPUT: " << endl;
    int n,m;
    cout << "Enter n = "; cin >> n;
    cout << "Enter m = "; cin >> m;
    vector<vector<int>> adj(n, vector<int>(n,INF));
    for (int i = 0; i < n; ++i) adj[i][i] = 0;
    for (int i = 0; i < m; ++i){
        int x, y, w;
        cout << "Enter x  y  w = ";
        cin >> x >> y >> w;
        adj[x][y] = adj[y][x] = w;
    }
    int a, b, c, d;
    cout << "Enter a b c d = ";
    cin >> a >> b >> c >> d;
    int r;
    cout << "Enter r = ";cin >> r;
    cout << endl;
    cout << "OUTPUT:" << endl;
    vector<vector<int>> minDist = FW(n, adj);
    BFS(a,b,c,d,r,adj,minDist,n);
    return 0;
}
