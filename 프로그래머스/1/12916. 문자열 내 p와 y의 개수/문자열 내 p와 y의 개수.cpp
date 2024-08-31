#include <string>
#include <iostream>
using namespace std;

bool solution(string s)
{
    bool answer = true;

    int p = 0, y = 0;
    
    for(auto str : s){
        if(str == 'p' || str == 'P')
            p++;
        if(str == 'y' || str == 'Y')
            y++;
    }
    
  
    if(p != y)
        answer = false;
    
    return answer;
}