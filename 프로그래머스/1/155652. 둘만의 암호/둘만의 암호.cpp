#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

string solution(string str, string skip, int index) {
    string answer = "";
    unordered_set<char> st;
  
    for(char s: skip)
        st.insert(s);
    
    for(char s : str){
        int cnt = 0;
        for(int i = 1; i <= 200; i++){
            int cur = s - 'a';
            int nxt = (cur + i) % 26;
            char t = (char)('a' + nxt);
           
            if(st.find(t) != st.end()) continue;
            else{
                cnt++;
            }
            if(cnt == index){
                answer += t;
                break;
            }
        }
       
    }
    return answer;
}