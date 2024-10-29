#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> v;
long long st, en;

bool solve(long long mid){
    long long sum = 0;
    //if(mid == 0) return false;
    for(int i = 0; i < v.size(); i++){
        sum += v[i] / mid;
    }

    return sum >= n;
}

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    cin >> k >> n;
    for(int i = 0; i < k; i++){
        int x;
        cin >> x;
        v.push_back(x);
    }

    st = 1;
    en = *max_element(v.begin(), v.end());

    while(st < en){
        long long mid = (st + en + 1) / 2;
        if(solve(mid))
            st = mid;
        else en = mid - 1;

        //cout << st << "and" << en << "\n";
    }

    cout << st << '\n';
    return 0;
}