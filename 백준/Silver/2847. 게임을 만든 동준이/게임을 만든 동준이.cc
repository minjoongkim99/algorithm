#include <iostream>
#include <list>
#include <string>

using namespace std;

int arr[102];
int cnt = 0;
int main() {

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    for(int i = n - 1 ; i >= 1; i--){
        if(arr[i] <= arr[i - 1]){
            int x = arr[i - 1] - arr[i] + 1;
            cnt += x;
            arr[i - 1] -= x;
        }
    }

    cout << cnt << "\n";
    return 0;
}