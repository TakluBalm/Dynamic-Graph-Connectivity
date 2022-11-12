#include <bits/stdc++.h>
#include "SpanningForest.cpp"
using namespace std;

class Graph{
	private:
		int vertices;
		int logn;
		vector<SpanningForest> forest;
		map<pair<int,int>, int>	edge;
		vector<map<int,set<int>>> TreeEdge;
		vector<map<int,set<int>>> NonTreeEdge;
		bool isTreeEdge(int u, int v,int level){
			//	TODO
			int u_ = min(u,v);
			int v_ = max(u,v);
			return TreeEdge[level][u_].find(v_)!=TreeEdge[level][u_].end();
		}

	public:
		Graph(){}

		Graph(int n){
			vertices = n;
			logn = floor(log2(n));
			forest = vector<SpanningForest>(logn+1, SpanningForest(n));
			TreeEdge = vector<map<int,set<int>>>(logn+1);
			NonTreeEdge = vector<map<int,set<int>>>(logn+1);
		}
		bool isConnected(int u_,int v_){
			return forest[logn].connected(u_,v_);
		}
		void insertEdge(int u_, int v_){
			int u = min(u_,v_), v = max(u_, v_);
			if(v > vertices || u < 0)	return;
			if(edge[{u,v}] != 0)	return;	
			edge[{u,v}] = logn;
			if(!forest[logn].connected(u,v)){
				TreeEdge[logn][u].insert(v);
				forest[logn].addEdge(u,v);
			}
			else{
				NonTreeEdge[logn][u].insert(v);
			}
		}

		void removeEdge(int u_, int v_){
			int u = min(u_,v_), v = max(u_,v_);
			if(v > vertices || u < 0)	return;
			int level = edge[{u,v}];
			edge.erase({u,v}); edge.erase({v,u});
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
				for(auto u: sm_tree){
					for(auto v: TreeEdge[level][u]){
						TreeEdge[level][u].erase(v);
						forest[level-1].addEdge(u,v);
						TreeEdge[level-1][u].insert(v);
						edge[{u,v}] = level-1;
					}
				}
				bool FoundReplacementEdge = false;
				for(int i=level;i<=logn;i++){
					for(auto u: sm_tree){
						for(auto v: NonTreeEdge[i][u]){
							NonTreeEdge[i][u].erase(v);
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
		}
};

int main(){
	Graph g(7);
	g.insertEdge(1,6);
	// g.insertEdge(2,6);
	// g.insertEdge(1,2);
	// if(g.isConnected(1,2)){
	// 	cout<<"lesgo"<<endl;
	// }
	return 1;
}