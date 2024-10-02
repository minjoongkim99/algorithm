#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int solution(vector<int> nums){   
    int answer = 0;
    unordered_set <int> s;
    for(auto e : nums)
        s.insert(e);
    
    if(s.size() < nums.size() / 2)
        answer = s.size();
    else
        answer = nums.size() / 2;
    return answer;
}