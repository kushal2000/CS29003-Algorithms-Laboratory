#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 


int** readBoard(int m, int n)
{
	// Initialise a 2-D array of type int 
	int **F = (int **)malloc(sizeof(int *)*m);
	for(int i=0; i<m; i++)
		F[i] = (int *)malloc(sizeof(int)*n);

	// Enter 0 for white and 1 for black
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			cin >> F[i][j];

	return F;
}

void printboard(int **F, int r, int c, int m, int n, int M, int N)
{
	//r,c,m,n help in bounding the chosen chess board and we only print W OR B for that
	for(int i = 0; i < M; i++)
	{
		for(int j=0; j< N; j++)
		{
			if(i>=r && j>=c && i<(r+m) && j<(c+n))
			{
				if(F[i][j] == 1)
					cout << "B ";
				else
					cout << "W ";
			}
			else
				cout << ". ";
		}
		cout << endl;
	}
}

bool ischessboard(int **F, int r, int c, int m, int n)
{
	//for same sum of row and column % 2 , the value should also be same
	int odd, even;
	if((r+c)%2 == 1)
	{
		odd = F[r][c];
		if(odd == 1)
			even = 0;
		else
			even = 1;
	}
	else
	{
		even = F[r][c];
		if(even == 1)
			odd = 0;
		else
			odd = 1;
	}

	for(int i = 0; i < m; i++)
	{
		for(int j=0; j< n; j++)
		{
			if((r+c+i+j)%2 == 1)
			{
				if(F[r+i][c+j]!=odd)
					return false;
			}
			else
			{
				if(F[r+i][c+j]!=even)
					return false;
			}
		}
	}
	return true;
}

int* essquare(int** F, int m, int n)
{
	//exhaustive search
	int imax = -1; 
	int jmax = -1;
	int lmax = 0;

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			int L = (m-i)>(n-j)? (n-j):(m-i);
			for(int k = L; k > 0; k--)
			{
				//redundant to check further
				if(k <= lmax)
					break;
				if(ischessboard(F, i, j, k, k))
				{
					if(k > lmax)
					{
						imax = i;
						jmax = j;
						lmax = k;
						break;
					}
				}
			} 
		}
	}
	// cout << count << endl;

	int* square = (int *)malloc(sizeof(int)*3);
	square[0] = imax;
	square[1] = jmax;
	square[2] = lmax;

	return square;
}

int* dpsquare(int** F, int m, int n)
{
	int imax = -1; 
	int jmax = -1;
	int lmax = 0;

	//initialisation of dp array
	int **T = (int **)malloc(sizeof(int *)*m);
	for(int i=0; i<m; i++)
		T[i] = (int *)malloc(sizeof(int)*n);
	for(int i=0;i<m;i++)
		T[i][n-1] = 1;
	for(int i=0;i<n;i++)
		T[m-1][i] = 1;

	//logic for iteration
	for(int i=m-2; i>=0; i--)
	{
		for(int j=n-2; j>=0; j--)
		{
			if(F[i][j] == F[i+1][j] || F[i][j] == F[i][j+1])
			{
				T[i][j] = 1;
			}
			//one more check needed in equality condition
			else
			{
				int l1 = T[i+1][j];
				int l2 = T[i][j+1];
				T[i][j] = l1<l2? (l1+1):(l2+1);
				if(l1==l2)
				{
					if(F[i][j]!=F[i+l1][j+l2])
						T[i][j]--;
				}
			}
		}
	}

	//iterate over the array to get maximum value O(n^2)
	for(int i = 0; i < m; i++)
	{
		for(int j=0; j< n; j++)
		{
			if(T[i][j] > lmax)
			{
				imax = i;
				jmax = j;
				lmax = T[i][j];
			}
		}
	}

	int* square = (int *)malloc(sizeof(int)*3);
	square[0] = imax;
	square[1] = jmax;
	square[2] = lmax;

	return square;
}

