#include <bits/stdc++.h> 
using namespace std; 

void print_path(int s,int d,vector<int> &parent)
{
	if(parent[d] == d ){
		cout<<d;
		return;
	}
	print_path(s,parent[d],parent);
	cout<<"->"<<d;
}

int bellman_ford(vector<int> &dist,vector<int> &parent,vector<pair<int,pair<int,int> > > edge_list,int n,int source)
{
	dist[source]=0;

	for(int i=1;i<=n-1;i++)
	{
		int done=1;
		for(auto j:edge_list)
		{
			
			int u,v,weight;
			u=j.first, v = j.second.first , weight = j.second.second;

			if(dist[u]!=INT_MAX && dist[v] > dist[u] + weight)
			{
				done=0;
				dist[v] = dist[u]+ weight;
				parent[v]=u;
			}
		}
		if(done)
			break;
	} 

	for(auto j:edge_list)
	{
		int u,v,weight;
		u=j.first, v = j.second.first , weight = j.second.second;

		if(dist[u]!=INT_MAX && dist[v] > dist[u] + weight)
		{
			return 0;
		}
	}

	return 1;
}

int validate(int source, int dest,int vertices,vector<pair<int, pair<int,int> > > edge_list)
{
	if(source<1 || source>vertices || dest<1 || dest>vertices)
	{
		cout<<"Invalid source or destination ...\n";
		return 0;
	}	

	for(int i=0;i<edge_list.size();i++)
	{
		if(source==edge_list[i].first && dest==edge_list[i].second.first)
		{
			cout<<"Duplicate edge found ...\n";
			return 0;
		}
	}

	return 1;
}

int main()
{
	freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    int vertices,edges;
   
    cin>>vertices>>edges;

    vector<pair<int,int> > adj[vertices+1];
    vector<pair<int, pair<int,int> > > edge_list;

    while(edges--)
    {
    	int source,dest,weight;
    	cin>>source>>dest>>weight;
    	if(!validate(source,dest,vertices,edge_list))
    	{
    		return 0;
    	}
    	adj[source].push_back({dest,weight});
    	edge_list.push_back({source,{dest,weight}});
    }

    vector<int> dist(vertices+1);	

    vector<int> parent(vertices+1);

    for(int i=0;i<=vertices;i++)
    	dist[i]=INT_MAX,parent[i]=i;


    if(bellman_ford(dist, parent, edge_list, vertices, 1))
    {
	    for(int i=2;i<=vertices;i++)
	    {
	    	cout<<"path from 1 to "<<i<<" : ";
	    	print_path(1,i,parent);
	    	cout<<endl;
	    	cout<<"Min Distance: "<<dist[i];
	    	cout<<"\n\n";
	    }
	    
    }else {
    	cout<<"Negative weight cycle exists\n";
    }

    return 0;
}
