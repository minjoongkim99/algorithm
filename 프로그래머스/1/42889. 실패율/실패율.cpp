#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(pair<int,float> & a, pair<int,float> &b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    else return a.second > b.second;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<int> arr(N + 2, 0);
    vector<pair<int, float>> v;
    for(auto e : stages){
        arr[e]++;
    }
    
 
    int len = stages.size();

    for(int i = 1; i < arr.size() - 1; i++){
        if(len == 0){
            v.push_back({i, 0});
            continue;
        }
        float failure = (float)arr[i] / (float)len;
        v.push_back({i, failure});
        len -= arr[i];
    }
    
    sort(v.begin(), v.end(), cmp);
    for(auto e : v){
        //cout << v[i].first << " " << v[i].second << "\n";
        answer.push_back(e.first);
    }
    
    
    return answer;
}