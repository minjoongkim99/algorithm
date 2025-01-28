#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int arr1[5] = {1, 2, 3, 4, 5};
int arr2[8] = {2, 1, 2, 3, 2, 4, 2, 5};
int arr3[10] = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    int a = 0, b = 0, c = 0;
    
    for(int i = 0; i < answers.size(); i++){
        if(answers[i] == arr1[i % 5]){
            a++;
        }
        if(answers[i] == arr2[i % 8]){
            b++;
        }
        if(answers[i] == arr3[i % 10]){
            c++;
        }
    }
    
    int mx = max(a, b);
    mx = max(mx, c);
    
    if(mx == a){
        answer.push_back(1);
    }
    if(mx == b){
        answer.push_back(2);
    }
    if(mx == c){
        answer.push_back(3);
    }

    return answer;
}