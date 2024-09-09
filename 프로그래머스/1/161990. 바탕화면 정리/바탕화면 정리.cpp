#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

bool isIn(int i, int j, int k, int l, int cnt, vector<string> wallpaper){
    int sum = 0;
    for(int x = i; x <= k; x++){
        for(int y = j; y <= l; y++){
            if(wallpaper[x][y] == '#')
                sum++;
        }
    }
    return cnt == sum;
}

vector<int> solution(vector<string> wallpaper) {
    vector<int> answer;
    
    int lux, luy, rdx, rdy;
    int distance = 1000000;
    
    int cnt = 0;
    for(int i = 0; i < wallpaper.size(); i++){
        for(int j = 0; j < wallpaper[0].size(); j++){
            if(wallpaper[i][j] == '#')
                cnt++;
        }
    }
    
    for(int i = 0; i < wallpaper.size(); i++){
        for(int j = 0; j < wallpaper[0].size(); j++){
            for(int k = i; k < wallpaper.size(); k++){
                for(int l = j; l < wallpaper[0].size(); l++){
                    if(isIn(i, j, k, l, cnt, wallpaper)){
                        if(distance > abs(i - k) + abs(j - l)){
                            distance = abs(i - k) + abs(j - l);
                            lux = i;
                            luy = j;
                            rdx = k + 1;
                            rdy = l + 1;
                        }
                    }
                    else continue;
                }
            }
        }
    }
    
    answer.push_back(lux);
    answer.push_back(luy);
    answer.push_back(rdx);
    answer.push_back(rdy);
    return answer;
}