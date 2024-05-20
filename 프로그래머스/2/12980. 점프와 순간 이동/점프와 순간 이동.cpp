#include <iostream>
#include <vector>
using namespace std;


int solution(int n)
{
    ios_base::sync_with_stdio(false);
    int ans = 0, sum = n;
    
    while(sum > 0){
        if(sum % 2 == 1){
            sum = sum - 1;
            ans++;
        }
        else{
            sum = sum / 2;
        }
    }
    return ans;
}