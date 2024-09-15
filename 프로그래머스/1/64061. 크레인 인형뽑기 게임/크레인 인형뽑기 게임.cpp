#include <string>
#include <vector>
#include <stack>
using namespace std;

stack<int> s;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    
    int len = board.size();
    
    for(int k = 0; k < moves.size(); k++){
        int dir = moves[k] - 1;
        
        for(int i = 0; i < len; i++){
            if(board[i][dir] > 0){
                int val = board[i][dir];
                board[i][dir] = 0;
                if(!s.empty() && s.top() == val){
                    s.pop();
                    answer += 2;
                }
                else{
                    s.push(val);
                }
                break;
            }
        }
    }
    
    return answer;
}