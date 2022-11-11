#include <bits/stdc++.h>
#include "SpanningForest.cpp"
using namespace std;

class Graph{
	private:
		class Node{
			Node* next;
			pair<int,int> e;
			Node(pair<int,int> e_){
				e = e_;
				next = NULL;
			}
			Node(pair<int,int> e_, Node* n){
				e = e_;
				n = next;
			}
		};

		map<pair<int,int>, int> edgeMap;
		vector<Node*> treeEdge, nonTreeEdge;
		int vertices;
		int logn;
		vector<SpanningForest> F;
	
	public:
		Graph(int n){
			vertices = n;
			logn = ceil(log2(n));
			F = vector<SpanningForest>(logn);
		}

		void addEdge(int u, int v){
			if(u < vertices && v < vertices){
				edgeMap[{v,u}] = logn;
				edgeMap[{u,v}] = logn;
			}
		}

		void addEdge(pair<int,int> p)	{addEdge(p.first, p.second);}

		void deleteEdge(int u, int v){
			if(isPresent(u, v)){
				edgeMap.erase({u,v});
				edgeMap.erase({v,u});
			}
		}

		void deleteEdge(pair<int,int> p)	{deleteEdge(p.first, p.second);}

		bool isPresent(int u, int v)	{return edgeMap.find({u,v}) != edgeMap.end();}

		bool isPresent(pair<int,int> p)	{return isPresent(p.first, p.second);}
};

int main(){
	Graph g(10);
	return 1;
}