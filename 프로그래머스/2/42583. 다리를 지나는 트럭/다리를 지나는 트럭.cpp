#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int finished = 0;
    int sum = 0;
    int idx = 0;
    int ret = 0;
    vector<pair<int,int>> road;
    int t = 1;
    
    while(true){
        if(weight >= sum + truck_weights[idx]){
            road.push_back({idx, bridge_length});
            sum += truck_weights[idx];
            idx++;
        }
        for(int i = 0; i < road.size(); i++){
            road[i].second--;
        }
        if(!road.empty() && road[0].second == 0){
            sum -= truck_weights[road[0].first];
            road.erase(road.begin());
            ret++;
        }
        t++;
        if(ret == truck_weights.size())
            break;
    }
    //cout << t << '\n';
    answer = t;
    return answer;
}