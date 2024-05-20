#include <string>
#include <vector>
#include <bitset>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> solution(string s) {
    ios_base::sync_with_stdio(false);
    vector<int> answer;
    int change = 0, cnt = 0;

    // bitset<32> mybit; mybit.set(1);    mybit.set(2); mybit.flip(1);   
    // mybit.set();    mybit.reset();
    // bitset<32>(int?).to_string();
    
    while(true){
        if(s == "1") break;
        change++;
        
        cnt += count(s.begin(), s.end(), '0'); // #include<algorithm>
        int one = count(s.begin(), s.end(), '1');
        
        s = bitset<32>(one).to_string();  // bit<set>(integer).to_string(); 
        s = s.substr(s.find('1'));        // 무슨 의미?
    }
   
    answer.push_back(change);   answer.push_back(cnt);
    return answer;
}