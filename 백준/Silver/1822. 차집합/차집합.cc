#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> v1, v2;
vector<int> ans;
int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);
    cin >> n >> m;
    v1.resize(n, 0);
    v2.resize(m, 0);
    for(int i = 0; i < n; i++)
        cin >> v1[i];
    for(int i = 0; i < m; i++)
        cin >> v2[i];
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());


    for(int i = 0; i < n; i++){
        if(binary_search(v2.begin(), v2.end(), v1[i]))
            continue;
        else
            ans.push_back(v1[i]);
    }

    if(ans.empty())
        cout << 0 << '\n';
    else{
        cout << ans.size() << '\n';
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << ' ';
        }
    }

    return 0;
}