int* esrectangle(int** F, int m, int n)
{
	//logic for iterative search
	int imax = -1; 
	int jmax = -1;
	int Mmax = 0;
	int Nmax = 0;
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			int M = m-i;
			int N = n-j;

			for(int k = M; k > 0; k--)
			{
				for(int l = N; l > 0; l--)
				{
					//redundant to search further
					if(k*l < Mmax*Nmax)
						break;
					if(ischessboard(F, i, j, k, l))
					{
						imax = i;
						jmax = j;
						Mmax = k;
						Nmax = l;
						break;
					}
				}			
			} 
		}
	}

	int* rectangle = (int *)malloc(sizeof(int)*3);
	rectangle[0] = imax;
	rectangle[1] = jmax;
	rectangle[2] = Mmax;
	rectangle[3] = Nmax;

	return rectangle;
}

int* dprectangle(int** F, int m, int n)
{
	int imax = -1; 
	int jmax = -1;
	int Mmax = 0;
	int Nmax = 0;

	int **R = (int **)malloc(sizeof(int *)*m);
	for(int i=0; i<m; i++)
	{
		R[i] = (int *)malloc(sizeof(int)*n);
		for(int j=0; j<n; j++)
			R[i][j] = 1;
	}

	//store max value of free colums on the right of a cell
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			int max_row = 0;
			while(j+max_row < (n-1) && F[i][j+max_row+1] != F[i][j+max_row])
			{
				max_row++;
			}
			for(int k=j+max_row; k>=j; k--)
			{
				R[i][k] = max_row - k + j + 1;
			}
			//we have already filled for max_row+1 number of values
			j+=max_row;
		}
	}

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			//for each i,j we find max area of the rectangle possible
			int max_col = 0;
			//single column area initialised
			int area = (max_col+1)*R[i][j];
			int loc_i = i;
			int loc_j = j;
			int loc_M = R[i][j];
			int loc_N = 1;
			int min_row = R[i][j];
			while(i+max_col < (m-1) && F[i+max_col+1][j] != F[i+max_col][j])
			{
				max_col++;

				//KEY DP Step: we checks for next column's R array value and the smaller one can only succeed in forming rectangle 
				min_row = min_row<R[i+max_col][j]? min_row:R[i+max_col][j];

				//check if this area is greater than original
				if((max_col+1)*min_row > area)
				{
					area = (max_col+1)*min_row;
					loc_M = max_col+1;
					loc_N = min_row;
					//check if this is greater than the global area
					if(area > Mmax*Nmax)
					{
						imax = i;
						jmax = j;
						Mmax = loc_M;
						Nmax = loc_N;
					}
				}
			}
		}
	}

	int* rectangle = (int *)malloc(sizeof(int)*3);
	rectangle[0] = imax;
	rectangle[1] = jmax;
	rectangle[2] = Mmax;
	rectangle[3] = Nmax;

	return rectangle;
}

int main()
{
	int m,n;
	cout << "m = ";
	cin >> m;
	cout << "n = ";
	cin >> n;

	int **F = readBoard(m,n);
	cout << endl;

	int* square = essquare(F, m, n);
	int i = square[0];
	int j = square[1];
	int l = square[2];

	cout << "+++ Exhaustive search: Square\n";
	printboard(F, i, j, l, l, m, n);
	cout << "Area = " << l*l << endl;
	cout << endl;

	int* rectangle = esrectangle(F, m, n);
	i = rectangle[0];
	j = rectangle[1];
	int M = rectangle[2];
	int N = rectangle[3];

	cout << "+++ Exhaustive search: Rectangle\n";
	printboard(F, i, j, M, N, m, n);
	cout << "Area = " << M*N << endl;
	cout << endl;

	square = dpsquare(F, m, n);
	i = square[0];
	j = square[1];
	l = square[2];

	cout << "+++ Dynamic Programming: Square\n";
	printboard(F, i, j, l, l, m, n);
	cout << "Area = " << l*l << endl;
	cout << endl;

	rectangle = dprectangle(F, m, n);
	i = rectangle[0];
	j = rectangle[1];
	M = rectangle[2];
	N = rectangle[3];

	cout << "+++ Dynamic Programming: Rectangle\n";
	printboard(F, i, j, M, N, m, n);
	cout << "Area = " << M*N << endl;
	cout << endl;
}