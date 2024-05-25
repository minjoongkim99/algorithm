#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int n, m;
vector<int> v1, v2;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;


    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        v1.push_back(x);
    }
    for(int i = 0; i < m; i++){
        int x;
        cin >> x;
        v2.push_back(x);
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    vector<int> ans;
    for(int i = 0; i < n; i++){
        int t = binary_search(v2.begin(), v2.end(), v1[i]);
        if(t == 0)
            ans.push_back(v1[i]);
    }

    cout << ans.size() << "\n";

    for (auto e: ans)
        cout << e << " ";


    return 0;
}