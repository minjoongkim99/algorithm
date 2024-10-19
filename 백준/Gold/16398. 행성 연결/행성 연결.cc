#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

long long parent[1002]; // 이 부분을 n+1로 수정할 수 있습니다.
int n;
long long sum = 0;  // 관리 비용의 합을 저장할 변수

vector<tuple<int,int,int>> v;

// 부모 노드를 찾는 함수 (경로 압축)
long long getParent(int x){
    if(parent[x] == x) return x;
    else return parent[x] = getParent(parent[x]);
}

// 두 노드를 합치는 함수 (유니온)
void unionParent(int a, int b){
    a = getParent(a);
    b = getParent(b);
    if(a > b)
        parent[a] = b;
    else parent[b] = a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);
    
    cin >> n;
    
    // parent 배열 초기화
    for(int i = 1; i <= n; i++)
        parent[i] = i;

    // 입력 받기
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int cost;
            cin >> cost;
            if(i != j) {
                v.push_back({cost, i, j});  // 비용과 노드 정보 추가
            }
        }
    }
    
    // 간선들을 비용 기준으로 정렬
    sort(v.begin(), v.end());
    
    // 크루스칼 알고리즘 수행
    int edges = 0;  // 연결된 간선 수를 저장하는 변수
    for(int i = 0; i < v.size(); i++){
        int cost, a, b;
        tie(cost, a, b) = v[i];

        // 두 노드가 이미 연결되어 있으면 넘어감
        if(getParent(a) != getParent(b)){
            unionParent(a, b);  // 두 노드를 연결
            sum += cost;        // 총 비용에 추가
            edges++;            // 간선 수 증가
            
            if(edges == n - 1)  // 최소 스패닝 트리는 n-1개의 간선으로 연결됨
                break;
        }
    }

    cout << sum << '\n';  // 최소 플로우 관리 비용 출력
    return 0;
}
