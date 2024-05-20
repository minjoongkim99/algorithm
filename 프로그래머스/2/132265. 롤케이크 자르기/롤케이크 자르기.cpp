#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

int solution(vector<int> topping) {
    int answer = 0;
    if(topping.size() == 1) return 0;
    
    unordered_map <int,int> a;
    unordered_map <int,int> b;
    int st = 0, mid = 1, en = topping.size();
    
    a[topping[st]]++;
    for(int i = mid; i < en; i++){
        b[topping[i]]++;
    }
    
    //cout << a.size() << "&" << b.size() << "\n";
    while(mid < en){
    
        //cout << topping[mid] << "!\n";
        a[topping[mid]]++;
        
        if(b.find(topping[mid]) != b.end())
            b[topping[mid]]--;
        if(b[topping[mid]] == 0){
            b.erase(topping[mid]);
        }
        mid++;
        //cout << a.size() << " " << b.size() << "\n";
        if(a.size() == b.size()){
            answer++;
        }
    }
    
    return answer;
}