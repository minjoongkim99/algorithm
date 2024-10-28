#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 9017 크로스컨트리 틀림 ㅠ

int N, K;
int info[1002][3];
int level[1002];

class nation {
public:
	int team;
	int gold;
	int silver;
	int bronze;
	nation(int t, int g, int s, int b) {
		this->team = t;
		this->gold = g;
		this->silver = s;
		this->bronze = b;
	}

	bool operator <(const nation& n) {
		if (this->gold < n.gold)
			return true;

		else if (this->gold == n.gold) {
			if (this->silver < n.silver)
				return true;
			else if (this->silver == n.silver) {
				if (this->bronze < n.bronze) {
					return true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
};
int main() {

	cin >> N >> K;
	vector<nation> v;
	for (int i = 1; i <= N; i++) {
		int team, gold, silver, bronze;
		cin >> team >> gold >> silver >> bronze;
		info[team][0] = gold;
		info[team][1] = silver;
		info[team][2] = bronze;
		v.push_back(nation(team, gold, silver, bronze));
	}

	sort(v.begin(), v.end());

	int cnt = 1;
	int index = v[v.size() - 1].team;
	level[index] = cnt;
	for (int i = v.size() - 1; i > 0; i--) {
		if (v[i].gold == v[i - 1].gold && v[i].silver == v[i - 1].silver && v[i].bronze == v[i - 1].bronze) {
			int k = v[i - 1].team;
			level[k] = cnt;
		}
		else {
			cnt++;
			int k = v[i - 1].team;
			level[k] = cnt;
		}
	}

	cout << level[K];

	return 0;
}