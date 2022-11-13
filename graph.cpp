#include <bits/stdc++.h>
#include "SpanningForest.cpp"
using namespace std;

#define DEBUG 0

class Graph{
	private:
		int vertices;
		int logn;
		vector<SpanningForest> forest;
		map<pair<int,int>, int>	edge;
		vector<vector<set<int>>> TreeEdge;
		vector<vector<set<int>>> NonTreeEdge;

		bool isTreeEdge(int u_, int v_, int level){
			//	TODO
			int u = min(u_,v_);
			int v = max(u_,v_);
			return TreeEdge[level][u].find(v) != TreeEdge[level][u].end();
		}

	public:
		Graph(){}

		void printState(){
			for(int i = 0; i <= logn; i++){
				forest[i].print();
			}
			cout << endl;
		}

		Graph(int n){
			vertices = n;
			logn = floor(log2(n));
			forest = vector<SpanningForest>(logn+1);
			for(int i = 0; i <= logn; i++){
				forest[i] = SpanningForest(n);
			}
			TreeEdge = vector<vector<set<int>>>(logn+1, vector<set<int>>(n));
			NonTreeEdge = vector<vector<set<int>>>(logn+1, vector<set<int>>(n));
		}

		bool isConnected(int u_,int v_){
			bool t = forest[logn].connected(u_,v_);
			if(DEBUG){
				cout << "(" << u_ << ", " << v_ << ")";
				if(t)	cout << " is connected" << endl;
				else	cout << " is not connected" << endl;
			}
			return t;
		}

		void insertEdge(int u_, int v_){
			int u = min(u_,v_), v = max(u_, v_);
			if(v > vertices || u < 0)	return;
			if(edge[{u,v}] != 0)	return;

			edge[{u,v}] = logn;
			if(!forest[logn].connected(u,v)){
				TreeEdge[logn][u].insert(v);
				forest[logn].addEdge(u,v);
			}else{
				NonTreeEdge[logn][u].insert(v);
			}

			if(DEBUG){
				printState();
			}
		}

		void removeEdge(int u_, int v_){
			//	Preliminary checks
			int u = min(u_,v_), v = max(u_,v_);
			if(v > vertices || u < 0)	return;
			
			//	Remove the edge from the edge map
			int level = edge[{u,v}];
			edge.erase({u,v});

			if(isTreeEdge(u, v,level)){
				TreeEdge[level][u].erase(v);
				for(int i = level; i <= logn; i++){
					forest[i].deleteEdge(u, v);
				}
				int tv;
				if(forest[level].getSize(u) < forest[level].getSize(v))
					tv = u;
				else	
					tv = v;
				vector<int> sm_tree = forest[level].getVertices(tv);
				// Pushing the small_tree tv one level
				set<int> ::iterator itr;
				for(auto u: sm_tree){
					vector<int> ToDelete;
					for(itr = TreeEdge[level][u].begin();itr!=TreeEdge[level][u].end();itr++){
						int v = *itr;
						ToDelete.push_back(v);
						forest[level-1].addEdge(u,v);
						TreeEdge[level-1][u].insert(v);
						edge[{u,v}] = level-1;
					}
					for(auto i: ToDelete){
						TreeEdge[level][u].erase(i);
					}
				}
				bool FoundReplacementEdge = false;
				for(int i = level; i <= logn; i++){
					for(auto u: sm_tree){
						vector<int> toDelete;
						for(auto v: NonTreeEdge[i][u]){
							toDelete.push_back(v);
							if(forest[i].connected(u,v)){ // edge is pushed one level down
								NonTreeEdge[i-1][u].insert(v);
								edge[{u,v}] = i-1;
							}
							else{ // replacement edge is found
								FoundReplacementEdge = true;
								TreeEdge[i][u].insert(v);
								for(int j=i;j<=logn;j++){
									forest[j].addEdge(u,v);
								}
								break;
							}
						}
						for(auto v: toDelete){
							TreeEdge[i][u].erase(v);
						}
						if(FoundReplacementEdge)
							break;
					}
					if(FoundReplacementEdge)
						break;
				}
			}
			else{     
				NonTreeEdge[level][u].erase(v);
			}
			
			if(DEBUG){
				printState();
			}
		}
};

int main(){
	#ifndef ONLINE_JUDGE
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
	#endif
	int n;cin>>n;
	int m;cin>>m;
	Graph g(n);
	for(int i=0;i<m;i++){
		string s;cin>>s;
		int a,b;cin>>a>>b;
		a--;b--;
		if(s=="add"){
			g.insertEdge(a,b);
		}
		else if(s=="rem"){
			g.removeEdge(a,b);
		}
		else{
			if(g.isConnected(a,b))
				cout<<"yes"<<endl;
			else	
				cout<<"no"<<endl;

		}
	}

	return 1;
}