#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<string, int> m1;
unordered_map<int, string> m2;
unordered_map<string ,int> give;
unordered_map<string ,int> given;
unordered_map<string, int> point;
vector<vector<int>> table;
int solution(vector<string> friends, vector<string> gifts) {
    int answer = 0;
    table.resize(friends.size(), vector<int>(friends.size(), 0));
    for(int i = 0; i < friends.size(); i++){
        m1[friends[i]] = i;
        m2[i] = friends[i];
        given[friends[i]] = 0;
        give[friends[i]] = 0;
    }
    
    for(int i = 0; i < gifts.size(); i++){
        string str1, str2;
        for(int j = 0; j < gifts[i].size(); j++){
            if(gifts[i][j] == ' '){
                str1 = gifts[i].substr(0, j);
                str2 = gifts[i].substr(j + 1);
                table[m1[str1]][m1[str2]]++;
                give[str1]++;
                given[str2]++;
                break;
            }
        }
    }

    for(int i = 0; i < friends.size(); i++){
        for(int j = i + 1; j < friends.size(); j++){
            if(table[i][j] > table[j][i]){
                point[m2[i]]++;
            }
            else if(table[i][j] < table[j][i]){
                point[m2[j]]++;
            }
            else{
                if(give[m2[i]] - given[m2[i]] > give[m2[j]] - given[m2[j]]){
                    point[m2[i]]++;
                }
                if(give[m2[i]] - given[m2[i]] < give[m2[j]] - given[m2[j]]){
                    point[m2[j]]++;
                }
            }
        }
    }
    for(auto e : point){
        if(e.second > answer)
            answer = e.second;
    }
    return answer;
}