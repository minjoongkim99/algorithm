#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int n, k;
int cnt[100002];
int a[200002];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int en = 0;
    cnt[a[en]]++;
    int ret = 0;
    for(int st = 0; st < n; st++){
        while(en + 1 != n && cnt[a[en + 1]] < k){
            en++;
            cnt[a[en]]++;
        }
        ret = max(ret, en - st + 1);

        cnt[a[st]]--;
    }

    cout << ret << "\n";
}
