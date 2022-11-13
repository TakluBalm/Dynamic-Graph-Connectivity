#include <bits/stdc++.h>
#include "SpanningForest.cpp"
using namespace std;

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
			}else{
				NonTreeEdge[logn][u].insert(v);
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
		}
};

int main(){
	Graph g(7);
	g.printState();
	g.insertEdge(4,5);
	g.printState();
	g.insertEdge(2,1);
	g.printState();
	g.insertEdge(2,6);
	g.printState();
	g.insertEdge(1,5);
	g.printState();
	g.removeEdge(1,5);
	g.printState();
	if(g.isConnected(1,4)){
		cout<<"lesgo"<<endl;
	}
	else{
		cout<<"STILL LESGPO"<<endl;
	}
	return 1;
}