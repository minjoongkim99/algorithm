#include <string>
#include <vector>

using namespace std;

int solution(int n, int m, vector<int> section) {
    int answer = 0;
    
    int st = 0;
    int en = 0;
    
    for(int i = 0; i < section.size(); i++){
        if(st <= section[i] && en >= section[i]) continue;
        else{
            answer++;
            st = section[i];
            en = st + m - 1;
        }
    }
    
    return answer;
}