#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    unordered_map <string, string> m;
    unordered_map <string, int> used;
    
    for(const string & s : records){
        stringstream ss(s);
        string t, idx, type;
        ss >> t >> idx >> type;
        //cout << t << " " << idx << " " << type << "\n";
        if(type == "IN"){
            m[idx] = t;
        }
        else if(type == "OUT"){
            int last = stoi(t.substr(0, 2)) * 60 + stoi(t.substr(3,2));
            string temp = m[idx];
            int first = stoi(temp.substr(0, 2)) * 60 + stoi(temp.substr(3,2));
            //cout << last - first << "\n";
            used[idx] += last - first;
            m.erase(m.find(idx));
            //cout << last << "\n";
        }
    }
    
    for(auto e : m){
        int last = 23 * 60 + 59;
        string temp = m[e.first];
        int first = stoi(temp.substr(0, 2)) * 60 + stoi(temp.substr(3,2));
        used[e.first] += last - first;
       //m.erase(m.find(first));
    }
    

    
    vector<pair<string,int>> v(used.begin(), used.end());
    sort(v.begin(), v.end());
    for(auto e : v){
        //cout << e.first << ": " << e.second << "\n";
    }
    
    for(auto e: v){
        //cout << e.second << "!!!\n";
        if(e.second <= fees[0]){
            answer.push_back(fees[1]);
        }
        else{
            int cnt = 0;
            if((e.second - fees[0]) % fees[2]  == 0)
                cnt = (e.second - fees[0]) / fees[2];
            else
                cnt = (e.second - fees[0]) / fees[2] + 1;
            int ret = fees[1] + cnt * fees[3];
            answer.push_back(ret);
        }
    }
    return answer;
}