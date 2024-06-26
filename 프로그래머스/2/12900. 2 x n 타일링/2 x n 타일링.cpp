#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    vector<int> v (n + 1, 0);
    int answer = 0;
    
    v[1] = 1;
    v[2] = 2;
    for(int i = 3; i <= n; i++){
        v[i] = (v[i -1] + v[i - 2]) % 1000000007;
    }
    answer = v[n];
    return answer;
}