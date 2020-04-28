#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 

int INTMAX=1000000000;

double printbuy1(double **M,int *c, int n, int C)
{
	int m = M[n-1][C];
	double ans = m*c[n-1];
	if(n!=1)
		ans += printbuy1(M,c,n-1,C-c[n-1]*m);
	cout << "Machine " << n-1 << " :  " << m << " copies, cost = " << m*c[n-1] << endl;
	return ans; 
}

double printbuy2(double **M,int *c, int n, int C,double **R)
{
	int m = M[n-1][C];
	double ans = m*c[n-1];
	if(n!=1)
		ans += printbuy2(M,c,n-1,C-c[n-1]*m,R);
	cout << "Machine " << n-1 << " :  " << m << " copies, cost = " << m*c[n-1];
	if(R[n-1][C])
		cout << " [Maintenance needed]\n";
	else
		cout << " [Maintenance not needed]\n";
	return ans; 
}

void optimalbuy1(int n,int C, int *c, double *s,double *t, double *p)
{
	cout << "Part 1: Best Buying Option\n";
	//memoizes total_profits
	double **T = (double **)malloc(n*sizeof(double*));
	//memomizes count of ith machine in ith row with jth column cost
	double **M = (double **)malloc(n*sizeof(double*));
	for(int i=0;i<n;i++)
	{
		T[i] = (double *)malloc((C+1)*sizeof(double));
		M[i] = (double *)malloc((C+1)*sizeof(double));
	}

	//initialise first row 
	for(int i=0;i<=C;i++)
	{
		// cout << c[0];
		if(i<c[0])
		{
			T[0][i]=-INTMAX;
			M[0][i]=0;
		}
		else
		{
			int m = (int)(i/c[0]);
			double e = (1-pow(p[0],m))*s[0]+pow(p[0],m)*t[0];
			T[0][i] = e;
			M[0][i] = m;
		}
	}

	//use the logic given in pdf 
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<=C;j++)
		{
			if(j<c[i])
				T[i][j]=-INTMAX;
			else
			{
				int m = (int)(j/c[i]);
				double e = -INTMAX;
				M[i][j] = 0;
				for(int k=1;k<=m;k++)
				{
					double e1 = (1-pow(p[i],k))*s[i]+pow(p[i],k)*t[i];
					double temp = T[i-1][j-k*c[i]];
					// cout << temp << endl;
					e1+=temp;
					// cout << e1 << endl;
					if(e < e1)
					{
						e = e1;
						M[i][j] = k;
					}
				}
				// cout << "HELLLO " << x << endl;
				T[i][j]=e;
			}
		}
	}
	// for(int i=0;i<n;i++)
	// {
	// 	for(int j=0;j<=C;j++)
	// 	{
	// 		cout << T[i][j] << "\t";
	// 	}
	// 	cout << endl;
	// }
	double x = printbuy1(M,c,n,C);
	cout << "Total buying cost      =    " << x << endl;
	cout << "Total expected profit  =    " << T[n-1][C] << endl;
}

void optimalbuy2(int n,int C, int *c, double *s,double *t, int *r, double *p, double *q)
{
	cout << "Part 2: Best Buying Option\n";
	//memoizes total profit
	double **T = (double **)malloc(n*sizeof(double*));
	//memomizes count of ith machine in ith row with jth column cost
	double **M = (double **)malloc(n*sizeof(double*));
	//memomizes maintenance status of ith machine in ith row with jth column cost
	double **R = (double **)malloc(n*sizeof(double*));

	for(int i=0;i<n;i++)
	{
		T[i] = (double *)malloc((C+1)*sizeof(double));
		M[i] = (double *)malloc((C+1)*sizeof(double));
		R[i] = (double *)malloc((C+1)*sizeof(double));
	}

	//initialise first row
	for(int i=0;i<=C;i++)
	{
		// cout << c[0];
		if(i<c[0])
		{
			T[0][i]=-INTMAX;
			M[0][i]=0;
		}
		else
		{
			int m = (int)(i/c[0]);
			double e1 = (1-pow(p[0],m))*s[0]+pow(p[0],m)*t[0];
			double e2 = (1-pow(q[0],m))*s[0]+pow(q[0],m)*t[0] - m*r[0];
			if(e1>e2)
			{
				T[0][i]=e1;
				R[0][i]=0;
			}
			else
			{
				T[0][i]=e2;
				R[0][i]=1;
			}
			M[0][i] = m;
		}
	}

	//use logic prescribed in pdf
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<=C;j++)
		{
			if(j<c[i])
				T[i][j]=-INTMAX;
			else
			{
				int m = (int)(j/c[i]);
				double e = -INTMAX;
				M[i][j] = 0;
				for(int k=1;k<=m;k++)
				{
					double e1 = (1-pow(p[i],k))*s[i]+pow(p[i],k)*t[i] + T[i-1][j-k*c[i]];;
					double e2 = (1-pow(q[i],k))*s[i]+pow(q[i],k)*t[i] - k*r[i] + T[i-1][j-k*c[i]];
					if(e < e1)
					{
						e = e1;
						M[i][j] = k;
						R[i][j] = 0;
					}
					if(e < e2)
					{
						e = e2;
						M[i][j] = k;
						R[i][j] = 1;
					}
				}
				// cout << "HELLLO " << x << endl;
				T[i][j]=e;
			}
		}
	}

	double x = printbuy2(M,c,n,C,R);
	cout << "Total buying cost      =    " << x << endl;
	cout << "Total expected profit  =    " << T[n-1][C] << endl;
}

int main() 
{ 
	int n;
	cout << "n = ";
	cin >> n;
	int C;
	int *c = (int *)malloc(n*sizeof(int));
	double *s = (double *)malloc(n*sizeof(double));
	double *t = (double *)malloc(n*sizeof(double));
	int *r = (int *)malloc(n*sizeof(int));
	double *p = (double *)malloc(n*sizeof(double));
	double *q = (double *)malloc(n*sizeof(double));

	cout << "Capital           (C) = ";
	cin >> C;

	cout << "Costs             (c) = ";
	for(int i=0;i<n;i++)
		cin >> c[i];

	cout << "Selling Price     (s) = ";
	for(int i=0;i<n;i++)
		cin >> s[i];

	cout << "Selling Price     (t) = ";
	for(int i=0;i<n;i++)
		cin >> t[i];

	cout << "Maintenance Cost  (r) = ";
	for(int i=0;i<n;i++)
		cin >> r[i];

	cout << "Probabilities     (p) = ";
	for(int i=0;i<n;i++)
		cin >> p[i];

	cout << "Probabilities     (q) = ";
	for(int i=0;i<n;i++)
		cin >> q[i];
	cout << "-------------------------------------------------------\n";
	optimalbuy1(n,C, c, s, t, p);
	cout << "-------------------------------------------------------\n";
	optimalbuy2(n,C, c, s, t, r, p, q);
	cout << "-------------------------------------------------------\n";
	return 0;
} 
