#include <bits/stdc++.h>
#include "SplayForest.cpp"
using namespace std;

class SpanningForest{
	private:
		struct mpNode{
			TreeNode* arbiEdge;
		};
	
		SplayForest t;
		vector<mpNode> vec;
		vector<bool> hasEdge;
	public:
		struct mpEdge{
			TreeNode* oc1;
			TreeNode* oc2;
			bool valid;
		};
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
			if(r==NULL)
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
			hasEdge.resize(n);
			for(int i = 0; i < n; i++){
				vec[i].arbiEdge = NULL;
				hasEdge[i] = false;
			}
		}

		bool connected(int u, int v){
			if(hasEdge[u]==false || hasEdge[v] == false)
				return false;
			return t.findBSTRoot(vec[u].arbiEdge) == t.findBSTRoot(vec[v].arbiEdge);
		}

		bool isPresent(int u, int v){
			return edgeMp[{u,v}].valid;
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
			if(!hasEdge[v]) return NULL;
			TreeNode* arbE = vec[v].arbiEdge;
			pair<int,int> edg = {arbE->ver1,arbE->ver2};
			TreeNode *in_edg  =  edgeMp[edg].oc1; // in_edg :  {u,v} out_edg : {v,u}
			TreeNode *out_edg  =  edgeMp[edg].oc2;
			if(in_edg->ver1 == v){
				TreeNode* tmp = out_edg;
				out_edg = in_edg;
				in_edg = tmp;
			}
			TreeNode* left = t.split(out_edg,LEFT);
			return t.merge(out_edg,left);
		}
		
		void addEdge(int u, int v){
			if(hasEdge[u]==false && hasEdge[v] == false){
				TreeNode* newNode1 = t.insertNode(u,v);
				TreeNode* newNode2 = t.insertNode(v,u);
				t.merge(newNode1, newNode2);
				mpEdge newMap;
				newMap.oc1 = newNode1;
				newMap.oc2 = newNode2;
				newMap.valid = true;
				edgeMp[{u,v}] = newMap;
				edgeMp[{v,u}] = newMap;
				hasEdge[u] = true;
				hasEdge[v] = true;
				vec[u].arbiEdge = newNode1;
				vec[v].arbiEdge = newNode1;
			}
			else if(hasEdge[u]==false || hasEdge[v] == false){
				int newVer,oldVer;
				if(hasEdge[u]==false){
					newVer =u;
					oldVer =v;
				}
				else{
					newVer = v;
					oldVer = u;
				}
				hasEdge[newVer] = true;
				TreeNode* splitting_edg = vec[oldVer].arbiEdge; // (x,u)
				if(splitting_edg->ver2 != oldVer){
					pair<int,int> edg = {splitting_edg->ver1,splitting_edg->ver2};
					if(edgeMp[edg].oc1->ver2 == oldVer){
						splitting_edg = edgeMp[edg].oc1;
					}
					else{
						splitting_edg = edgeMp[edg].oc2;
					}
				}
				TreeNode* newNode1 = t.insertNode(oldVer,newVer);
				TreeNode* newNode2 = t.insertNode(newVer,oldVer);
				mpEdge newMap;
				newMap.oc1 = newNode1;
				newMap.oc2 = newNode2;
				newMap.valid = true;
				edgeMp[{u,v}] = newMap;
				edgeMp[{v,u}] = newMap;
				vec[newVer].arbiEdge = newNode1;
				TreeNode* right = t.split(splitting_edg,RIGHT);
				TreeNode* update1 = t.merge(splitting_edg,newNode1);
				TreeNode* update2 = t.merge(update1,newNode2);
				TreeNode* update3 = t.merge(update2,right);
			}
			else{
				if(edgeMp[{u,v}].valid)	return;
				TreeNode* splitting_edg = vec[u].arbiEdge; // (x,u)
				if(splitting_edg->ver2 !=u){
					pair<int,int> edg = {splitting_edg->ver1,splitting_edg->ver2};
					if(edgeMp[edg].oc1->ver2 == u){
						splitting_edg = edgeMp[edg].oc1;
					}
					else{
						splitting_edg = edgeMp[edg].oc2;
					}
				}
				TreeNode* right = t.split(splitting_edg,RIGHT);
				TreeNode* reRoot = makeRoot(v);
				TreeNode* newNode1 = t.insertNode(u,v);
				TreeNode* newNode2 = t.insertNode(v,u);
				mpEdge newMap;
				newMap.oc1 = newNode1;
				newMap.oc2 = newNode2;
				newMap.valid = true;
				edgeMp[{u,v}] = newMap;
				edgeMp[{v,u}] = newMap;
				TreeNode* update1 = t.merge(splitting_edg,newNode1);
				TreeNode* update2 = t.merge(update1,reRoot);
				TreeNode* update3 = t.merge(update2,newNode2);
				TreeNode* update4 = t.merge(update3,right);
			}
		}

		void deleteEdge(int u, int v){
			if(!edgeMp[{u,v}].valid)	return;
			edgeMp[{u,v}].valid = false;
			edgeMp[{v,u}].valid = false;
			TreeNode *first_oc = edgeMp[{u,v}].oc1;
			TreeNode *second_oc = edgeMp[{u,v}].oc2;
			if(isBefore(second_oc,first_oc)){
				TreeNode* tmp = second_oc;
				second_oc = first_oc;
				first_oc  = second_oc;
			}
			TreeNode* split1 = t.split(first_oc,LEFT);
			TreeNode* redun_1 = t.findLeftMost(first_oc);
			TreeNode* split2 = t.split(redun_1,RIGHT);
			TreeNode* split3 = t.split(second_oc,RIGHT);
			TreeNode* repl_c1 = t.findLeftMost(split3);
			TreeNode* redun_2 = t.findRightMost(second_oc);
			TreeNode* split4 = t.split(redun_2,LEFT);
			TreeNode* repl_c2 = t.findRightMost(split1);
			TreeNode* merge1 = t.merge(split1,split3); // split1-split3 is Tree1 and split4 is Tree2
			if(vec[u].arbiEdge == first_oc || vec[u].arbiEdge == second_oc){
				if(first_oc->ver2 == u){
						vec[u].arbiEdge = t.findLeftMost(split4);
					}
				else{
					vec[u].arbiEdge = NULL;
					if(repl_c1!=NULL)
						vec[u].arbiEdge = repl_c1;
					else if(repl_c2!=NULL)
						vec[u].arbiEdge = repl_c2;
				}
			}
			if(vec[v].arbiEdge == first_oc || vec[v].arbiEdge == second_oc){
				if(first_oc->ver2 == v){
					vec[v].arbiEdge = t.findLeftMost(split4);
				}
				else{
					vec[v].arbiEdge = NULL;
					if(repl_c1!=NULL)
						vec[v].arbiEdge = repl_c1;
					else if(repl_c2!=NULL)
						vec[v].arbiEdge = repl_c2;
				}
			}
			if(vec[u].arbiEdge == NULL)
				hasEdge[u] = false;
			if(vec[v].arbiEdge == NULL)
				hasEdge[v] = false;
		}

		int getSize(int u){
			if(!hasEdge[u])	return 1;
			TreeNode* r = t.findBSTRoot(vec[u].arbiEdge);
			return r->size;
		} 
};