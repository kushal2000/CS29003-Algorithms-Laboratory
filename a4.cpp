#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 

typedef struct{
	double m;
	double c;
	int num;
} line;

typedef struct{
	double x;
	double y;
} point;

struct Node
{
	int num;
	int num_oper;
	string oper;
	Node* next;
};

bool perfect(int n)
{
	int num=0;
	if(n==0)
		return false;

	while(n!=1)
	{
		if(n%2!=0)
			return false;
		n=n/2;
	}
	return true;
}

int num_factors(int n)
{
	int num=0;
	if(n==0)
		return 0;
	while(n%2==0)
	{
		n=n/2;
		num++;
	}
	return num;
}

void greedy1(int n)
{
	int oper = 0;
	cout << "Greedy 1\n";
	cout << "Start         : "<<n << endl;
	while(n!=1)
	{
		if(n%2==0)
		{
			n = n/2;
			cout << "Divide        : " << n << endl;
		}
		else
		{
			n = n-1;
			cout << "Decrement     : " << n << endl;
		}
		oper++;
	}
	cout << "Number of steps = " << oper << endl;
}

void greedy2(int n)
{
	int oper = 0;
	cout << "Greedy 2\n";
	cout << "Start         : "<<n << endl;
	while(n!=1)
	{
		if(n%2==0)
		{
			n = n/2;
			cout << "Divide        : " << n << endl;
		}
		else
		{
			if(n==3)
			{
				n = n-1;
				cout << "Decrement     : " << n << endl;
			}
			else
			{
				int m1 = num_factors(n+1);
				int m2 = num_factors(n-1);
				if(m1>m2)
				{
					n = n+1;
					cout << "Increment     : " << n << endl;
				}
				else
				{
					n = n-1;
					cout << "Decrement     : " << n << endl;
				}
			}
		}
		oper++;
	}
	cout << "Number of steps = " << oper << endl;
}

void greedy3(int n, int k, int *A)
{
	int oper = 0;
	cout << "Greedy 3\n";
	cout << "Start         : "<<n << endl;
	while(n!=1)
	{
		if(n%2==0)
		{
			n = n/2;
			cout << "Divide        : " << n << endl;
		}
		else
		{
			int num = 0;
			int factors = 0;
			for(int i=0;i<k;i++)
			{
				int x = n + A[i];
				if(n==3&&x==12)
				{
					continue;
				}
				if(x>0)
				{
					if(factors<=num_factors(x))
					{
						if(factors==num_factors(x))
						{
							if(x<num)
								num =x;
						}
						else
						{
							factors = num_factors(x);
							num = x;
						}
					}
				}
			}
			cout << "Add "<< num - n << "        : " << num << endl;
			n = num;
		}
		oper++;
	}
	cout << "Number of steps = " << oper << endl;
}

void optimal(int n,int x, int k, int *A)
{
	long m=pow(2,x);
	m = m+10;
	Node **ans = (Node **)malloc(m*sizeof(Node *));
	for(int j=0;j<m;j++)
	{
		ans[j]=new Node();
		// cout << "HELLO\n";
		ans[j]->num=j+1;
		int y = j+1;
		if(perfect(y))
		{
			Node *ptr = ans[j];
			ans[j]->num_oper = num_factors(y);
			for(int k=0;k<num_factors(j+1);k++)
			{
				ptr->oper = "Divide";
				Node *next = new Node();
				next->num = y/2;
				y=y/2;
				next->num_oper = ptr->num_oper-1;
				ptr->next = next;
				ptr = ptr->next;
			}
		}
		else
		{
			ans[j]->num_oper=-1;
		}
	}
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<m;j++)
		{
			for(int t=0;t<k;t++)
			{
				int y = j+A[t];

				if(y<m&&y>=0)
				{
				if(ans[y]->num_oper!=-1)
				{
					if(ans[j]->num_oper!=-1)
					{
						if(ans[y]->num_oper+1<ans[j]->num_oper)
						{
							ans[j]->oper ="Add";
							ans[j]->num_oper=ans[y]->num_oper+1;
							ans[j]->next = ans[y];
						}
					}
					else
					{
						ans[j]->oper ="Add";
						ans[j]->num_oper=ans[y]->num_oper+1;
						ans[j]->next = ans[y];
					}
				}
				}
				if(j%2==1)
				{
				y = (j+1)/2-1;
				if(y<m&&y>=0)
				{
				if(ans[y]->num_oper!=-1)
				{
					if(ans[j]->num_oper!=-1)
					{
						if(ans[y]->num_oper+1<ans[j]->num_oper)
						{
							ans[j]->oper ="Divide";
							ans[j]->num_oper=ans[y]->num_oper+1;
							ans[j]->next = ans[y];
						}
					}
					else
					{
						ans[j]->oper ="Divide";
						ans[j]->num_oper=ans[y]->num_oper+1;
						ans[j]->next = ans[y];
					}
				}
				}
				}
			}
		}
	}
	int steps = ans[n-1]->num_oper;
	cout << "Optimal\n";
	cout << "Start           : "<<ans[n-1]->num << endl;
	while(ans[n-1]->next!=NULL)
	{
		if(ans[n-1]->oper=="Add")
			cout << ans[n-1]->oper << " " << ans[n-1]->next->num-ans[n-1]->num << "          : " << ans[n-1]->next->num << endl;
		if(ans[n-1]->oper=="Divide")
			cout << ans[n-1]->oper << "          : " << ans[n-1]->next->num << endl;
		ans[n-1]=ans[n-1]->next;
	}
	cout << "Number of steps = " << steps << endl;
}

int main()
{
	cout << "n = ";
	int n;
	cin >> n;
	cout << "----------------------------\n";
	greedy1(n);
	cout << "----------------------------\n";
	greedy2(n);
	cout << "k = ";
	int k;
	cin >> k;
	int *A = new int[k];
	for(int i=0;i<k;i++)
		cin >> A[i];
	cout << "----------------------------\n";
	greedy3(n,k,A);
	cout << "----------------------------\n";
	float x = log(n)/log(2);
	int m = ceil(x)+1;
	if(m>12)
		m--;
	optimal(n,m,k,A);
	return 0;
}