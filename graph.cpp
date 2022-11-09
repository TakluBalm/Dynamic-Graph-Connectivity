#include <bits/stdc++.h>
#include "spanning_forest.cpp"
using namespace std;

class Graph{
	private:
		map<pair<int,int>, int> edgeMap;
		int vertices;
		int logn;
		vector<Spanning_Forest> F;
	
	public:
		Graph(int n){
			vertices = n;
			logn = ceil(log2(n));
			F = vector<Spanning_Forest>(logn);
		}

		void addEdge(int u, int v){
			if(u < vertices && v < vertices){
				edgeMap[{u,v}] = logn;
				edgeMap[{v,u}] = logn;
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
}