﻿#include <iostream>
#include <queue>
#include "Struct.h"
#include <vector>
#define C make_pair
#define fi first 
#define se second 
#define value fi.fi 
#define xx fi.se 
#define yy se.fi 
#define dir se.se  
using namespace std;
typedef pair <int, int> ii;
typedef pair<ii, ii> node;

// DIJKSTRA

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

bool check(int x, int y, int n, int c[][12]) {
    return x >= 0 && y >= 0 && x <= n + 1 && y <= n + 1 && c[x][y] == -1;
}
bool checkUseDij(Vector2 A, Vector2 B,int Size, int c[][12]) {
    vector <vector<vector<int> > > f(Size + 3,vector<vector<int> >(Size + 3,vector<int>(5,100)));
    priority_queue <node, vector<node>, greater<node> > p;
    // f[Size + 1][Size + 1][5] 
    // diretion 3th is direction with: 
    // 0 is L
    // 1 is R
    // 2 is U
    // 3 is D 

    swap(A.x, A.y);
    swap(B.x, B.y);
    f[A.x][A.y][4] = 0; // co nghia la di tu A den B quay f[x][y][k] lan
    p.push(C(C(0,A.x),C(A.y, 4)));
    while (!p.empty()) {
        node ps = p.top();
        p.pop();
        if (f[ps.xx][ps.yy][ps.dir] != ps.value) continue;
        if (ps.xx == B.x && ps.yy == B.y) return ps.value <= 3;

        for (int i = 0; i < 4; i++) {
            int X = ps.xx + dx[i];
            int Y = ps.yy + dy[i];
            if (check(X, Y, Size,c) || (X == B.x && Y == B.y)) {
                if (ps.dir != i) {
                    if (f[X][Y][i] > ps.value + 1) {
                        f[X][Y][i] = ps.value + 1;
                        p.push(C(C(f[X][Y][i],X),C(Y, i)));
                    }
                }
                else if (f[X][Y][i] > ps.value) {
                    f[X][Y][i] = ps.value;
                    p.push(C(C(f[X][Y][i], X), C(Y, i)));
                }
            }
        }
    }
    return false; 
}


