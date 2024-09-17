#include <string>
#include <vector>
#include <bitset>
#include <iostream>
using namespace std;


int a1[16][16];
int a2[16][16];
vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    
    for(int i = 0; i < arr1.size(); i++){
        bitset<16> b(arr1[i]);
        for(int j = 0; j < n; j++){
            a1[i][n - 1 - j] = b[j];
        }
    }
    for(int i = 0; i < arr2.size(); i++){
        bitset<16> b(arr2[i]);
        for(int j = 0; j < n; j++){
            a2[i][n - 1 - j] = b[j];
        }
    }
    
    for(int i = 0; i < n; i++){
        string str = "";
        for(int j = 0; j < n; j++){
            if(a1[i][j] == 1 || a2[i][j] == 1)
                str += "#";
            else str += " ";
        }
        answer.push_back(str);
    }
    return answer;
}