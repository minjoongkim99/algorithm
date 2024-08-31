#include <string>
#include <vector>
#include <iostream>
using namespace std;


int solution(string s) {
    int answer = 0;
   
    int len = s.size();
    
    int cur = 0;
    int nxt = cur + 1;
    
    char cmp = s[cur];
    int a = 1, b = 0;
    while(true){
        if(nxt >= len) {
            answer++;
            break;
        }
        if(cur == len - 1){
            answer++;
            break;
        }
        if(cmp == s[nxt]){
            a++;
        }
        else{
            b++;
        }
        if(a == b){
            //cout << cur << " " << nxt << "!\n";
            answer++;
            cur = nxt + 1;
            if(cur >= len)
                break;
            nxt = cur + 1;
            a = 1; b = 0;
            cmp = s[cur];
        }
        else{
            nxt++;
        }
    }
    return  answer;
}