#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = -1;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    int idx = 0;
    int sum = 0;
    
    for(int i = 0; i <= (int)B.size(); i++){
        if(B[i] <= A[idx]) continue;
    
        idx++;
        if(idx > (int)A.size())
            break;
        sum++;
    }
    return sum;
}