#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 

struct Node
{
	int* arr;
	int n;
};

Node* initheap(int p, int n)
{
	// Initialise an array of heap nodes 
	Node *heap = new Node[(n+p-1)/p];

	//Node 0 is a dummy node storing N = size of heap
	heap[0].n=1;

	int r = (n+p-1)/p;
	int i;
	//allocate memory in the heap nodes
	for(i=1; i<=r; i++)
	{
		heap[i].n=0;
		//allocate memory to array
		heap[i].arr = (int *)malloc(p*sizeof(int));
	}
	return heap;
}

bool parent_dist(Node* H, int child_idx)
{
	//base condition
	int parent_idx = child_idx/2;
	if(parent_idx==0)
		return false;

	//check parent and child nodes
	int* parent = H[parent_idx].arr;
	int* child = H[child_idx].arr;

	//find min in parent
	int min = INT_MAX;
	int min_idx = -1;
	for(int i=0;i<H[parent_idx].n;i++)
	{
		if(parent[i]<min)
		{
			min = parent[i];
			min_idx = i;
		}
	}

	//find max in child
	int max = -INT_MAX;
	int max_idx = -1;
	for(int i=0;i<H[child_idx].n;i++)
	{
		if(child[i]>max)
		{
			max = child[i];
			max_idx = i;
		}
	}

	//condition for swapping
	if(min < max)
	{
		parent[min_idx] = max;
		child[max_idx] = min;
		return true;
	}
	else
		return false;
}

void insert(Node* H, int p, int x)
{
	//check if last node is full, update last node
	if(H[H[0].n].n==p)
		H[0].n++;

	//insert into last node
	int last_idx = H[0].n;
	H[last_idx].arr[H[last_idx].n] = x;
	H[last_idx].n++;

	//check for disturbances and move up the heap
	while(parent_dist(H, last_idx))
		last_idx/=2;
}

void prnheap(Node *H)
{
	//check size of Heap first
	int N = H[0].n;

	//print all nodes one by one
	for(int i=1;i<=N;i++)
	{
		int len = H[i].n;
		cout << "[ ";
		for(int j=0;j<len;j++)
			cout << H[i].arr[j] << " ";
		cout << "]\n";
	}
}

//returns index of max element in root node
int findmax(Node *H)
{
	int max = -INT_MAX;
	int max_idx = -1;
	for(int i=0;i<H[1].n;i++)
	{
		if(H[1].arr[i]>max)
		{
			max = H[1].arr[i];
			max_idx = i;
		}
	}
	return max_idx;
}

void heapify(Node* H, int parent_idx)
{
	int N = H[0].n;

	int left_child_idx = parent_idx*2;
	int right_child_idx = parent_idx*2+1;

	int* parent = H[parent_idx].arr;
	int* left_child;
	int* right_child;

	//get min of parent node
	int min = INT_MAX;
	int min_idx = -1;
	for(int i=0;i<H[parent_idx].n;i++)
	{
		if(parent[i]<min)
		{
			min = parent[i];
			min_idx = i;
		}
	}

	//get max of left child node
	int left_max = -INT_MAX;
	int left_max_idx = -1;
	if(left_child_idx <= N)
	{
		left_child = H[left_child_idx].arr;
		for(int i=0; i<H[left_child_idx].n; i++)
		{
			if(left_child[i] > left_max)
			{
				left_max = left_child[i];
				left_max_idx = i;
			}
		}
	}

	//get max of right child node
	int right_max = -INT_MAX;
	int right_max_idx = -1;
	if(right_child_idx <= N)
	{
		right_child = H[right_child_idx].arr;
		for(int i=0; i<H[right_child_idx].n; i++)
		{
			if(right_child[i] > right_max)
			{
				right_max = right_child[i];
				right_max_idx = i;
			}
		}
	}

	//conditions for calling heapify and swapping
	if (right_max > left_max)
	{
		if(right_max > min)
		{
			parent[min_idx] = right_max;
			right_child[right_max_idx] = min;
			heapify(H, right_child_idx);
		}
	}
	else
	{
		if(left_max > min)
		{
			parent[min_idx] = left_max;
			left_child[left_max_idx] = min;
			heapify(H, left_child_idx);
		}
	}
}

void delmax(Node *H)
{
	int last_idx = H[0].n;

	//empty heap
	if(last_idx==0)
		return;

	int idx = findmax(H);
	//check if heap has only root left
	if(last_idx==1)
	{
		// return;
		// cout << "HELLO";
		H[1].n--;		
		int temp = H[1].arr[idx];
		H[1].arr[idx] = H[1].arr[H[1].n];
		H[1].arr[H[1].n] = temp;
		return;	
	}
	
	H[1].arr[idx] = H[last_idx].arr[H[last_idx].n-1];
	H[last_idx].n--;
	//update last node
	while(H[last_idx].n==0)
	{
		H[0].n--;
		last_idx--;
	}

	heapify(H,1);
}

int main() 
{ 
	int p;
	cout << "p = ";
	cin >> p;
	int n;
	cout << "n = ";
	cin >> n;

	Node *H = initheap(p,n);

	int *A = (int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		cin >> A[i];
		insert(H,p,A[i]);
	}

	cout << endl;
	cout << "+++ " << n << " insertions made\n";
	prnheap(H);

	for(int i=0;i<n;i++)
	{
		A[n-i-1]=H[1].arr[findmax(H)];
		delmax(H);
	}

	cout << endl;
	cout << "+++ " << n << " deletions made\n";
	cout << endl;

	cout << "+++ Input array sorted\n";
	for(int i=0; i<n; i++)
		cout << A[i] << " ";
	cout << endl;
} 