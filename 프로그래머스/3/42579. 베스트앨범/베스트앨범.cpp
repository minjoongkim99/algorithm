#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if(a.first == b.first)
        return a.second < b.second;
    else return a.first > b.first;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    map<string, int> m;
    map<int, string, greater<>> g_cnt; // 장르 개수 총합 오름차순으로.
    map<string, vector<pair<int,int>>> ret;
    int len = plays.size();
    for(int i = 0; i < len; i++){
        m[genres[i]] += plays[i];
        ret[genres[i]].push_back({plays[i], i});
    }

    for(auto e : m){
        g_cnt[e.second] = e.first;
    }
    for(auto e : g_cnt){
        string src = e.second;
        //cout << src << ": ";
        vector<pair<int,int>> v(ret[src].begin(), ret[src].end());
        sort(v.begin(), v.end(), cmp);
        for(int i = 0; i < v.size(); i++){
            if(i > 1) break;
            //cout << v[i].first << "," << v[i].second << " ";
            answer.push_back(v[i].second);
        }
        
    }
    // gernes 많은것들로 오름차순 정렬.
    
    return answer;
}