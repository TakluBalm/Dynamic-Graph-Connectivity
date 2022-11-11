#include <bits/stdc++.h>
using namespace std;

struct TreeNode{
	TreeNode *parent, *left, *right;
	unsigned int size, height;
	int data;
	TreeNode(int data_){
		parent = left = right = NULL;
		size = 1;
		height = 1;
		data = data_;
	}
};

class SplayForest{
	private:

		void right_rotate(TreeNode* n){
			TreeNode* p = n->parent;
			TreeNode* gp = p->parent;
			if (gp != NULL) {
				if (p == gp->right) {
					gp->right = n;
				}
				else {
					gp->left = n;
				}
			}
			n->parent = gp;
			p->parent = n;
			p->right = n->left;
			if (p->right != NULL) {
				p->right->parent = p;
			}
			n->left = p;
		}

		void left_rotate(TreeNode* n){
			TreeNode* p = n->parent;
			TreeNode* gp = p->parent;
			if (gp != NULL) {
				if (p == gp->right) {
					gp->right = n;
				}
				else {
					gp->left = n;
				}
			}
			n->parent = gp;
			p->parent = n;
			p->left = n->right;
			if (p->left != NULL) {
				p->left->parent = p;
			}
			n->right = p;
		}

		void splay(TreeNode* n){
			while (n->parent != NULL){
				TreeNode* p = n->parent;
				TreeNode* gp = p->parent;

				if (gp == NULL) {
					if (n == p->left){
						right_rotate(n);
					} else {
						left_rotate(n);
					}
					break;
				}
				if (n == p->left) {
					if (p == gp->left) {
						// zig-zig
						right_rotate(p);
						right_rotate(n);
					} else {
						// zig-zag
						right_rotate(n);
						left_rotate(n);
					}
					} else {
						if (p == gp->left) {
						// zag-zig
						left_rotate(n);
						right_rotate(n);
					} else {
						// zag-zag
						left_rotate(p);
						left_rotate(n);
					}
				}
			}
		}
	public:

		SplayForest(){};

		TreeNode* insertNode(int val){
			return new TreeNode(val);
		}

		TreeNode* split(TreeNode* t, bool right){
			splay(t);
			if(right){
				if(t->right == NULL)	return NULL;

				TreeNode* temp = t->right;
				t->right = temp->parent = NULL;
				return temp;
			}else{
				if(t->left == NULL)	return NULL;

				TreeNode* temp = t->left;
				t->left = temp->parent = NULL;
				return temp;
			}
		}

		TreeNode* merge(TreeNode* t1, TreeNode* t2){
			t1 = findRightMost(findBSTRoot(t1));
			t2 = findBSTRoot(t2);
			splay(t1);
			t1->right = t2;
			return t1;
		}

		TreeNode* findBSTRoot(TreeNode* t){
			while(t->parent != NULL){
				t = t->parent;
			}
			return t;
		}

		TreeNode* findRightMost(TreeNode* t1){
			if(t1 == NULL)	return NULL;
			while(t1->right != NULL)	t1 = t1->right;
			return t1;
		}

		TreeNode* findLeftMost(TreeNode* t){
			if(t == NULL)	return NULL;
			while(t->left != NULL)	t = t->left;
			return t;
		}
};