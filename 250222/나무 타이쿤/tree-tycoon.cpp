#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m; // 격자 크기, 총 연수
int d, p; // 이동방향, 칸 수. 

int ddy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int ddx[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int arr[17][17];
int food[17][17];
int tmp[17][17];
vector<pair<int,int>> pos;

int sum = 0;

void showArr(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}

void showFood(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << food[i][j] << ' ';
        }
        cout << '\n';
    }
}

void moveFood(){
    fill(&tmp[0][0], &tmp[0][0] + 17 * 17, 0);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(food[i][j] == 0) continue;
            else{

                int ny = i + p * ddy[d - 1];
                int nx = j + p * ddx[d - 1];

                if(ny >= n)
                    ny = ny % n;
                else if(ny < 0){
                    ny = n + ny;
                }

                if(nx >= n)
                    nx = nx % n;
                else if(nx < 0){
                    nx = n + nx;
                }

                tmp[ny][nx] = 1;
            }
        }
    }

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            food[i][j] = tmp[i][j];

}

void increaseArr(){

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(food[i][j] == 1)
                arr[i][j]++;
            else continue;
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(food[i][j] == 1){

                for(int dir = 1; dir < 8; dir = dir + 2){
                    int yy = i + ddy[dir];
                    int xx = j + ddx[dir];
                    if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
                    if(arr[yy][xx] >= 1)
                        arr[i][j]++;
                }
            }
            else continue;
        }
    }
}

void cutting(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(food[i][j] == 1) continue;
            else{
                if(arr[i][j] >= 2){
                    arr[i][j] -= 2;
                    pos.push_back({i, j});
                }
            } 
        }
    }
}

void makeFood(){
    fill(&food[0][0], &food[0][0] + 17 * 17, 0);
    for(auto e : pos){
        food[e.first][e.second] = 1;
    }

    pos.clear();
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    cin >> n >> m;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> arr[i][j];
        }
    }

    
    food[n - 2][0] = food[n - 2][1] = food[n - 1][0] = food[n - 1][1] = 1;

    for(int testcase = 0; testcase < m; ++testcase){
        cin >> d >> p;
        
        // 특수영양제 영역 이동
        moveFood();

        //cout << "특수 영양제 이동 후\n";
        //showFood();

        increaseArr();
        //cout << "영양제 소멸 하며 성장\n";
        //showArr();

        cutting();
        //cout << "다음 영양제의 좌표들\n";
        //for(auto e : pos){
        //    cout << e.first << "," << e.second << "  ";
        //}

        makeFood();

        //cout << "\n=================\n";
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            sum += arr[i][j];
        }
    }
    cout << sum << '\n';

    return 0;
}
