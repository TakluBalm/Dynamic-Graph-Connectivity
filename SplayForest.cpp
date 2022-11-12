#include <bits/stdc++.h>
using namespace std;

struct TreeNode{
	TreeNode *parent, *left, *right;
	unsigned int size;
	int data;
	TreeNode(int data_){
		parent = left = right = NULL;
		size = 1;
		data = data_;
	}
};

class SplayForest{
	private:

		void updateSize(TreeNode* t){
			t->size = (t->right == NULL)?(0):(t->right->size) + (t->left == NULL)?(0):(t->left->size) + 1;
		}

		void right_rotate(TreeNode* n){
			TreeNode* p = n->parent;
			TreeNode* gp = p->parent;
			if (gp != NULL) {
				if(p == gp->right){
					gp->right = n;
				}else{
					gp->left = n;
				}
			}
			n->parent = gp;
			p->parent = n;
			p->right = n->left;
			if(p->right != NULL){
				p->right->parent = p;
			}
			n->left = p;
			updateSize(p);
			updateSize(n);
		}

		void left_rotate(TreeNode* n){
			TreeNode* p = n->parent;
			TreeNode* gp = p->parent;
			if (gp != NULL){
				if (p == gp->right){
					gp->right = n;
				}else{
					gp->left = n;
				}
			}
			n->parent = gp;
			p->parent = n;
			p->left = n->right;
			if(p->left != NULL){
				p->left->parent = p;
			}
			n->right = p;
			updateSize(p);
			updateSize(n);
		}

		void splay(TreeNode* n){
			while (n->parent != NULL){
				TreeNode* p = n->parent;
				TreeNode* gp = p->parent;

				if(gp == NULL){
					if(n == p->left){
						right_rotate(n);
					}else{
						left_rotate(n);
					}
					break;
				}
				if(n == p->left){
					if(p == gp->left){
						// zig-zig
						right_rotate(p);
						right_rotate(n);
					}else{
						// zig-zag
						right_rotate(n);
						left_rotate(n);
					}
				}else{
					if(p == gp->left){
						// zag-zig
						left_rotate(n);
						right_rotate(n);
					}else{
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

		TreeNode* getNext(TreeNode* t){
			if(t->right != NULL)	return findLeftMost(t->right);
			TreeNode* parent = t->parent;
			while(parent != NULL){
				if(t == parent->left)	return parent;
				t = parent;
				parent = t->parent;
			}
			return NULL;
		}

		TreeNode* split(TreeNode* t, bool right){
			splay(t);
			if(right){
				if(t->right == NULL)	return NULL;

				TreeNode* temp = t->right;
				t->right = temp->parent = NULL;
				t->size -= temp->size;
				return temp;
			}else{
				if(t->left == NULL)	return NULL;

				TreeNode* temp = t->left;
				t->left = temp->parent = NULL;
				t->size -= temp->size;
				return temp;
			}
		}

		TreeNode* merge(TreeNode* t1, TreeNode* t2){
			t1 = findRightMost(findBSTRoot(t1));
			t2 = findBSTRoot(t2);
			splay(t1);
			t1->right = t2;
			t1->size += t2->size;
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