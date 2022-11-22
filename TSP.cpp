#include <bits/stdc++.h> 
using namespace std; 

int all_visited;

int tsp(int mask, int pos, vector<vector<int> > adj , int dp[][50], int n)
{
	if(mask==all_visited)
	{
		return adj[pos][0];
	}

	if(dp[mask][pos]!=-1) return dp[mask][pos];


	int minCost=9999999;
	for(int city=0;city<n;city++)
	{
		if((mask & (1<<city)) == 0)
		{
			int cost = adj[pos][city] + tsp(mask|(1<<city),city,adj,dp,n);
			
			minCost=min(cost,minCost);
		}
	}	
	return dp[mask][pos]=minCost;
}



void path(int mask,int pos,vector<vector<int> > adj , int dp[][50], int n)
{
    if(mask==all_visited) return;

    int ans = INT_MAX, chosenCity;

    for(int city=0;city<n;city++)
    {
        if((mask&(1<<city))==0)
        {
            int newAns = adj[pos][city] + dp[mask|(1<<city)][city];
            if(newAns < ans){
                ans = newAns;
                chosenCity = city;
            }
        }
    }

    cout<<chosenCity+1<<"-->"; 
    path(mask|(1<<chosenCity),chosenCity,adj,dp,n);
}

int validate(int source, int dest,int vertices,vector<vector<int> > edge_list,int weight)
{
	if(source<0 || source>=vertices || dest<0 || dest>=vertices)
	{
		cout<<"Invalid source or destination ...\n";
		return 0;
	}	

	if(edge_list[source][dest]==weight)
	{
		cout<<"Same edge alreay exists ...\n";
		return 0;
	}

	return 1;
}


int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);


	int vertices,edges;
	cin>>vertices>>edges;

	int n = vertices;

	vector<vector<int> > adj;

	for(int i=0;i<n;i++)
	{
		vector<int> v;
		for(int j=0;j<n;j++)
		{
			v.push_back(0);
		}
		adj.push_back(v);
	}

	
	for(int i=0;i<edges;i++)
    {
        int first_node,second_node,weight;
        cin >> first_node >> second_node >> weight;
        if(!validate(first_node-1,second_node-1,n,adj,weight))
        {
        	cout<<first_node<<" "<<second_node<<" "<<weight;
        	return 0;
        }
        adj[first_node-1][second_node-1] = weight;
    }

    int dp[(1<<n)][50];
    memset(dp,-1,sizeof(dp));

    int mask=1;

    all_visited = (1<<n)-1;
    tsp(mask,0,adj,dp,n);
    cout<<"Minimum Cost : "<< dp[1][0]<<"\n";

    mask=1;

    cout<<"Path : 1-->";
    path(mask,0	,adj,dp,n);
    cout<<1<<"\n";

	return 0;
}

