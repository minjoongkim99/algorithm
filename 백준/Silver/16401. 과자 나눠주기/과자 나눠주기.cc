#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int l[1000002];

bool parametric_search(int x) {
    if (x == 0)
        return true;
    long long cnt = 0;
    for (int i = 0; i < n; ++i) {
        if(l[i] / x == 0) continue;
        else cnt += l[i] / x;
    }
    return cnt >= m;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> n;

    int st = 0;
    int en = 0;
    for (int i = 0; i < n; i++) {
        cin >> l[i];
        if(l[i] > en)
            en = l[i];
    }

    while (st < en) {
        int mid = (st + en + 1) / 2;
        if (parametric_search(mid))
            st = mid;
        else
            en = mid - 1;
    }
    cout << st << "\n";
}