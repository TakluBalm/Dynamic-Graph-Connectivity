#include <bits/stdc++.h>
#include "SpanningForest.cpp"
using namespace std;

class Graph{
	private:
		int vertices;
		int logn;
		vector<SpanningForest> forest;
		map<pair<int,int>, int>	edge;

		bool isTreeEdge(int u, int v){
			//	TODO
		}

	public:
		Graph(){}

		Graph(int n){
			vertices = n;
			logn = floor(log2(n));
			forest = vector<SpanningForest>(logn+1, SpanningForest(n));
		}

		void insertEdge(int u_, int v_){
			int u = min(u_,v_), v = max(u_, v_);
			if(v > vertices || u < 0)	return;
			if(edge[{u,v}] != 0)	return;
			
			edge[{u,v}] = logn;
			if(!forest[logn].connected(u,v)){
				forest[logn].addEdge(u,v);
			}
			//	TODO: Maintain tree and non-tree edges seperately
		}

		void removeEdge(int u_, int v_){
			int u = min(u_,v_), v = max(u_,v_);
			if(v > vertices || u < 0)	return;

			int level = edge[{u,v}];
			edge.erase({u,v}); edge.erase({v,u});
			if(isTreeEdge(u, v)){
				for(int i = level; i <= logn; i++){
					forest[i].deleteEdge(u, v);
				}
			}
		}
};

int main(){
	Graph g(10);
	return 1;
}