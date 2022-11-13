#include <bits/stdc++.h>
using namespace std;

#define RIGHT true
#define LEFT false

struct TreeNode{
	TreeNode *parent, *left, *right;
	unsigned int size;
	int ver1,ver2;
	TreeNode(int ver1_,int ver2_){
		parent = left = right = NULL;
		size = 1;
		ver1 = ver1_;
		ver2 = ver2_;
	}
};

class SplayForest{
	private:

		void updateSize(TreeNode* t){
			t->size = ((t->right == NULL)?(0):(t->right->size)) + ((t->left == NULL)?(0):(t->left->size)) + 1;
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
			p->left = n->right;
			if(p->left != NULL){
				p->left->parent = p;
			}
			n->right = p;
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
			p->right = n->left;
			if(p->right != NULL){
				p->right->parent = p;
			}
			n->left = p;
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

		TreeNode* insertNode(int u,int v){
			return new TreeNode(u,v);
		}

		TreeNode* getNext(TreeNode* t){
			//	Preliminary Checks
			if(t == NULL)	return NULL;

			//	If node has a right child
			if(t->right != NULL)	return findLeftMost(t->right);

			//	If node does not have a right child
			TreeNode* parent = t->parent;
			while(parent != NULL){
				if(t == parent->left)	return parent;
				t = parent;
				parent = t->parent;
			}

			return NULL;
		}

		void inorder(TreeNode* t){
			//	Preliminary Checks
			if(t == NULL)	return;

			inorder(t->left);
			cout << t->ver1 << ", " << t->ver2;
			inorder(t->right);
		}

		TreeNode* split(TreeNode* t, bool right){
			//	Preliminary Checks
			if(t == NULL)	return t;

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
			//	Preliminary Checks
			if(t1 == NULL || t2 == NULL)	return (t1)?t2:t1;

			//	Merge Step
			t1 = findRightMost(findBSTRoot(t1));
			t2 = findBSTRoot(t2);
			splay(t1);

			//	Update pointers
			t1->right = t2;
			t2->parent = t1;

			//	Update the sizes
			t1->size += t2->size;

			return t1;
		}

		TreeNode* findBSTRoot(TreeNode* t){
			//	Preliminary Checks
			if(t == NULL)	return NULL;

			while(t->parent != NULL)	t = t->parent;
			return t;
		}

		TreeNode* findRightMost(TreeNode* t1){
			//	Preliminary Checks
			if(t1 == NULL)	return NULL;

			while(t1->right != NULL)	t1 = t1->right;
			return t1;
		}

		TreeNode* findLeftMost(TreeNode* t){
			//	Preliminary Checks
			if(t == NULL)	return NULL;

			while(t->left != NULL)	t = t->left;
			return t;
		}
		
	
};