#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 
#include <time.h>

double lorec(int n);

double hirec(int n)
{
	//base condition
	if(n==0) return 1;

	//recursive formula
	return 2*hirec(n-1) + lorec(n-1);
}

double lorec(int n)
{
	//base condition
	if(n==0) return 0;

	//recursive formula
	return hirec(n-1) + lorec(n-1);
}

double* hilorec(int n)
{
	double *curr=(double *)malloc(2*sizeof(double));

	//base condition
	if(n==0)
	{
		curr[0]=1;
		curr[1]=0;
	}

	//recursive formula
	else
	{
		double *prev=hilorec(n-1);
		curr[0]=2*prev[0]+prev[1];
		curr[1]=prev[0]+prev[1];
	}

	return curr;
}

double* hiloformula(int n)
{
	//formula computation
	double *ans=(double *)malloc(2*sizeof(double));
	ans[0] = ((5+sqrt(5))/10)*pow(((3-sqrt(5))/2),n+1) + ((5-sqrt(5))/10)*pow(((3+sqrt(5))/2),n+1);
	ans[1] = ((-5-3*sqrt(5))/10)*pow(((3-sqrt(5))/2),n+1) + ((-5+3*sqrt(5))/10)*pow(((3+sqrt(5))/2),n+1);
	return ans;
}

int main()
{
	cout << "n = ";
	int n;
	cin >> n;
	cout << endl;
	double hi,lo;
	cout.precision(10); //set precision to 10 decimal points
	cout << "+++ Method 0\n"<<scientific; //set to scientific output
	hi=hirec(n); lo=lorec(n);
	cout << "    hi("<<n<<") = "<<hi<<", lo("<<n<<") = "<<lo<<endl;

	cout << "+++ Method 1\n";
	double *ans=hilorec(n); 
	cout << "    hi("<<n<<") = "<<ans[0]<<", lo("<<n<<") = "<<ans[1]<<endl;

	cout << "+++ Method 2\n";
	ans=hiloformula(n); 
	cout << "    hi("<<n<<") = "<<ans[0]<<", lo("<<n<<") = "<<ans[1]<<endl;
}