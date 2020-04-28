#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 

struct Graph
{
	int n;
	char** airline;
	int** ticket_price;
};

Graph readgraph()
{
	struct Graph G;
	cout << "No. of cities = ";
	int n;
	cin >> n;
	G.n = n;

	G.airline = (char **)malloc(n*sizeof(char *));
	G.ticket_price = (int **)malloc(n*sizeof(int *));

	for(int i=0;i<n; i++)
	{
		G.airline[i] = (char *)malloc(n*sizeof(char ));
		G.ticket_price[i] = (int *)malloc(n*sizeof(int ));
	}

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(i!=j)
				G.ticket_price[i][j] = INT_MAX/3;
			else
				G.ticket_price[i][i] = 0;
			G.airline[i][j] = 'x';
		}
	}

	while(true)
	{
		int c1, c2, cost;
		char a;
		cin >> c1;

		if(c1==-1)
			break;

		cin >> c2 >> cost >> a;
		G.airline[c1][c2] = a;
		G.ticket_price[c1][c2] = cost;
	}

	return G;
}

Graph getAIgraph(Graph G_orig)
{
	int n = G_orig.n;
	struct Graph G;
	G.n = n;
	G.airline = (char **)malloc(n*sizeof(char *));
	G.ticket_price = (int **)malloc(n*sizeof(int *));

	for(int i=0;i<n; i++)
	{
		G.airline[i] = (char *)malloc(n*sizeof(char ));
		G.ticket_price[i] = (int *)malloc(n*sizeof(int ));
	}

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			G.airline[i][j] = 'a';
			if(G_orig.airline[i][j] == 'a')
				G.ticket_price[i][j] = G_orig.ticket_price[i][j];
			else if(i!=j)
				G.ticket_price[i][j] = INT_MAX/3;
			else
				G.ticket_price[i][i] = 0;
		}
	}
	return G;
}

void printTicketPrices(int **C, int n)
{
	cout <<"\t\t";
	for(int i=0;i<n;i++)
	{
		cout << i << "\t";
	}
	cout << endl;

	for(int i=0; i<n; i++)
	{
		cout << i << "\t->\t";
		for(int j=0; j<n; j++)
		{
			if(C[i][j] != INT_MAX/3)
				cout << C[i][j] << "\t";
			else
				cout << "-" << "\t";
		}
		cout << endl;
	}
}

int **APSP(Graph G)
{
	int n = G.n;
	int **C = (int **)malloc(n*sizeof(int *));
	for(int i=0; i<n; i++)
		C[i] = (int *)malloc(n*sizeof(int));

	for(int i=0; i<n; i++)
	{
		for(int j=0;j<n; j++)
			C[i][j] = G.ticket_price[i][j];
	}

	for(int k=0; k<n; k++)
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if (C[i][k] + C[k][j] < C[i][j])
					C[i][j] = C[i][k] + C[k][j];
			}
		}
	}

	return C;
}

int **APSPone(Graph G, int **C1)
{
	int n = G.n;
	int **C = (int **)malloc(n*sizeof(int *));
	for(int i=0; i<n; i++)
		C[i] = (int *)malloc(n*sizeof(int));

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(C1[i][j] != INT_MAX/3)
			{
				C[i][j] = C1[i][j];
				continue;
			}
			C[i][j] = INT_MAX/3;
			for(int k=0; k<n; k++)
			{
				for(int l=0; l<n; l++)
				{
					if(C1[i][k] + G.ticket_price[k][l] + C1[l][j] < C[i][j])
						C[i][j] = C1[i][k] + G.ticket_price[k][l] + C1[l][j];
				}
			}
		}
	}
	return C;
}

int **APSPany(Graph G, int **C1)
{
	int n = G.n;
	int **C = (int **)malloc(n*sizeof(int *));
	for(int i=0; i<n; i++)
		C[i] = (int *)malloc(n*sizeof(int));
	int **C2 = APSP(G);

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(C1[i][j] != INT_MAX/3)
				C[i][j] = C1[i][j];
			else
				C[i][j] = C2[i][j];
		}
	}
	return C;
}

void prngraph(Graph G)
{
	int n = G.n;
	for(int i=0; i<n; i++)
	{
		cout << i << "\t->\t";
		for(int j=0; j<n; j++)
		{
			if(i!=j && G.ticket_price[i][j] != INT_MAX/3)
			{
				cout << j << " (" << G.ticket_price[i][j] << ", " << G.airline[i][j] << ")\t";
			}
		}
		cout << endl;
	}
}

int main() 
{ 
	Graph G = readgraph();
	cout << endl;

	cout << "+++ Original Graph \n";
	prngraph(G);
	cout << endl;

	Graph H = getAIgraph(G);
	cout << "+++ AI Subgraph\n";
	prngraph(H);
	cout << endl;

	int **C1 = APSP(H);
	cout << "+++ Cheapest AI prices\n";
	printTicketPrices(C1, H.n);
	cout << endl;

	int **C2 = APSPone(G, C1);
	cout << "+++ Cheapest prices with at most one non-AI leg\n";
	printTicketPrices(C2, H.n);
	cout << endl;

	int **C3 = APSPany(G, C1);
	cout << "+++ Cheapest prices with any number of non-AI legss\n";
	printTicketPrices(C3, H.n);
	cout << endl;
}