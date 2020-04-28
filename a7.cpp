#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 

struct Node
{
	int key;
	Node* right;
	Node* left;
	Node* root;
};

int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
} 

int nCr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
} 
  
int countseq(int* A, int n)
{
	if(n <= 2)
		return 1;
	int *A_l = (int *)malloc(n*sizeof(int));
	int *A_r = (int *)malloc(n*sizeof(int));
	int l = 0, r = 0;
	for(int i = 1; i < n; i++)
	{
		if(A[i]<=A[0])
		{
			A_l[l]=A[i];
			l++;
		}
		else
		{
			A_r[r]=A[i];
			r++;
		}
	}
	return countseq(A_l,l)*countseq(A_r,r)*nCr(n-1,l);
}

int countOnes(int n) 
{ 
    if (n == 0) 
        return 0; 
    else
        return (n & 1) + countOnes(n >> 1); 
} 

bool isEven(int n)
{
	if(n%2==0)
		return true;
	return false;
}

int** findallseq(int *A, int n)
{
	int total = countseq(A,n);
	int **exprs = (int **)malloc(total*sizeof(int *));
	for(int i=0;i<total;i++)
		exprs[i] = (int *)malloc(n*sizeof(int));
	if(n<=2)
	{
		exprs[0]=A;
		return exprs;
	}

	int *A_l = (int *)malloc(n*sizeof(int));
	int *A_r = (int *)malloc(n*sizeof(int));
	int l = 0, r = 0;
	for(int i = 1; i < n; i++)
	{
		if(A[i]<=A[0])
		{
			A_l[l]=A[i];
			l++;
		}
		else
		{
			A_r[r]=A[i];
			r++;
		}
	}

	int **left_exprs = findallseq(A_l,l);
	int left_total = countseq(A_l,l);
	int **right_exprs = findallseq(A_r,r);
	int right_total = countseq(A_r,r);

	int count=0;
	for(int t=0;t<pow(2,l+r);t++)
	{
		int ones = countOnes(t);
		if(ones==r)
		{
			for(int j=0;j<left_total;j++)
			{
				for(int k=0;k<right_total;k++)
				{
					int *left_expr=left_exprs[j];
					int *right_expr=right_exprs[k];
					int *expr = (int *)malloc(n*sizeof(int));
					expr[0]=A[0];
					int temp_t = t;
					int temp_l = l;
					int temp_r = r;
					for(int i=0;i<l+r;i++)
					{
						if(isEven(temp_t))
						{
							expr[n-1-i] = left_expr[temp_l-1];
							temp_l--;
						}
						else
						{
							expr[n-1-i] = right_expr[temp_r-1];
							temp_r--;
						}
						temp_t = temp_t >> 1;
					}
					exprs[count]=expr;
					count++;
				}
			}
		}
	}
	return exprs;
}

void BSTins(Node* T,int x)
{
	if(x>T->key)
	{
		if(T->right==NULL)
		{
			Node *node = new Node();
			node->key = x;
			T->right = node;
		}
		else
			BSTins(T->right,x);
	}
	else
	{
		if(T->left==NULL)
		{
			Node *node = new Node();
			node->key = x;
			T->left = node;
		}
		else
			BSTins(T->left,x);
	}
}

void preorder(Node* node)
{
	if(node!=NULL)
	{
		cout << node->key << " ";
		preorder(node->left);
		preorder(node->right);
	}
}

void inorder(Node* node)
{
	if(node!=NULL)
	{
		inorder(node->left);
		cout << node->key << " ";
		inorder(node->right);
	}
}

void BSTprn(Node* node)
{
	cout << "    Preorder\t: ";
	preorder(node);
	cout << endl;

	cout << "    Inorder  \t: ";
	inorder(node);
	cout << endl;
}

Node* BSTcons(int *A, int n)
{
	if(n==0)
	{
		cout << "Invalid input";
		return NULL;
	}
	
	Node *T=new Node();
	T->key = A[0];
	for(int i=1;i<n;i++)
	{
		BSTins(T,A[i]);
	}
	return T;
}

bool BSTsame(Node* T1,Node* T2)
{
	if(T1->key!=T2->key)
		return false;

	bool right_flag;
	bool left_flag;
	if((T1->right==NULL)||(T2->right==NULL))
	{
		if((T2->right==NULL) && (T1->right==NULL))
			right_flag = true;
		else
			right_flag = false;
	}
	else 
		right_flag = BSTsame(T1->right,T2->right);

	if((T1->left==NULL)||(T2->left==NULL))
	{
		if((T2->left==NULL) && (T1->left==NULL))
			left_flag = true;
		else
			left_flag = false;
	}
	else
		left_flag = BSTsame(T1->left,T2->left);

	return right_flag&&left_flag;
}

void BSTfree(Node* T)
{
	if(T->right!=NULL)
		BSTfree(T->right);
	if(T->left!=NULL)
		BSTfree(T->left);
	if(T->right==NULL&&T->left==NULL)
		free(T);
}

int checkall(Node* T, int **L, int n, int total)
{
	int count=0;
	for(int i=0;i<total;i++)
	{
		Node* T1=BSTcons(L[i],n);
		// cout << "check\n";
		if(!BSTsame(T,T1))
			count++;
		// cout << "check\n";
		BSTfree(T1);
		// cout << "check\n";
	}	
	return count;
}

void printallseq(int **L, int total, int n)
{
	for(int i=0;i<total;i++)
	{
		cout << "    Sequence " << i+1 <<"\t: ";
		for(int j=0;j<n;j++)
			cout << L[i][j] << " ";
		cout << endl;
	}
}

int main() 
{ 
	int n;
	cout << "n = ";
	cin >> n;
	int *A = (int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
		cin >> A[i];
	cout << endl;

	int total = countseq(A,n);
	cout << "+++ Sequence Count\n";
	cout << "    Total no. of sequences = " << total << endl;
	cout << endl;
	
	cout << "+++ All sequences\n";
	int **L = findallseq(A,n);
	printallseq(L, total, n);
	cout << endl;

	cout << "+++ BST constructed from input array\n";
	Node* T = BSTcons(A,n);
	BSTprn(T);
	cout << endl;

	cout << "+++ Checking all sequences\n";
	int count = checkall(T,L,n,total);
	if(count==0)
		cout << "    All trees match\n";
	else
		cout << "    " << count << " trees do not match\n";
} 
