#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 

struct Node
{
	int key;
	Node* right;
	Node* left;
	Node* parent;
};

void preorder(Node* node)
{
	if(node!=NULL)
	{
		cout << node->key << "\t";
		preorder(node->left);
		preorder(node->right);
	}
}

void inorder(Node* node)
{
	if(node!=NULL)
	{
		inorder(node->left);
		cout << node->key << "\t";
		inorder(node->right);
	}
}

void prntree(Node* node)
{
	cout << "--- Preorder listing\n";
	preorder(node);
	cout << endl;

	cout << "--- Inorder listing\n";
	inorder(node);
	cout << endl;
}

void swapchild(Node* node)
{
	Node* temp = node->left;
	node->left = node->right;
	node->right = temp;
}

Node* lrotate(Node* pivot)
{
	Node* root = pivot->right;
	if(root==NULL)
		return NULL;
	Node* temp = root->left;

	root->left = pivot;
	pivot->right = temp;

	Node* temp1 = pivot->parent;
	if(temp1->right==pivot)
	{
		temp1->right=root;
		root->parent=temp1;
	}
	else
	{
		temp1->left=root;
		root->parent=temp1;
	}

	pivot->parent=root;
	if(temp!=NULL)
		temp->parent=pivot;

	return root;
}

Node* rrotate(Node* pivot)
{
	Node* root = pivot->left;
	if(root==NULL)
		return NULL;
	Node* temp = root->right;

	root->right = pivot;
	pivot->left = temp;

	Node* temp1 = pivot->parent;
	if(temp1->right==pivot)
	{
		temp1->right=root;
		root->parent=temp1;
	}
	else
	{
		temp1->left=root;
		root->parent=temp1;
	}

	pivot->parent=root;
	if(temp!=NULL)
		temp->parent=pivot;

	return root;
}	

void makeskew(Node* node)
{
	if(node==NULL)
		return;
	while(node->left!=NULL)
		node = rrotate(node);
	makeskew(node->right);
}

void bsort(Node* node)
{
	int n=1;
	Node* temp = node;
	while(temp->right!=NULL)
	{
		temp=temp->right;
		n++;
	}
	for(int i=0; i<n;i++)
	{
		temp = node;
		for(int j=0; j<n-1-i; j++)
		{
			if(temp->right->key<temp->key)
			{
				swapchild(temp);
				rrotate(temp);
				swapchild(temp);
			}
			else
				temp=temp->right;
		}
	}
}

void rebalance(Node *node, int n, int rot)
{
	//rot = 1 means right rotate on left subtree
	//rot = 0 means left rotate on right subtree
	if(node->right!=NULL&&rot==0)
	{
		for(int i=0;i<n/2;i++)
			lrotate(node->right);
		// prntree(node);
		rebalance(node->right,n/2,1);
		rebalance(node->right,n-n/2-1,0);
	}
	if(node->left!=NULL&&rot==1)
	{
		for(int i=0;i<n/2;i++)
			rrotate(node->left);
		// prntree(node);
		rebalance(node->left,n/2,0);
		rebalance(node->left,n-n/2-1,1);
	}
}

void store(Node* node, int** arr, int i, int j)
{
	if(i==j)
		return;
	node->key = arr[i][0];
	if(arr[i][1]>0)
	{
		Node* left_subtree = new Node();
		left_subtree->parent=node;
		node->left = left_subtree;
		store(left_subtree, arr, i+1, i+arr[i][1]+1);
	}
	if(arr[i][2]>0)
	{
		Node* right_subtree = new Node();
		right_subtree->parent=node;
		node->right = right_subtree;
		store(right_subtree, arr, i+1+arr[i][1], i+arr[i][1]+1+arr[i][2]);
	}
}

Node* readTree(int *x)
{
	cout << "n = ";
	int n;
	cin >> n;
	*x=n;

	int **arr = (int **)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
	{
		arr[i] = (int *)malloc(3*sizeof(int));
	}

	Node* dummy = new Node();
	dummy->key=-100000000;
	Node* node = new Node();
	dummy->right = node;
	node->parent=dummy;

	for(int i=0;i<n;i++)
	{
		cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
	}

	store(node, arr,0,n);
	return dummy;
}

int main() 
{ 
	int n;
	Node* dummy = readTree(&n);
	cout << "+++ Initial tree \n";
	prntree(dummy->right);
	cout << endl;

	makeskew(dummy->right);
	cout << "+++ Tree Made skew\n";
	prntree(dummy->right);
	cout << endl;

	bsort(dummy);
	cout << "+++ Tree after sorting\n";
	prntree(dummy->right);
	cout << endl;

	rebalance(dummy,n,0);
	cout << "+++ Tree after rebalancing \n";
	prntree(dummy->right);
} 
