#include <bits/stdc++.h>
#include "SplayForest.cpp"
using namespace std;

class SpanningForest{
	private:
		struct mpNode{
			TreeNode* first;
			TreeNode* last;
		};
		SplayForest t;
		vector<mpNode> vec;

	public:

		SpanningForest(){}

		SpanningForest(int n){
			vec.resize(n);
			for(int i = 0; i < n; i++){
				TreeNode* temp = t.insertNode(i);
				vec[i].first = temp;
				vec[i].last = temp;
			}
		}

		bool connected(int u, int v){
			return t.findBSTRoot(vec[u].first) == t.findBSTRoot(vec[v].first);
		}

		void addEdge(int u, int v){
			/*TODO*/
		}

		void deleteEdge(int u, int v){
			/*TODO*/
		}
};