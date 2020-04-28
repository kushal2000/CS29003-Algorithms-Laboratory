#include <stdio.h> 
#include <string.h>
#include <bits/stdc++.h> 
using namespace std; 

vector <string> findallexpr(int n)
{
	vector <vector <string> > expr;
	for(int i=0;i<n;i++)
	{
		vector <string> vec;
		if(i==0)
		{
			//base condition of dp
			string s="1";
			vec.push_back(s);
		}
		else
		{
			int m=i+1;
			//additions
			for(int j=1;j<=m/2;j++)
			{
				for(int k=0;k<expr[j-1].size();k++)
				{
					for(int l=0;l<expr[m-j-1].size();l++)
					{
						string s1 = expr[j-1][k];
						string s2 = expr[m-j-1][l];
						string s = s1 + "+" + s2;
						int flag=0;

						//check if duplicate
						for(int a=0; a<vec.size();a++)
						{
							if(s==vec[a])
							{
								flag=1;
								break;
							}
						}

						//if not, add to expressions
						if(!flag)
							vec.push_back(s);
					}
				}
			}
			//multiplications
			for(int j=2;j<=sqrt(m);j++)
			{
				if(m%j==0)
				{
					for(int k=0;k<expr[j-1].size();k++)
					{
						for(int l=0;l<expr[m/j-1].size();l++)
						{
							string s1 = expr[j-1][k];
							int flag1=0; int flag2=0;
							//to check if adding brackets is necessary
							for(int a=0;a<s1.length();a++)
							{
								if(flag2==0&&s1[a]=='+')
									flag1=1;
								if(s1[a]=='(')
									flag2++;
								if(s1[a]==')')
									flag2--;
							}
							if(flag1)
								s1 = "(" + s1 + ")";

							string s2 = expr[m/j-1][l];
							flag1=0; flag2=0;
							//to check if adding brackets is necessary
							for(int a=0;a<s2.length();a++)
							{
								if(flag2==0&&s2[a]=='+')
									flag1=1;
								if(s2[a]=='(')
									flag2++;
								if(s2[a]==')')
									flag2--;
							}
							if(flag1)
								s2 = "(" + s2 + ")";

							//add multiplication of both strings
							string s = s1+"*"+s2;
							int flag=0;

							//check if duplicate
							for(int a=0; a<vec.size();a++)
							{
								if(s==vec[a])
								{
									flag=1;
									break;
								}
							}

							//if not, add to vector
							if(!flag)
								vec.push_back(s);
						}
					}
				}
			}
		}
		expr.push_back(vec);
	}
	return expr[n-1];
}

void printallexpr(vector <string> vec, int n)
{
	//appropriate printing formatting
	if(n<10)
		cout << n << "   = ";
	else
		cout << n << "  = ";
	for(int i=0;i<vec.size();i++)
	{
		if(i==0)
			cout << vec[i] << endl;
		else
			cout << "    = "<<vec[i]<<endl;

	}
	cout << "....."<<vec.size()<<" expressions\n";
}
int main()
{
	cout << "n = ";
	int n;
	cin >> n;
	vector <string> vec = findallexpr(n);
	cout << "+++ Before sorting\n";
	printallexpr(vec,n);

	//selection sorting done to vector
	for(int i=0;i<vec.size()-1;i++)
	{
		string s=vec[i];
		int count=0;
		int index=i;
		for(int k=0;k<s.length();k++)
		{
			if(s[k]=='1')
				count++;
		}
		for(int j=i;j<vec.size();j++)
		{
			int count1=0;
			for(int k=0;k<vec[j].length();k++)
			{
				if(vec[j][k]=='1')
					count1++;
			}
			if(count1>count||(count==count1&&vec[j].length()>vec[index].length()))
			{
				count=count1;
				index=j;
			}
		}
		string temp=vec[index];
		vec[index]=vec[i];
		vec[i]=temp;
	}

	cout <<endl;
	cout << "+++ After sorting\n";
	printallexpr(vec,n);
}