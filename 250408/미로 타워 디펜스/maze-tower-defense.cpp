#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int arr[30][30];
int idx[900];
int d, p;

vector<int> v;

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

int len = 1, cur = 0, change = 0;


int point = 0;

void showArr() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << arr[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << '\n';
}

void showVector() {
	cout << "VECTOR ELEMENT\n";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << '\t';
	}
	cout << "\n";
}

void attack(int dir, int len) {
	
	for (int i = 1; i <= len; ++i) {
		int yy = n / 2 + i * dy[dir];
		int xx = n / 2 + i * dx[dir];

		if (yy < 0 || yy >= n || xx < 0 || xx >= n) continue;

		if (arr[yy][xx] > 0) {
			point += arr[yy][xx];
			arr[yy][xx] = -1;
		}
	}
}

void snailEmpty() {
	int cy = n / 2, cx = n / 2;
	int dir = 2;
	int flag = 0;
	while (true){
		int ny = cy + dy[dir];
		int nx = cx + dx[dir];
		//cout << ny << "," << nx << " " << len << " " << cur << " " << change << "\n";
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
			break;
		}
		if (arr[ny][nx] == 0) break;
		
		if (arr[ny][nx] != -1) 
			v.push_back(arr[ny][nx]);

		cur++;
		if (cur == len) {
			cur = 0;
			dir = (dir + 3) % 4;
			change++;
		}
		if (change == 2) {
			change = 0;
			len++;
		}

		cy = ny;
		cx = nx;
		//flag++;
	}
}

int eraseMonster() {
	fill(&idx[0], &idx[0] + 900, 0);
	int flag = 0;
	vector<int> tmp;

	for (int i = 0; i < v.size() - 3; ++i) {
		if (v[i] == v[i + 1] && v[i + 1] == v[i + 2] && v[i + 2] == v[i + 3]) {
			idx[i] = idx[i + 1] = idx[i + 2] = idx[i + 3] = 1;
			flag = 1;
		}
	}

	for (int i = 0; i < v.size(); ++i) {
		if (idx[i] == 1) point += v[i];
		else tmp.push_back(v[i]);
	}
	
	v = tmp;
	return flag;
}

/*
			* 4. 삭제가 끝난 다음 몬스터 차례대로 나열 했을 때, 같은 숫자끼리
			*	짝을 지어준다. (총 개수, 숫자 크기)로 변환 후 미로에 삽입
			*  OOB이면 무시한다.
*/

void makeNewVector() {
	vector<int> tmp;

	int val = v[0];
	int cnt = 1;

	for (int i = 0; i < v.size() - 1; ++i) {
		if (v[i] == v[i + 1]) {
			cnt++;
		}
		else {
			tmp.push_back(cnt);
			tmp.push_back(val);

			val = v[i + 1];
			cnt = 1;
		}
	}

	tmp.push_back(cnt);
	tmp.push_back(val);

	v = tmp;
}


//(총 개수, 숫자 크기)로 변환 후 미로에 삽입. OOB이면 무시
void vecToArr() {
	fill(&arr[0][0], &arr[0][0] + 30 * 30, 0);

	int cy = n / 2, cx = n / 2;
	int dir = 2;

	for (int i = 0; i < v.size(); ++i) {
		int ny = cy + dy[dir];
		int nx = cx + dx[dir];
		//cout << ny << "and" << nx << "!\n";

		if (ny < 0 || ny >= n || nx < 1 || nx >= n) break;
		arr[ny][nx] = v[i];

		cur++;

		if (cur == len) {
			cur = 0;
			dir = (dir + 3) % 4;
			change++;
		}
		if (change == 2) {
			change = 0;
			len++;
		}

		cy = ny;
		cx = nx;
	}
}


int main() {
	int T = 1;
	//cin >> T;
	
	for (int tc = 1; tc <= T; ++tc) {
		//global_init();
		point = 0;
		v.clear();

		cin >> n >> m;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> arr[i][j];
			}
		}

		for (int i = 1; i <= m; ++i) {
			// local_init()

			cin >> d >> p;
			//cout << "RUN" << i << "\n";

			/*
			1. 플레이어는 상하좌우 방향 중 주어진 공격 칸 수만큼 몬스터 공격 가능
			*/
			attack(d, p);
			//showArr();

			/*
			* 2. 비어 있는 공간을 몬스터는 앞으로 이동하여 빈공간 채우기
			*/
			len = 1, cur = 0, change = 0;
			snailEmpty();
			//showVector();


			/*
			* 3. 이때 몬스터의 종류가 4번이상 반복하여 나오면 해당 몬스터들 삭제
			*	삭제된 이후 몬스터 당겨주고 또 4번이상 몬스터 있으면 또 삭제
			*  이것을 반복
			*/
			while (true) {
				int flag = eraseMonster();
				if (flag == 0) break;
				//showVector();
			}

			//showVector();


			/*
			* 4. 삭제가 끝난 다음 몬스터 차례대로 나열 했을 때, 같은 숫자끼리
			*	짝을 지어준다. (총 개수, 숫자 크기)로 변환.
			*/
			makeNewVector();
			//showVector();

			// 미로에 삽입. OOB 이면 무시한다.
			len = 1, cur = 0, change = 0;
			vecToArr();
			//cout << "FINISHED\n";
			//showArr();

			// final_init()
			v.clear();
		}

		cout << point << '\n';
		//cout << "-------------------------\n";
	}
	return 0;
}

/* n * n 나선형 미로, 1 2 3번 몬스터
* 몬스터를 제거하는 것이 목표
*/

/*
1. 플레이어는 상하좌우 방향 중 주어진 공격 칸 수만큼 몬스터 공격 가능
*/

/* 
* 2. 비어 있는 공간을 몬스터는 앞으로 이동하여 빈공간 채우기
*/

/*
* 3. 이때 몬스터의 종류가 4번이상 반복하여 나오면 해당 몬스터들 삭제
*	삭제된 이후 몬스터 당겨주고 또 4번이상 몬스터 있으면 또 삭제
*  이것을 반복
*/

/*
* 4. 삭제가 끝난 다음 몬스터 차례대로 나열 했을 때, 같은 숫자끼리
*	짝을 지어준다. (총 개수, 숫자 크기)로 변환 후 미로에 삽입
*  OOB이면 무시한다.
*/

/*
* 1~4번을 거쳐 한 라운드 끝나고, 1 3 과정에서 삭제되는 몬스터 번호는 
* 점수에 합쳐진다
*/