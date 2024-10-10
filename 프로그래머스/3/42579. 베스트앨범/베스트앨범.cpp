#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if(a.first > b.first)
        return true;
    else if(a.first < b.first)
        return false;
    if(a.first == b.first)
        return a.second < b.second;
    //else return a.first > b.first;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    ios_base::sync_with_stdio(false);
    
    map<string, int> m;
    map<int, string, greater<>> g_cnt; // 장르 개수 총합 오름차순으로.
    map<string, vector<pair<int,int>>> ret;
  
    for(int i = 0; i < plays.size(); i++){
        m[genres[i]] += plays[i];
        ret[genres[i]].push_back({plays[i], i});
    }

    for(auto e : m){
        g_cnt[e.second] = e.first;
    }
    
    vector<int> answer;
    for(auto e : g_cnt){
        string src = e.second;
    
        vector<pair<int,int>> v(ret[src].begin(), ret[src].end());
        sort(v.begin(), v.end(), cmp);
        
        for(int i = 0; i < v.size(); i++){
            if(i > 1) 
                break;
            answer.push_back(v[i].second);
        }
    }
    
    return answer;
}