#include <iostream>
#include <vector>
using namespace std;

int n, m;
int arr[27][27];
int d, p;
int point = 0;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};
int visited[900];

vector<int> v;

void attack(int d, int p){
    int y = n / 2, x = n / 2;

    for(int len = 1; len <= p; ++len){
        int yy = y + len * dy[d];
        int xx = x + len * dx[d];
        if(yy < 0 || yy >= n || xx < 0 || xx >= n) 
            break;
        if(arr[yy][xx] > 0){
            point += arr[yy][xx];
            arr[yy][xx] = -1;
        }
    }
}

void fillEmpty(){
    v.clear();

    int y = n / 2, x = n / 2;
    int len = 1, cur = 0, k = 0;
    int dir = 2;
    while(true){
        int yy = y + dy[dir];
        int xx = x + dx[dir];
        if(yy < 0 || yy >= n || xx < 0 || xx >= n) break;       // ?
        if(arr[yy][xx] == 0) break;

        if(arr[yy][xx] > 0)
            v.push_back(arr[yy][xx]);
        
        cur++;
        if(len == cur){
            dir = (dir + 3) % 4;
            cur = 0;
            k++;
        }
        if(k == 2){
            len++;
            k = 0;
        }
        y = yy;                 // 중요한 부분이다. 디버깅 잘했음
        x = xx;                 // 여기서 틀렸음. 항상 앞으로 나아가야한다.
    }
}

int check4(){
    int flag = 0;
    fill(&visited[0], &visited[0] + 900, 0);
    
    for(int i = 0; i < v.size() - 3; ++i){
        if(v[i] == v[i + 1] && v[i + 1] == v[i + 2] && v[i + 2] == v[i + 3]){
            flag = 1;
            visited[i] = visited[i + 1] = visited[i + 2] = visited[i + 3] = 1;
        }
    }
    return flag;
}

void getPoint(){
    vector<int> tmp;
    for(int i = 0; i < v.size(); ++i){
        if(visited[i] == 0){
            tmp.push_back(v[i]);
        }
        if(visited[i] == 1){
            point += v[i];
        }
    }
    v.clear();
    v= tmp;
}

void makeNewNumber(){
    vector<int> tmp;
    int cnt = 1;
    for(int i = 0; i < v.size() - 1; ++i){
        if(v[i] == v[i + 1]){
            cnt++;
        }
        else{
            tmp.push_back(cnt);
            tmp.push_back(v[i]);
            cnt = 1;
        }
    }
    tmp.push_back(cnt);
    tmp.push_back(v[v.size() - 1]);
    v.clear();
    v = tmp;
}

void toArr(){
    fill(&arr[0][0], &arr[0][0] + 27 * 27, 0);
    int y = n / 2, x = n / 2;
    int idx = 0;
    int len = 1, cur = 0, k = 0;
    int dir = 2;

     while(true){
        int yy = y + dy[dir];
        int xx = x + dx[dir];

        if(yy < 0 || yy >= n || xx < 0 || xx >= n) break;       // ?
        
        arr[yy][xx] = v[idx++];
        if(idx == v.size()) break;

        cur++;
        if(len == cur){
            dir = (dir + 3) % 4;
            cur = 0;
            k++;
        }
        if(k == 2){
            len++;
            k = 0;
        }
        y = yy;                 // 중요한 부분이다. 디버깅 잘했음
        x = xx;                 // 여기서 틀렸음. 항상 앞으로 나아가야한다.
    }
}

int main() {
    // Please write your code here.
    int T = 1;

    for(int tc = 1; tc <= T; ++tc){
        // init();
        cin >> n >> m;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                cin >> arr[i][j];

        for(int run = 0; run < m; ++run){
            cin >> d >> p;
            v.clear();

            attack(d, p);
    
            fillEmpty();

            int flag = 1;
            while(flag == 1){
                flag = check4();

                getPoint();
            }

            makeNewNumber();
            
            toArr();
        }

        cout << point << '\n';
    }

    return 0;
}