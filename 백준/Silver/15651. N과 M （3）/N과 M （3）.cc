#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int arr[10];
int visited[10];
vector<int> v;

void dfs(int cnt)
{
    if(cnt == m){
        for(auto e : v){
            cout << e << " ";
        }
        cout << "\n";
        return;
    }

    for(int i = 1; i <= n; i++){

        //visited[i] = 1;
        v.push_back(i);
        dfs(cnt+1);
        v.pop_back();
        //visited[i] = 0;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);       cout.tie(nullptr);
    cin >> n >> m;

    dfs(0);
}
