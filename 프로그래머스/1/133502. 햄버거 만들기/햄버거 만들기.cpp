#include <string>
#include <vector>

using namespace std;

vector<int> v;
int solution(vector<int> ingredient) {
    int answer = 0;
    
    for(int i : ingredient){
        v.push_back(i);
        if(v.size() > 3){
           if(v[v.size() - 1] == 1 && v[v.size() - 2] == 3 &&  v[v.size() - 3] == 2 && v[v.size() - 4] == 1){
               for(int j = 0; j < 4; j++)
                   v.pop_back();
               answer++;
           }
        }
    }
    return answer;
}