#include<bits/stdc++.h>
using namespace std;
#define INF 1e18
#define ll long long
struct state
{
	ll dist;
	int pmask,pcap,p;
	state()
	{
		dist=INF;
	}
	void upd(ll _dist,int mask,int _pcap,int _p)
	{
		if(_dist<dist)
		{
			dist=_dist;
			pmask=mask;
			pcap=_pcap;
			p=_p;
		}
	}
};
class RouteOptimiser
{
public:
	int n,c,MAX;					// number of people, max capacity of each bus
	vector<vector<ll>> adj; 		// adjacency matrix corresponding to pickup points
	vector<ll> fdist;				// distances corresponding to destination
	vector<vector<vector<state>>> dp; 	// dp[i][j][k] is the minimum cost corresponding to mask i, j in the current bus, k is the last guy who boarded
	RouteOptimiser(){}
	RouteOptimiser(int _n,int _c,vector<vector<ll>> _adj,vector<ll> _fdist)
	{
		n=_n;
		c=_c;
		adj=_adj;
		fdist=_fdist;
		MAX=(1<<n);
	}
	void computeMinCost()
	{
		dp.assign(MAX,vector<vector<state>>(c+1,vector<state>(n)));
		ll cost;
		dp[0][0][0].dist=0;
		for(int mask=0;mask<MAX;mask++)
		for(int j=0;j<c;j++)
		for(int i=0;i<n;i++)
		{
			if(dp[mask][j][i].dist==INF)	continue;
			for(int x=0;x<n;x++)
			{
				if(mask&(1<<x))	continue;
				int nmask=mask|(1<<x);
				cost=0;
				if(j)
					cost=adj[i][x];
				cost+=dp[mask][j][i].dist;
				dp[nmask][j+1][x].upd(cost,mask,j,i);
				cost+=fdist[x];
				dp[nmask][0][x].upd(cost,mask,j,i);
			}
		}

		ll mn=INF;
		ll mask=MAX-1;
		int cap=0,x;
		for(int i=0;i<n;i++)
		{
			if(mn>dp[mask][cap][i].dist)
			{
				mn=dp[mask][cap][i].dist;
				x=i;
			}
		}
		cout<<"Minimum cost: "<<mn<<endl;
		vector<vector<int>> res;
		while(mask)
		{
			if(cap==0)	
				res.push_back(vector<int>({n}));
			res.back().push_back(x);
			state s=dp[mask][cap][x];
			mask=s.pmask;
			cap=s.pcap;
			x=s.p;
		}
		cout<<"Number of buses: "<<res.size()<<endl;
		cout<<"~~~Routes~~~"<<endl;
		for(vector<int> v:res)
		{
			for(int x:v)
			{
				cout<<x<<' ';
			}
			cout<<endl;
		}
	}
};
int main()
{
	int n,c;
	cout<<"Enter number of people and bus capacity:"<<endl;
	cin>>n>>c;
	vector<vector<ll>> adj(n,vector<ll>(n));
	vector<ll> fdist(n);
	cout<<"Enter the adjacency matrix:"<<endl;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	{
		cin>>adj[i][j];
	}
	cout<<"Enter the destination distance vector"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>fdist[i];
	}
	RouteOptimiser R(n,c,adj,fdist);
	R.computeMinCost();
}