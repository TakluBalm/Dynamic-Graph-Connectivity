#include <bits/stdc++.h>
#include "SplayForest.cpp"
using namespace std;

class SpanningForest{
	private:
		struct mpNode{
			TreeNode* arbiEdge;
			mpNode(){
				arbiEdge = NULL;
			}
		};
	
		SplayForest t;
		vector<mpNode> vec;
	public:
		struct mpEdge{
			TreeNode* oc1;
			TreeNode* oc2;
			mpEdge(TreeNode* one, TreeNode* two){
				oc1 = one; oc2 = two;
			}
			mpEdge(){
				oc1 = oc2 = NULL;
			}
		};

		/*
		Edges are always storeed in the form
		(u,v) where u <= v
		*/
		map<pair<int,int>,mpEdge> edgeMp;
		SpanningForest(){}

		void print(){
			for(int i = 0; i < vec.size(); i++){
				t.inorder(t.findBSTRoot(vec[i].arbiEdge));
				cout << ", ";
			}
			cout << endl;
		}
		

		vector<int> getVertices(int u){
			TreeNode* r = vec[u].arbiEdge;

			//	Preliminary checks
			if(r == NULL)
				return {u};

			vector<int> ver;
		 	r = t.findBSTRoot(r);
			queue<TreeNode*> q;
			q.push(r);

			while(!q.empty()){
				TreeNode* cur = q.front();
				q.pop();
				if(vec[cur->ver1].arbiEdge == cur){
					ver.push_back(cur->ver1);
				}
				if(vec[cur->ver2].arbiEdge == cur){
					ver.push_back(cur->ver2);
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
				vec[i].arbiEdge = NULL;
			}
		}

		bool connected(int u, int v){
			if(vec[u].arbiEdge == NULL || vec[v].arbiEdge == NULL)
				return false;
			return t.findBSTRoot(vec[u].arbiEdge) == t.findBSTRoot(vec[v].arbiEdge);
		}

		bool isPresent(int u_, int v_){
			int u = min(u_,v_), v = max(u_,v_);
			return edgeMp.find({u,v}) != edgeMp.end();
		} 


		bool isBefore(TreeNode* node1,TreeNode* node2){
			TreeNode* left = t.split(node1,LEFT);
			if(t.findBSTRoot(node1) == t.findBSTRoot(node2)){
				t.merge(left,node1);
				return true;
			}
			t.merge(left,node1);
			return false;
		}

		TreeNode* makeRoot(int v){
			
			if(vec[v].arbiEdge == NULL)	return NULL;

			TreeNode* arbE = vec[v].arbiEdge;

			int u_ = arbE->ver1, v_ = arbE->ver2;
			mpEdge info = edgeMp[{min(u_,v_), max(u_,v_)}];

			TreeNode* splitEdge;
			if(info.oc1->ver1 == v)	splitEdge = info.oc1;
			else					splitEdge = info.oc2;

			TreeNode* left = t.split(splitEdge,LEFT);
			return t.merge(splitEdge, left);
		}
		
		void addEdge(int u_, int v_){

			int u = min(u_, v_), v = max(u_, v_);
			
			if(isPresent(u,v) || connected(u,v))	return;

			TreeNode* newNode1 = t.insertNode(u,v);
			TreeNode* newNode2 = t.insertNode(v,u);
			edgeMp[{u,v}] = mpEdge(newNode1, newNode2);

			TreeNode* l = makeRoot(u);
			TreeNode* r = makeRoot(v);
			l = t.merge(l, newNode1);
			l = t.merge(l, r);
			l = t.merge(l, newNode2);

		//	Update arbitrary edges
			vec[u].arbiEdge = newNode1;
			vec[v].arbiEdge = newNode2;
		}

		void deleteEdge(int u_, int v_){

			int u = min(u_, v_), v = max(u_, v_);

			if(!isPresent(u,v))	return;

			TreeNode *first, *last;
			mpEdge info = edgeMp[{u,v}];
			if(isBefore(info.oc1, info.oc2)){
				first = info.oc1;
				last = info.oc2;
			}else{
				first = info.oc2;
				last = info.oc1;
			}

			edgeMp.erase({u,v});

		//	Re-label u and v
			u = first->ver1; v = first->ver2;

			TreeNode* left = t.split(first, LEFT);
			TreeNode* right = t.split(last,RIGHT);
			TreeNode* repl1 = t.findLeftMost(right);
			TreeNode* repl2 = t.findRightMost(left);

			TreeNode* middle;
			middle = t.split(last,LEFT);
			middle = t.split(first,RIGHT);
			t.merge(left, right);
			
			if(vec[u].arbiEdge == first || vec[u].arbiEdge == last){
				vec[u].arbiEdge = NULL;
				if(repl1!=NULL)
					vec[u].arbiEdge = repl1;
				else if(repl2!=NULL)
					vec[u].arbiEdge = repl2;
			}
			if(vec[v].arbiEdge == first || vec[v].arbiEdge == last){
				vec[v].arbiEdge = t.findLeftMost(middle);
			}

			delete first;
			delete last;
		}

		int getSize(int u){
			if(vec[u].arbiEdge == NULL)	return 1;
			TreeNode* r = t.findBSTRoot(vec[u].arbiEdge);
			return r->size;
		} 
};