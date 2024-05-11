#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<int> solution(int n, vector<string> w) {
    vector<int> answer; // 번호 차례
    map<string, int> m;
    
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다. 
   
    string last_word = w[0];
    m[w[0]] = 1;
    int pinpoint = -1;
    for(int i = 1; i < w.size(); i++){
        if(w[i][0] != last_word[last_word.size() - 1]){
            //cout << w[i] << "break\n";
            pinpoint = i;
            break;
        }
        if(m.find(w[i]) != m.end()){
            //cout << w[i] << "break\n";
            pinpoint = i;
            break;
        }
        last_word = w[i];
        m[w[i]] = 1;
    }
    
    int x = pinpoint / n + 1;
    int y = pinpoint % n;
    
    cout << y << "," << x;
    if(y == - 1){
        answer = {0, 0};
    }
    else answer = {y + 1, x};
    return answer;
}