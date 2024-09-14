#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
int a[4001], b[4001], c[4001], d[4001];
vector<int> two1;
vector<int> two2;

long long cnt = 0;
int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            two1.push_back(a[i] + b[j]);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            two2.push_back(c[i] + d[j]);
        }
    }

    sort(two1.begin(), two1.end());
    sort(two2.begin(), two2.end());

    for(int i = 0; i < two1.size(); i++){
        cnt += upper_bound(two2.begin(), two2.end(), -two1[i]) - lower_bound(two2.begin(), two2.end(), -two1[i]);
    }
    cout << cnt << '\n';
    return 0;
}