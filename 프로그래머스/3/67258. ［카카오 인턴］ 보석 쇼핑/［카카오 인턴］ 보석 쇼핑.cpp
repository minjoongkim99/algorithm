#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    answer.push_back(0); answer.push_back(0);
    unordered_map <string, int> m;
    
    for(int i = 0; i < gems.size(); i++){
        if(m.find(gems[i]) != m.end()) continue;
        else{
            m[gems[i]] = 0;
        }
    }
    
    int len = gems.size(); // 보석함 길이
    int cnt = m.size();    // 보석의 개수
    int ret = len + 1; // 결과 반환하기.
    int cur = 0, st = 0, en = 0;

    while(en < len){

        if(m[gems[en]] == 0){
            cur++;
        }
        m[gems[en]]++;
        
        if(cur == cnt){
            while(st <= en){
                if(m[gems[st]] == 1)
                    break;
                m[gems[st]]--;
                st++;
            }
            
            if(ret > en - st + 1){
                ret = en - st + 1;
                answer[0] = st + 1;     answer[1] = en + 1;
            }
        }
        en++;
    }
    
    return answer;
}