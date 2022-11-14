#include <bits/stdc++.h>
using namespace std;

bool isConnected(int u, int v, vector<set<int>>& adj){
	vector<bool> vis(adj.size(), false);
	stack<int> s; s.push(u);
	while(!s.empty()){
		int t = s.top(); s.pop();
		if(vis[t])	continue;
		if(t == v)	return true;
		vis[t] = true;
		for(auto n: adj[t]){
			if(!vis[n]){
				s.push(n);
			}
		}
	}
	return false;
}

int main(){
	freopen("test.txt", "r", stdin);
	freopen("brute_output.txt", "w", stdout);
	uint64_t updation_time = 0, io_time = 0, prep_time = 0, query_time = 0;
	
	int V, ops;
	
	io_time -= clock();
	cin >> V >> ops;
	io_time += clock();
	
	prep_time -= clock();
	vector<set<int>> adj(V);
	prep_time += clock();

	for(int i = 0; i < ops; i++){
		string s;
		int u, v;
		io_time -= clock();
		cin >> s >> u >> v;
		io_time += clock();
		
		u--; v--;
		
		if(s == "add"){
			updation_time -= clock();
			adj[u].insert(v);
			adj[v].insert(u);
			updation_time += clock();
		}else if(s == "rem"){
			updation_time -= clock();
			adj[u].erase(v);
			adj[v].erase(u);
			updation_time += clock();
		}else{
			query_time -= clock();
			bool ans = isConnected(u, v, adj);
			query_time += clock();
			if(ans == true){
				io_time -= clock();
				cout << "YES\n";
				io_time += clock();
			}else{
				io_time -= clock();
				cout << "NO\n";
				io_time += clock();
			}
		}
	}

	cerr << "Updation Time: " << updation_time << endl;
	cerr << "Query Time   : " << query_time << endl;
	cerr << "Preprocessing: " << prep_time << endl;
	cerr << "IO Time      : " << io_time << endl;
	cerr << "Total time   : " << updation_time + query_time << endl;
}