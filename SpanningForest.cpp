#include <bits/stdc++.h>
#include "SplayForest.cpp"
using namespace std;

#define RIGHT true
#define LEFT false

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
		
		vector<int> getVertices(TreeNode* r){
			vector<int> ver;
		 	r = t.findBSTRoot(r);
			queue<TreeNode*> q;
			q.push(r);
			while(!q.empty()){
				TreeNode* cur = q.front();
				q.pop();
				if(vec[cur->data].first == cur){
					ver.push_back(cur->data);
				}
				if(cur->left!=NULL)
					q.push(cur->left);
				if(cur->right!=NULL)
					q.push(cur->right);
			}
			return ver;
		}

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

		bool isPresent(int u, int v){
			TreeNode* temp1 = t.getNext(vec[u].last), *temp2 = t.getNext(vec[v].last);
			if((temp1 != NULL && temp1->data == v) || (temp2 != NULL && temp2->data == u))	return true;
			return false;
		}

		void addEdge(int u, int v){
			if(isPresent(u, v))	return;
			TreeNode* temp = t.split(vec[u].last, RIGHT);
			t.merge(vec[u].last, vec[v].first);
			vec[u].last = t.insertNode(u);
			t.merge(vec[u].first, vec[u].last);
			t.merge(vec[u].first, temp);
		}

		void deleteEdge(int u, int v){
			if(!isPresent(u,v))	return;

			TreeNode* temp1 = t.split(vec[v].first, LEFT);
			TreeNode* redundant = t.findLeftMost(t.split(vec[v].last, RIGHT));
			TreeNode* temp2 = t.split(redundant, RIGHT);

			if(redundant = vec[u].last){
				vec[u].last = t.findRightMost(temp1);
			}

			t.merge(temp1, temp2);
		}
};