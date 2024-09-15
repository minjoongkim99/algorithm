#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool check(int y1, int y2, int x1, int x2, const vector<vector<string>> park){
    
    for(int i = y1; i < y2; i++){
        for(int j = x1; j < x2; j++){
            if(park[i][j] != "-1") return false;
        }
    }
    return true;
}

int find(const vector<int> mats, const vector<vector<string>> park){
    
    int n = park.size();
    int m = park[0].size();
    
    for(int t = 0; t < mats.size(); t++){
        int len = mats[t];
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(i + len >= n + 1) continue;
                if(j + len >= m + 1) continue;
                if(check(i, i + len, j, j + len, park)){
                    return len;
                }
            }
        }
    }
    
    return -1;
}

int solution(vector<int> mats, vector<vector<string>> park) {
    int answer = 0;
    
    sort(mats.begin(), mats.end(), greater<int>());
    
    answer = find(mats, park);
    return answer;
}