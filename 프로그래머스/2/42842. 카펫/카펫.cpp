#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    int total = brown + yellow;
    
    for(int v = 3; v <= sqrt(total); v++){
        if(total % v != 0) continue;
        else{
            int h = total / v;
            if(brown == (h + v - 2) * 2){
                return {h, v};
            }
        }
    }
    //return {};
    //return answer;
}