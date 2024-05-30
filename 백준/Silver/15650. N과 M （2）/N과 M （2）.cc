#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int visited[10];
vector<int> v;
int ret = 0;
void backtracking(int idx, int cnt){

    if(idx > n + 1) return;
    if(cnt == m){
        for(auto e : v){
            cout << e << " ";
        }
        cout<< "\n";
        return;

    }



    v.push_back(idx);
    backtracking(idx + 1, cnt + 1);
    v.pop_back();

    backtracking(idx + 1, cnt);

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    backtracking(1,0);
}
