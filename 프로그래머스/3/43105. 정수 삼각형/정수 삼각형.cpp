#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int n = triangle.size();
    vector<vector<int>> dp (502, vector<int>(502, 0));
    dp[0][0] = triangle[0][0];
    dp[1][0] = triangle[1][0] + dp[0][0];
    dp[1][1] = triangle[1][1] + dp[0][0];
    
    for(int h = 2; h < n; h++){
    
        for(int i = 1; i < h; i++){
            dp[h][i] = triangle[h][i] + max(dp[h - 1][i - 1], dp[h - 1][i]);
        }
        dp[h][0] = triangle[h][0] + dp[h - 1][0];
        dp[h][h] = triangle[h][h] + dp[h - 1][h - 1];
    }
    
    int ret = 0;
    for(int i = 0; i < n; i++){
        if(ret < dp[n - 1][i])
            ret = dp[n - 1][i];
    }
    
    
    return ret;
}