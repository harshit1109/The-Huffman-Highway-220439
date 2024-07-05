#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int directions[6][3] = {{-1, 0, 0}, {1, 0, 0},{0, -1, 0}, {0, 1, 0},{0, 0, -1}, {0, 0, 1}};

bool isValid(int x, int y, int z, int X, int Y, int Z, const vector<vector<vector<int>>>& grid, const vector<bool>& visited) {
    int index = x * Y * Z + y * Z + z;
    return x >= 0 && x < X && y >= 0 && y < Y && z >= 0 && z < Z && grid[x][y][z] == 0 && !visited[index];
}

int shortestPath3D(int X, int Y, int Z, int xs, int ys, int zs, int xd, int yd, int zd, const vector<vector<vector<int>>>& grid) {
    if (grid[xs][ys][zs] == 1 || grid[xd][yd][zd] == 1) return -1;
    
    vector<bool> visited(X * Y * Z, false);
    queue<tuple<int, int, int, int>> q;
    q.push(make_tuple(xs, ys, zs, 0));
    visited[xs * Y * Z + ys * Z + zs] = true;

    while (!q.empty()) {
        auto front = q.front();
        int x = get<0>(front);
        int y = get<1>(front);
        int z = get<2>(front);
        int dist = get<3>(front);
        q.pop();

        if(x==xd && y==yd && z==zd) return dist;

        for (const auto& dir:directions) {
            int nx = x + dir[0], ny = y + dir[1], nz = z + dir[2];
            int index = nx * Y * Z + ny * Z + nz;
            if (isValid(nx, ny, nz, X, Y, Z, grid, visited)) {
                q.push(make_tuple(nx, ny, nz, dist + 1));
                visited[index] = true;
            }
        }
    }
    return -1;
}

int main() {
    int X, Y, Z;
    cin>>X>>Y>>Z;

    int xs, ys, zs, xd, yd, zd;
    cin >> xs >> ys >> zs >> xd >> yd >> zd;

    vector<vector<vector<int>>> grid(X, vector<vector<int>>(Y, vector<int>(Z)));
    for (int x = 0; x < X; ++x) {
        for (int y = 0; y < Y; ++y) {
            for (int z = 0; z < Z; ++z) {
                cin >> grid[x][y][z];
            }
        }
    }

    int result=shortestPath3D(X,Y,Z,xs,ys,zs,xd,yd,zd,grid);
    if (result==-1) {
        cout<<"No path exists"<<endl;
    } else {
        cout<<"Shortest path length is:"<<result<<endl;
    }
}
