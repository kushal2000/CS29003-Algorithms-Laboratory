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

//utility function to find point of intersection of two lines
point intersect(line l1,line l2)
{
	point P;
	P.x = (l1.c-l2.c)/(l2.m-l1.m);
	P.y = (l2.m*l1.c-l1.m*l2.c)/(l2.m-l1.m);
	return P;
}

line *method1(line* l,int n,int *p)
{
	line *boundary = (line *)malloc(n*sizeof(line));
	int k = 0; //size of active boundary
	// line *ans;
	line K;
	int min = 100000000;

	//create an array of flags to check if a line has been used
	int *used = (int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		used[i]=0;
	}

	//find line with min slope
	int index =-1;
	for(int i=0;i<n;i++){
		if(l[i].m<min){
			K=l[i];
			min=K.m;
			index = i;
		}
	}

	//assing current line and point as well as add to boundary
	used[index]=1;
	point Q;
	Q.x = -100000000;
	Q.y = 0;
	boundary[k] = K;
	k++;

	line L;
	point P;
	while(1){
		line L;
		point P;
		P.x = 100000000;
		point P1;
		line L1;
		//to flag if no valid intersection point exists
		int flag = 0;

		//find the intersection point and line with least valid x
		for(int i=0;i<n;i++){
			if(used[i]==0){
				P1 = intersect(K,l[i]);
				if(P1.x > Q.x){
					flag=1;
					if(P1.x < P.x){
						P = P1;
						L = l[i];
					}
				} 
			}
		}
		if(flag==0)
			break;
		else{
			K = L;
			Q = P;
			used[K.num] = 1;
			boundary[k] = K;
			k++;
		}
	}
	*p = k;
	return boundary;
}

line *method2(line* l,int n,int *p)
{
	//boundary and boundary points constitute the boundary and first of it is initialised
	line *boundary = (line *)malloc(n*sizeof(line));
	point *boundary_points = (point *)malloc(n*sizeof(line));
	int k = 0; //size of active boundary
	boundary[k]=l[0];
	boundary_points[k].x = -100000000;
	boundary_points[k].y = -0;
	k++;
	for(int i=1;i<n;i++)
	{
		point P=intersect(boundary[k-1],l[i]);
		//cut boundary till last line does not satisfy valid conditions
		while(boundary_points[k-1].x>P.x)
		{
			k--;
			P=intersect(boundary[k-1],l[i]);
		}
		boundary[k] = l[i];
		boundary_points[k] = P;
		k++;
	}
	*p = k;
	return boundary;
}


void merge(line arr[], int l, int m, int r) 
{ 
    int i, j, k;
    //size of left sorted subarray 
    int n1 = m-l+1; 
    //size of right sorted subarray
    int n2 = r-m;

    //create the two sorted subarrays seperately
    line *L=(line *)malloc(n1*sizeof(line)); 
    line *R=(line *)malloc(n2*sizeof(line));
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l; // we change our original array from this position

    //standard logic to merge two sorted subarrays starting from index k
    while (i < n1 && j < n2) { 
        if (L[i].m <= R[j].m) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
	while (i < n1){ 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2){ 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(line arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 

int main()
{
	//Take input of no. of lines and the equations of the lines in specified format
	cout << "n = ";
	int n;
	cin >> n;
	int k;
	line *l = new line[n];
	for(int i=0;i<n;i++)
	{
		cin >> l[i].m >> l[i].c;
		l[i].num = i;
	}
	cout << "---------------------------------------------------------\n";
	cout << fixed;
	cout << "Lines before sorting\n" << setprecision(10);
	cout << endl;
	for(int i=0;i<n;i++)
	{
		cout << "Line " << l[i].num << ": y = " << l[i].m << " x + " << l[i].c << endl;
	}
	cout << "---------------------------------------------------------\n";
	//invoke method 1 and print result
	line* boundary = method1(l,n,&k);
	cout << "Method 1\n";
	cout << endl;
	point A;
	A.x = -100000000;
	A.y = 0;
	point B;
	if(k==1)
		cout << "Line " << boundary[0].num << ": From MINUS_INFINITY to PLUS_INFINITY\n";
	else{
		for(int i=0;i<k-1;i++)
		{
			point B = intersect(boundary[i],boundary[i+1]);
			if(i==0)
				cout << "Line " << boundary[i].num << ": From MINUS_INFINITY to ("<< B.x << " , " << B.y << ")\n";
			else
				cout << "Line " << boundary[i].num << ": From (" << A.x << " , " << A.y << ") to ("<< B.x << " , " << B.y << ")\n";
			A = B;
		}
		cout << "Line " << boundary[k-1].num << ": From (" << A.x << " , " << A.y << ") to PLUS_INFINITY\n";
	}
	cout << "---------------------------------------------------------\n";
	//invoke mergesort and get updated array of lines
	mergeSort(l,0,n-1);

	cout << "Lines after sorting\n";
	cout << endl;
	for(int i=0;i<n;i++)
	{
		cout << "Line " << l[i].num << ": y = " << l[i].m << " x + " << l[i].c << endl;
	}
	cout << "---------------------------------------------------------\n";
	//invoke method 2 and print result
	boundary = method2(l,n,&k);
	cout << "Method 2\n";
	cout << endl;
	A.x = -100000000;
	A.y = 0;
	if(k==1)
		cout << "Line " << boundary[0].num << ": From MINUS_INFINITY to PLUS_INFINITY\n";
	else{
		for(int i=0;i<k-1;i++)
		{
			point B = intersect(boundary[i],boundary[i+1]);
			if(i==0)
				cout << "Line " << boundary[i].num << ": From MINUS_INFINITY to ("<< B.x << " , " << B.y << ")\n";
			else
				cout << "Line " << boundary[i].num << ": From (" << A.x << " , " << A.y << ") to ("<< B.x << " , " << B.y << ")\n";
			A = B;
		}
		cout << "Line " << boundary[k-1].num << ": From (" << A.x << " , " << A.y << ") to PLUS_INFINITY\n";
	}
	cout << "---------------------------------------------------------\n";
	return 0;
}