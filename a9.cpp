#include <stdio.h> 
#include <bits/stdc++.h> 
using namespace std; 

struct Node{
	int val;
	Node* next;
};

struct Graph
{
	int v;
	char* color;
	int* index;
	vector <int> *adj;
};

Graph readgraph(int* x)
{
	struct Graph G;
	cout << "No. of vertices = ";
	int n;
	cin >> n;
	G.v = n;
	*x = n;

	G.adj = new vector<int>[n];
	G.color = (char *)malloc(n*sizeof(char));
	G.index = (int *)malloc(n*sizeof(int));

	cout << "Enter colors of vertices \n";
	for(int i=0;i<n; i++)
	{
		char c;
		cin >> c;
		G.color[i] = c;
		G.index[i] = i;
	}
	cout << "Enter edges \n";
	int v1,v2;
	while(true)
	{
		cin >> v1;
		if(v1==-1)
		{
			break;
		}
		cin >> v2;

		G.adj[v1].push_back(v2);
		G.adj[v2].push_back(v1);
	}
	return G;
}

void prngraph(Graph G, int n)
{
	for(int i=0;i<n;i++)
	{
		cout << "[" << G.color[i] << "]   ";
		cout << G.index[i] << " -> ";	

		for(int j=0;j<G.adj[i].size();j++)
			cout << G.index[G.adj[i][j]] << ",  ";

		cout << endl;
	}
}

Graph getcolgraph(Graph G, char color, int n, int *x)
{
	struct Graph G_col;
	int v=0;
	

	for(int i=0;i<n;i++)
	{
		if(G.color[i]==color)
			v++;
	}
	*x = v;

	G_col.adj = new vector<int>[v];
	G_col.color = (char *)malloc(v*sizeof(char));
	G_col.index = (int *)malloc(v*sizeof(int));

	int ind=0;
	for(int i=0;i<n;i++)
	{
		if(G.color[i]==color)
		{
			G_col.color[ind] = color;
			G_col.index[ind] = i;
			ind++;
		}	
	}

	for(int i=0;i<v;i++)
	{
		for(int j=0;j<G.adj[G_col.index[i]].size();j++)
		{
			if(G.color[G.adj[G_col.index[i]][j]]==color)
			{
				int k;
				for(k=0;k<v;k++)
				{
					if(G_col.index[k]==G.adj[G_col.index[i]][j])
						break;
				}
				G_col.adj[i].push_back(k);
			}
		}
	}

	return G_col;
}

void prncycle(Graph G, int* parent, int u, int root)
{
	if(parent[u]==root)
	{
		cout << G.index[u] << " (" << G.color[u] << ") ";
		u = root;
		cout << G.index[u] << " (" << G.color[u] << ") " <<  endl;
	}
	else
	{
		cout << G.index[u] << " (" << G.color[u] << ") " << " ";
		prncycle(G, parent, parent[u], root) ;
	}
}

void DFS(int root, int u, Graph G, int* visited,int* parent,int *level) 
{ 
    visited[u] = 1; 

    for (int i=0; i<G.adj[u].size(); i++) 
    {  	
    	if(u!=root)
    	{
	        if (level[G.adj[u][i]]!=-1 && level[G.adj[u][i]] < level[u] && parent[u]!=G.adj[u][i])
	        {
	        	// cout << u;
	        	// cout << G.adj[u][i];

	        	// level[G.adj[u][i]]=level[u]+1;
	        	// visited[G.adj[u][i]]=1;
	        	prncycle(G, parent, u, G.adj[u][i]);
	        	cout << endl;
	        	// cout << "hello\n";
	            // return;
	        }
	    }
    }

    for (int i=0; i<G.adj[u].size(); i++) 
    {
        if (visited[G.adj[u][i]] == 0)
        {
        	// cout << G.adj[u][i];
        	parent[G.adj[u][i]]=u;
        	level[G.adj[u][i]]=level[u]+1;
            DFS(root, G.adj[u][i], G, visited, parent, level); 
        } 
    }

    // for (int i=0; i<G.adj[u].size(); i++) 
    // {  	
    // 	if(u!=root)
    // 	{
	   //      if (G.adj[u][i] == root && parent[u]!=root)
	   //      {
	   //      	// cout << u;
	   //      	// cout << G.adj[u][i];

	   //      	level[G.adj[u][i]]=level[u]+1;
	   //      	visited[G.adj[u][i]]=1;
	   //      	prncycle(G, parent, u, root);
	   //      	// cout << "hello\n";
	   //          return;
	   //      }
	   //  }
    // }
} 
  
int *multi_DFS(Graph G, int n) 
{ 
    int *visited = (int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
    	visited[i]=0;

    int *parent = (int *)malloc(n*sizeof(int));
    int *level = (int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
    	visited[i]=0;

    for (int u=0; u<n; u++) 
    {
    	for(int i=0;i<n;i++)
    		level[i]=-1;

        if (visited[u] == 0) 
        {
        	// cout << u << endl;
        	level[u] = 0;
        	parent[u] = -1;
            DFS(u, u, G, visited, parent,level);
        }
    }
    return parent;
} 

Graph getrbgraph(Graph G, int* red_parents, int* blue_parents, Graph G_r, Graph G_b, int n, int r, int b)
{
	Graph G_rb = G;

	G_rb.adj = NULL;
	G_rb.adj = new vector<int>[n];

	for(int i=0;i<n;i++)
	{
		char c1 = G.color[i];
		for(int j=0;j<G.adj[i].size();j++)
		{
			char c2 = G.color[G.adj[i][j]];

			if(c1!=c2)
				G_rb.adj[i].push_back(G.adj[i][j]);
		}
	}

	for(int i=0;i<r;i++)
	{
		if(red_parents[i]!=-1)
		{
			int ind1 = G_r.index[i];
			int ind2 = G_r.index[red_parents[i]];
			G_rb.adj[ind1].push_back(ind2);
			G_rb.adj[ind2].push_back(ind1);
		}
	}

	for(int i=0;i<b;i++)
	{
		if(blue_parents[i]!=-1)
		{
			int ind1 = G_b.index[i];
			int ind2 = G_b.index[blue_parents[i]];
			G_rb.adj[ind1].push_back(ind2);
			G_rb.adj[ind2].push_back(ind1);
		}
	}
	return G_rb;
}

int main() 
{ 
	int n,r,b;
	Graph G = readgraph(&n);
	cout << endl;

	cout << "+++ Original Graph (G)\n";
	prngraph(G, n);
	cout << endl;

	Graph G_r = getcolgraph(G, 'r', n, &r);
	Graph G_b = getcolgraph(G, 'b', n, &b);

	cout << "+++ Red Subgraph (GR)\n";
	prngraph(G_r, r);
	cout << endl;

	cout << "+++ Blue Subgraph (GB)\n";
	prngraph(G_b, b);
	cout << endl;

	cout << "+++ Red Cycles\n";
	int* red_parents = multi_DFS(G_r, r);
	cout << endl;

	cout << "+++ Blue Cycles\n";
	int* blue_parents = multi_DFS(G_b, b);
	cout << endl;

	cout << "+++ Nonmonochromatic graph (GB)\n";
	Graph G_rb = getrbgraph(G, red_parents, blue_parents, G_r, G_b, n, r, b);
	prngraph(G_rb, n);
	cout << endl;

	cout << "+++ Multicolor Cycles\n";
	int* parents = multi_DFS(G_rb, n);
} 