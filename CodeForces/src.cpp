#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int maxn = 3e5 + 1e2;
int n, e;
vector<int> adj[maxn];

int par[maxn];
int dfs_num[maxn];
int dfs_low[maxn];
int state[maxn];

int bridge_above[maxn];
int max_bridge_trail[maxn];

int curr = 0;
int res = 0;

void bridge_dfs(int pos){
	state[pos] = 1;

	dfs_num[pos] = curr;
	dfs_low[pos] = curr;
	curr++;
	
	for(int nnext : adj[pos]){
		if(nnext != par[pos]){
			if(state[nnext] == 0){
				par[nnext] = pos;

				bridge_dfs(nnext);

				if(dfs_low[nnext] > dfs_num[pos]){
					bridge_above[nnext]++;
				}
			}

			dfs_low[pos] = min(dfs_low[pos], dfs_low[nnext]);
		}
	}

	state[pos] = 2;
}

void dfs3(int pos){
	state[pos] = 1;

	int a = -1;
	int b = -1;

	for(int i = 0; i < adj[pos].size(); i++){
		int nnext = adj[pos][i];

		if(adj[pos][i] != par[pos] and state[nnext] == 0){
			dfs3(nnext);
			if(a < max_bridge_trail[nnext]){
				b = a;
				a = max_bridge_trail[nnext];
			} else if(b < max_bridge_trail[nnext]){
				b = max_bridge_trail[nnext];
			}
		}
	}

	res = std::max(res, std::max(a + b, std::max(a, b)));

}

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n >> e;

	for(int i = 0; i < e; i++){
		int f, s;
		cin >> f >> s;
		f--, s--;

		adj[f].push_back(s);
		adj[s].push_back(f);
	}

	par[0] = -1;
	bridge_dfs(0);

	std::fill(state, state + n, 0);
	dfs3(0);

	std::cout << res << '\n';
}
