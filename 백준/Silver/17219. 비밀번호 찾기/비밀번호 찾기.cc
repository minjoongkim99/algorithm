#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);
    unordered_map<string, string > db;
    
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        string site, pwd;
        cin >> site >> pwd;
        db[site] = pwd;
    }

    for(int i = 0; i < m; i++){
        string site;
        cin >> site;
        if(db.find(site) != db.end())
            cout << db[site] << "\n";
    }
    return 0;
}