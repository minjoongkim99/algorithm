#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int len;
bool cmp(string a, string b){
    if(a[len] < b[len]) return true;
    else if(a[len] > b[len]) return false;
    else{
        if(a < b) return true;
        else return false;
    }
}

vector<string> solution(vector<string> strings, int n) {
    vector<string> answer;
    len = n;
    sort(strings.begin(), strings.end(), cmp);
    answer = strings;

    return answer;
}