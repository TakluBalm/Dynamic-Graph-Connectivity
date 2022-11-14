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
			int u = min(u_,v_), v = max(u_,v_);
			return TreeEdge[level][u].find(v) != TreeEdge[level][u].end();
		}

	public:
		Graph(){}

		void printState(){
			// for(int i = 0; i <= logn; i++){
			// 	forest[i].print();
			// }
			// cout << endl;
			for(int i=logn;i>=0;i--){
				cout<<"level "<<i<<" Tree Edges ";
				for(int u=0;u<vertices;u++){
					for(auto v: TreeEdge[i][u]){
						cout<<"( "<<u+1<<","<<v+1<<" )"<<" ";
					}
				}
				cout<<endl;
				cout<<"level "<<i<<" Non-Tree Edges ";
				for(int u=0;u<vertices;u++){
					for(auto v: NonTreeEdge[i][u]){
						cout<<"( "<<u+1<<","<<v+1<<" )"<<" ";
					}
				}
				cout<<endl;
			}
			cout<<endl;
		}

		Graph(int n){
			vertices = n;
			logn = floor(log2(n));
			forest = vector<SpanningForest>(logn+1);
			TreeEdge = vector<vector<set<int>>>(logn+1, vector<set<int>>(n));
			NonTreeEdge = vector<vector<set<int>>>(logn+1);
			for(int i = 0; i <= logn; i++){
				forest[i] = SpanningForest(n);
				TreeEdge[i] = vector<set<int>> (n);
				NonTreeEdge[i] = vector<set<int>>(n);
			}
		}

		bool isConnected(int u_,int v_){
			bool t = forest[logn].connected(u_,v_);
			if(DEBUG){
				cout << "(" << u_ +1<< ", " << v_ +1<< ")";
				if(t)	cout << " is connected" << endl;
				else	cout << " is not connected" << endl;
			}
			return t;
		}

		void insertEdge(int u_, int v_){
			//	Preliminary Checks
			int u = min(u_,v_), v = max(u_, v_);
			if(v > vertices || u < 0)	return;
			if(edge[{u,v}] != 0)	return;

			//	Insert Edge at level log(n)
			edge[{u,v}] = logn;

		/*
			If edge joins previously unconnected vertices it
			should be addes as a Tree Edge, otherwise it should be
			added as a non-Tree edge.
		*/
			if(!forest[logn].connected(u,v)){
				TreeEdge[logn][u].insert(v);
				TreeEdge[logn][v].insert(u);
				forest[logn].addEdge(u,v);
			}else{
				NonTreeEdge[logn][u].insert(v);
				NonTreeEdge[logn][v].insert(u);
			}

			if(DEBUG){
				printState();
			}

			if(DEBUG){
				printState();
			}
		}

		void removeEdge(int u_, int v_){
			int u = min(u_,v_), v = max(u_,v_);
		//	Preliminary checks
			if(v > vertices || u < 0)	return;
			
		//	Remove the edge from the edge map 
			int level = edge[{u,v}];
			edge.erase({u,v});

			if(isTreeEdge(u, v,level)){

			/*
				Remove the Edge from the graph
				as well as the spanning Forests
			*/
				TreeEdge[level][u].erase(v);
				TreeEdge[level][v].erase(u);

			/*
				Remove the edge from all the forests from that to above level
			*/
				for(int i=level;i<=logn;i++)
					forest[i].deleteEdge(u, v);

			//	Traversing all the levels and find Tv, Tw
				for(int i = level; i <= logn; i++){
				//	Re-label u and v such that v represents smaller tree
					if(forest[i].getSize(u) < forest[i].getSize(v))
						swap(u,v);

				//	Pushing the tree containing v one level down
					vector<int> sm_tree = forest[i].getVertices(v);			
					for(auto v1: sm_tree){
						vector<int> ToDelete;
						for(auto v2: TreeEdge[i][v1]){
							ToDelete.push_back(v2);
							forest[i-1].addEdge(v1,v2);
							TreeEdge[i-1][v1].insert(v2);
							TreeEdge[i-1][v2].insert(v1);
							edge[{min(v1,v2),max(v2,v1)}] = i - 1;
						}
						for(auto v2: ToDelete){
							TreeEdge[i][v2].erase(v1);
							TreeEdge[i][v1].erase(v2);
						}
					}
					
				// Searching for replacement edge in the forests at level i
					bool FoundReplacementEdge = false;
					for(auto v1: sm_tree){
						vector<int> toDelete;
						for(auto v2: NonTreeEdge[i][v1]){
							toDelete.push_back(v2);
							if(forest[i].connected(v1, v2)){
							/*
								Edge is not a replacement edge, thus
								its level is decreased
							*/
								NonTreeEdge[i-1][v1].insert(v2);
								NonTreeEdge[i-1][v2].insert(v1);
								edge[{min(v1,v2),max(v2,v1)}] = i-1;
							}
							else{
							/*
								{v1,v2} is a replacement edge as
								it runs between 2 unconnected components
							*/
								FoundReplacementEdge = true;
								TreeEdge[i][v1].insert(v2);
								TreeEdge[i][v2].insert(v1);
							//	Inserting {v1,v2} into all forests above this level
								for(int j = i; j <= logn; j++){
									forest[j].addEdge(v1,v2);
								}
								break;
							}
						}
						for(auto v2: toDelete){
							NonTreeEdge[i][v1].erase(v2);
							NonTreeEdge[i][v2].erase(v1);
						}
						if(FoundReplacementEdge)	break;
					}
					if(FoundReplacementEdge)	break;
				}
			}
			else{ 
				NonTreeEdge[level][u].erase(v);
				NonTreeEdge[level][v].erase(u);
			}
			if(DEBUG){
				printState();
			}
			
			if(DEBUG){
				printState();
			}
		}
};

int main(){
	freopen ("test.txt", "r", stdin);
	freopen ("graph_output.txt", "w", stdout);

	uint64_t prep_time = 0, updation_time = 0, query_time = 0, io_time = 0;
	uint64_t start, end;
	

	int n, m; 
	io_time -= clock();
	cin >> n >> m;
	io_time += clock();
	
	prep_time -= clock();
	Graph g(n);
	prep_time += clock();

	
	for(int i = 0; i < m; i++){
		string s;
		int a,b;

		io_time -= clock();
		cin >> s >> a >> b;
		io_time += clock();
		
		a--; b--;
		if(s == "add"){
			updation_time -= clock();
			g.insertEdge(a,b);
			updation_time += clock();
		}
		else if(s == "rem"){
			updation_time -= clock();
			g.removeEdge(a,b);
			updation_time += clock();
		}
		else{
			query_time -= clock();
			bool ans = g.isConnected(a,b);
			query_time += clock();

			if(ans){
				io_time -= clock();
				cout<<"YES"<<endl;
				io_time += clock();
			}
			else{	
				io_time -= clock();
				cout<<"NO"<<endl;
				io_time += clock();
			}
		}
	}

	cerr << "Updation Time: " << updation_time << endl;
	cerr << "Query Time   : " << query_time << endl;
	cerr << "Preprocessing: " << prep_time << endl;
	cerr << "IO Time      : " << io_time << endl;
	cerr << "Total time   : " << updation_time + query_time << endl;

	return 0;
}