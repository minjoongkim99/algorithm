#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int r, c, q;
int arr[1002][1002];
int sum[1002][1002];

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

   cin >> r >> c >> q;
   for(int i = 1;  i <= r; i++){
       for(int j = 1; j <= c; j++){
           cin >> arr[i][j];
           sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
       }
   }
   vector<int> ans;
   for(int i = 1; i <= q; i++){
       int x1, y1, x2, y2;
       cin >> x1 >> y1 >> x2 >> y2;
       int cnt = (x2 - x1 + 1) * (y2 - y1 + 1);

       int val = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
        ans.push_back(val / cnt);
   }

   for(auto e : ans){
       cout << e << '\n';
   }

   return 0;
}