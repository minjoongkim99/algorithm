#include <string>
#include <vector>

using namespace std;

int solution(string A, string B) {
    int answer = -1;
        
    for(int i = 0; i < A.size(); i++){
        string tmp = "";
        for(int j = 0; j < A.size(); j++){
            tmp += A[(j + (A.size() - i)) % A.size()];
        }
        if(tmp == B){
            answer = i;
            break;
        }
    }
    return answer;
}