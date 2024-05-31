#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string t, string p) {
    int answer = 0;
    //int len = p.size();
    //int cmp = stoi(p);
    for(int i = 0; i < t.size() - p.size() + 1; i++){
        string str = t.substr(i, p.size());
        //cout << stoi(str) << "\n";
        if((str) <= p)
            answer++;
    }
    return answer;
}