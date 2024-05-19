#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

vector<int> solution(int n, vector<string> words) {
    ios_base::sync_with_stdio(false);
    vector<int> answer;
    
    char last_word = words[0][words[0].size() - 1];
    unordered_set<string> s;
    s.insert(words[0]);
    int idx = -1;
    
    for(int i = 1; i < words.size(); i++){
        
        string word = words[i];
        if(last_word != word[0]){
            idx = i;
            break;
        }
        if(s.find(word) != s.end()){
            idx = i;
            break;
        }
        s.insert(word);
        last_word = word[word.size() - 1];
    }
    
    int number = idx % n + 1;
    int cnt = idx / n + 1;
    
    if(idx == -1){
        answer.push_back(0);
        answer.push_back(0);
    }
    else{
        answer.push_back(number);
        answer.push_back(cnt);
    }
    return answer;
}