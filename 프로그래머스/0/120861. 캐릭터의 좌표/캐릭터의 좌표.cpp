#include <string>
#include <vector>
#include <iostream>
using namespace std;
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
string dir[4] = {"left", "right", "down", "up"};

vector<int> solution(vector<string> keyinput, vector<int> board) {
    vector<int> answer;
   
    int n = board[0];
    int m = board[1];
    
    int y = n / 2;
    int x = m / 2;
    
    for(const string& s: keyinput){
        if(s == "up"){
            int yy = y + dy[3];
            int xx = x + dx[3];
            if(yy < 0 || yy >= n || xx < 0 || xx >= m) continue;
            y = yy, x = xx;
        }
        else if(s == "down"){
            int yy = y + dy[2];
            int xx = x + dx[2];
            if(yy < 0 || yy >= n || xx < 0 || xx >= m) continue;
            y = yy, x = xx;
        }
        else if(s == "left"){
            int yy = y + dy[0];
            int xx = x + dx[0];
            if(yy < 0 || yy >= n || xx < 0 || xx >= m) continue;
            y = yy, x = xx;
        }
        else if(s == "right"){
            int yy = y + dy[1];
            int xx = x + dx[1];
            if(yy < 0 || yy >= n || xx < 0 || xx >= m) continue;
            y = yy, x = xx;
        }
    }

    answer.push_back(y - n / 2);
    answer.push_back(x - m / 2);
    return answer;
}