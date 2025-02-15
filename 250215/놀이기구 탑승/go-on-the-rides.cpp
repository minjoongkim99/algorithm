#include <iostream>
#include <vector>

using namespace std;

int n;
// 우선순위 vector 돌리기는 sort 함수를 사용하여 정렬, sort 함수가 있음을 항상 유의하기
vector<int> friends[402];       // vector<> 자료구조로 주로 담았음. vector<vector<int>> 쓸 때도 있고. 
int arr[402][402];              // 2차원 배열은 무조건임. SIZE가 어디까지인지. 여유분.
int point;                      // Output에 대한 변수. (구해야하는 것은 무엇인가??)

int dy[4] = {-1, 0, 1, 0};      // dy -> i
int dx[4] = {0, 1, 0, -1};      // dx -> j      순서외우기
//  ddy, ddx는 8방향    dy dx는 4방향으로 외워놓기

void insert_person(int idx){

    int fn = -1, en = -1;        // 비교해야할 값(우선순위)들에 대한 변수. 매번 갱신해야함.
    int ny = -1, nx = -1;       // 해당 함수의 목표는 사람이 들어갈 자리를 잡는 것이다. 가져야할 좌표를 알고 있어야힌다.

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(arr[i][j] != 0) continue;
            int fcnt = 0, ecnt = 0;

            for(int dir = 0; dir < 4; ++dir){
                int yy = i + dy[dir];
                int xx = j + dx[dir];

                if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue; // yy, xx OOB는 항상! 0-인덱스. 1-인덱스
                
                if(arr[yy][xx] == 0) ecnt++;
                for(int k = 0; k < 4; ++k){
                    if(arr[yy][xx] == friends[idx][k])
                        fcnt++;
                    
                }
            }

            if(fcnt > fn){
                fn = fcnt; 
                en = ecnt;
                ny = i;
                nx = j;
            }
            else if(fcnt == fn){
                if(ecnt > en){
                    en = ecnt;
                    ny = i;
                    nx = j;
                }
            }
        }
    }
    // if(>) elseif(==) elseif(==) elseif(==)~~ 우선순위 비교 같기
    arr[ny][nx] = idx;
}

void getPoint(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            
            int cnt = 0;

            for(int dir = 0; dir < 4; ++dir){
                int yy = i + dy[dir];
                int xx = j + dx[dir];

                if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
                for(int k = 0; k < 4; ++k){
                    if(arr[yy][xx] == friends[arr[i][j]][k]){ // value가 새로운 Index로 들어가는 경우. 
                        cnt++;              //[arr[i][j]][k] 
                    }
                }
            }

            if(cnt == 0) point += 0;
            else if(cnt == 1) point += 1;
            else if(cnt == 2) point += 10;
            else if(cnt == 3) point += 100;
            else if(cnt == 4) point += 1000;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 복잡한 우선순위 비교 후 삽입에 대한 문제이다. 구현은 어떻게 하는가?
    // 1. 4방향 인접한 칸 좋아하는 친구 많음    
    // 2. 1이 여러 곳이라면 비어있는 칸 많음
    // 3. 행작 -> 열작                  이러한 기준이 매번 있다. 행작 열작은 for문 위치 조절로 조건문 안달고 편리하게 할 수 있음.

    cin >> n;

    for(int i = 0; i < n * n; ++i){
        int idx, a, b, c, d;
        cin >> idx >> a >> b >> c >> d;
        friends[idx].push_back(a);  
        friends[idx].push_back(b);
        friends[idx].push_back(c);  
        friends[idx].push_back(d);

        insert_person(idx);
    }

    getPoint();

    cout << point << '\n';

    // 2차원 배열에 담는 것은 각 사람이 위치할 값이다. arr[i][j] = 사람의 번호.
    // vector<?>는 친구다. 2차원 배열과 vector의 연관관계를 이용하여 비교 같은 연산을 진행해야한단
    // 비교 시, index로 들어가야할지 value로 들어가야할지 항상 유의해야한다.
    return 0;
}