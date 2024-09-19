#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for(int query = 0; query < commands.size(); query++){
        int i = commands[query][0];
        int j = commands[query][1];
        int k = commands[query][2];
        
        vector<int> v;
        for(int len = i - 1; len < j; len++){
            v.push_back(array[len]);
        }
        
        sort(v.begin(), v.end());

        answer.push_back(v[k - 1]);
        
    }
    return answer;
}