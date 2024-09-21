#include <string>
#include <vector>
#include <iostream>
using namespace std;

int sy = 0, sx = 0;
int n, m;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void move(int dir, int distance, const vector<string> park){
    int cy = sy;
    int cx = sx;
    for(int i = 1; i <= distance; i++){
        int ny = cy + dy[dir];
        int nx = cx + dx[dir];
        if(ny < 0 || ny >= n || nx < 0 || nx >= m) return;;
        if(park[ny][nx] == 'X') return;
        cy = ny;
        cx = nx;
    }
    sy = cy;
    sx = cx;
}

vector<int> solution(vector<string> park, vector<string> routes) {
    vector<int> answer;
    n = park.size();
    m = park[0].size();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(park[i][j] == 'S'){
                sy = i;
                sx = j;
                break;
            }
        }
    }
    
    for(auto e : routes){
        char dir = e[0];
        int distance = (e[2]) - '0';
        if(dir == 'N'){
            move(0, distance, park);
        }
        else if(dir == 'E'){
            move(1, distance, park);
        }
        else if(dir == 'S'){
            move(2, distance, park);
        }
        else if(dir == 'W'){
            move(3, distance, park);
        }
    }
    answer.push_back(sy);
    answer.push_back(sx);
    return answer;
}