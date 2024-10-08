#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(int a, int b){
    string str1 = to_string(a);
    string str2 = to_string(b);
    
    if(str1 + str2 > str2 + str1) return true;
    else return false;
}
string solution(vector<int> numbers) {
    string answer = "";
    
    sort(numbers.begin(), numbers.end(), cmp);
    
    for(auto e : numbers){
        answer += to_string(e);
    }
    if(answer[0] == '0') return "0";
    return answer;
}