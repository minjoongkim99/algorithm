#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int arr[15];
vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    int people = orders.size(); // 20이하
    int len_min = course[0];
    int len_max = course[course.size() - 1];
    
    for(int i = 0; i < orders.size(); i++){
        sort(orders[i].begin(), orders[i].end());
    }
    
    //cout << len_min << " " << len_max << "\n";
    
    for(int k = 0; k < course.size(); k++){
        int len = course[k];
        unordered_map<string, int> m;
        
        for(int i = 0; i < orders.size(); i++){
            int n = orders[i].size();
            if(len > n) continue;
            
            fill(&arr[0], &arr[0] + 15, 1);
            for(int tmp = 0; tmp < len; tmp++)
                arr[tmp] = 0;
            
            do{
                string str = "";
                for(int j = 0; j < n; j++){
                    if(arr[j] == 0)
                        str += orders[i][j];
                }
                cout << str << " ";
                m[str]++;
            }while(next_permutation(arr, arr + n));
            
           cout << "\n";
        }
        
        int ret = 1;
        for(auto e : m){
            if(e.second > ret){
                ret = e.second;
            }
        }
        if(ret == 1) continue;
        for(auto e : m){
            if(e.second == ret){
                answer.push_back(e.first);
            }
        }
    }
    
    sort(answer.begin(), answer.end());
    return answer;
}