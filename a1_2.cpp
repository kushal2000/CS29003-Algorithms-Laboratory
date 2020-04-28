#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 
#include <time.h>

bool method0(int* arr,int n)
{
	int i,j,k;

	//choose a,b,c
	for(int a=1;a<=n-2;a++)
	{
		for(int b=a+1;b<=n-1;b++)
		{
			for(int c=b+1;c<=n;c++)
			{
				//find indexes of a,b,c,
				for(int m=0;m<n;m++)
				{
					if(arr[m]==a)
						j=m;
					if(arr[m]==b)
						k=m;
					if(arr[m]==c)
						i=m;
				}

				//condition to return false
				if(i<j&&j<k)
					return false;
			}
		}
	}
	return true;
}

bool method1(int* arr,int n)
{
	int a,b,c;
	//choose 3 indexes
	for(int i=0;i<n-2;i++)
	{
		for(int j=i+1;j<n-1;j++)
		{
			for(int k=j+1;k<n;k++)
			{
				//check if values at choosen indexes do not violate
				c = arr[i]; a = arr[j] ; b = arr[k];
				if(a<b&&b<c)
					return false;
			}
		}
	}
	return true;
}

bool method2(int* arr,int n)
{
	int c,temp;
	//set value of c
	for(int i=0;i<n-2;i++)
	{
		c = arr[i];
		temp = c;
		//check if following values less than c are in strictly decreasing order
		for(int j=i+1;j<n;j++)
		{
			if(arr[j]<c)
			{
				if(arr[j]<temp)
					temp=arr[j];
				else
					return false;
			}
		}
	}
	return true;
}

bool method3(int* arr,int n)
{
	int highest=arr[0];int highest_index=0;
	int high=arr[0];int high_index=0;
	int low=-1;int low_index=-1;

	for(int i=1;i<n;i++)
	{
		//find highest value so far
		if(arr[i]>highest)
		{
			highest=arr[i];
			highest_index=i;
		}

		//find highest value initially
		if(arr[i]>high)
		{
			if(low_index==-1)
			{
				high=arr[i];
				high_index=i;
			}
		}

		//find lowest value
		else
		{
			if(low_index==-1||arr[i]<low)
			{
				low=arr[i];
				low_index=i;

				//update high value only on encounter
				high=arr[highest_index];
				high_index=highest_index;
			}
			else
				return false;
		}
	}
	return true;
}

int main()
{
	cout << "n = ";
	int n;
	cin >> n;
	cout << endl;
	cout << "+++ Sequence = ";
	int *arr=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		cin >> arr[i];
	}
	// for(int i=0;i<n;i++)
	// {
	// 	cout << arr[i];
	// }
	cout << "    Method 0: ";
	if(method0(arr,n))
		cout << "Algolicious\n";
	else
		cout << "Unalgolicious\n";

	cout << "    Method 1: ";
	if(method1(arr,n))
		cout << "Algolicious\n";
	else
		cout << "Unalgolicious\n";

	cout << "    Method 2: ";
	if(method2(arr,n))
		cout << "Algolicious\n";
	else
		cout << "Unalgolicious\n";

	cout << "    Method 3: ";
	if(method3(arr,n))
		cout << "Algolicious\n";
	else
		cout << "Unalgolicious\n";
}