#include <string>
#include <vector>

using namespace std;
int month[12] = {0,31,29,31,30,31,30,31,31,30,31,30};
string date[7] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

string getDay(int a,int b){
  for(int i = 0; i < a; i++)
    b += month[i];
    
    string answer= date[(b + 4) % 7];  
    return answer;
}


string solution(int a, int b) {
    string answer = getDay(a, b);
    return answer;
}