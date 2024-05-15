#include <iostream>
#include <vector>
using namespace std;

int solution(int n, vector<int> s, int w)
{
    int answer = 0;
    int current = 1;
    int idx = 0;
    int len = s.size() - 1;
    while(true){
        if(current > n) break;
        //cout << current << " ";
        if(idx <= len && current >= s[idx] - w){
            current = s[idx] +  w + 1;
            idx++;
        }
        else{
            answer++;
            current = current + 2 * w + 1;
        }
    }
    
    
    return answer;
}