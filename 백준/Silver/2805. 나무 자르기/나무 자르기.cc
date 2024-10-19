#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> v;

int st, en;

bool parametric_search(int val){
    long long sum = 0;
    for(int e : v){
        if(e - val > 0)
            sum += (e - val);
    }

    return sum >= m;
}

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    cin >> n >> m;
    v.resize(n, 0);
    for(int i = 0; i < n; i++)
        cin >> v[i];

    en = *max_element(v.begin(), v.end());

    while(st < en){
        int mid = (st + en + 1) / 2;

        if(parametric_search(mid)){
            st = mid;
        }
        else en = mid - 1;
    }

    cout << st << '\n';
    return 0;
}