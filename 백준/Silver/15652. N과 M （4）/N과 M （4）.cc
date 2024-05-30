#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int visited[10];
vector<int> v;

void dfs(int cnt, int idx)
{
    if(cnt == m){
        for(auto e : v){
            cout << e << " ";
        }
        cout << "\n";
        return;
    }

    for(int i = idx; i <= n; i++){
        //dfs(cnt, idx + 1);

        // visited?
        //visited[i] = 1;
        v.push_back(i);
        dfs(cnt + 1, i); // about idx?
        v.pop_back();
        //visited[i] = 0;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);       cout.tie(nullptr);

    cin >> n >> m;

    dfs(0,1);
}
