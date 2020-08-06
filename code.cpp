#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define INF 1e18
#define F first
#define S second
#define forl(i,n)	for(int i=0;i<n;i++)
ll N,M,C,V,T,D;
ll MAX;
struct state
{
	int i,j,k,l,m;
	state(){}
	state(int _i,int _j,int _k,int _l,int _m) 
	{
		i=_i,j=_j,k=_k,l=_l,m=_m;
	}
};
int main()
{
	cout<<"Enter the number of passengers"<<endl;
	cin>>N;
	cout<<"Enter the number of buses"<<endl;
	cin>>M;
	cout<<"Enter the capacity of each bus"<<endl;
	cin>>C;
	cout<<"Enter the velocity of each bus (in kmph)"<<endl;
	cin>>V;
	cout<<"Enter the time-window (in minutes)"<<endl;
	cin>>T;
	D=V*T/60.0;
	MAX=(1<<N);
	double dist[N][N],fdist[N];
	cout<<"Enter the distance-matrix (in mts)"<<endl;
	forl(i,N)
	forl(j,N)	
		cin>>dist[i][j],dist[i][j]/=1000;
	cout<<"Enter the final-dist vector (in mts)"<<endl;
	forl(i,N)
		cin>>fdist[i],fdist[i]/=1000;

	cout<<"Sit back and relax.. Computing.."<<endl;
	int minL=0;
	pair<double,state> dp[MAX][M+1][D+1][C+1][N];
	forl(i,MAX)forl(j,M+1)forl(k,D+1)forl(l,C+1)forl(m,N) dp[i][j][k][l][m].F=INF;
	dp[0][0][0][0][0].F=0;
	forl(i,MAX)
	forl(j,M)
	forl(k,D+1)
	forl(l,C+1)
	forl(m,N)
	{
		if(dp[i][j][k][l][m].F==INF)	continue;
		//Check for occupancy here... 
		if(l>=minL)
		{
			double d=k+fdist[m];
			if(d>D)	continue;
			d=dp[i][j][k][l][m].F+fdist[m];
			if(dp[i][j+1][0][0][0].F>d)
				dp[i][j+1][0][0][0]=mp(d,state(i,j,k,l,m));
		}
		if(l==C)	continue;
		double d;
		forl(x,N)
		{
			if(i&(1<<x))	continue;
			int nmask=i|(1<<x);
			int temp=k;
			d=dp[i][j][k][l][m].F;
			if(l>0)	d+=dist[m][x],temp+=ceil(dist[m][x]);
			if(temp<=D && dp[nmask][j][temp][l+1][x].F>d)
				dp[nmask][j][temp][l+1][x]=mp(d,state(i,j,k,l,m));
		}
	}
	double res=INF;
	state curr;
	forl(j,M+1)
		if(res>dp[MAX-1][j][0][0][0].F)
		{
			res=dp[MAX-1][j][0][0][0].F;
			curr=state(MAX-1,j,0,0,0);
		}
	cout<<res<<endl;
	vector<vector<int>> buses;
	vector<int> curbus;
	while(curr.i>0)
	{
		if(curr.l==0)	
		{
			reverse(curbus.begin(),curbus.end());
			if(curbus.size())
				buses.pb(curbus);
			curbus.clear();
		}
		else
			curbus.pb(curr.m);
		curr=dp[curr.i][curr.j][curr.k][curr.l][curr.m].S;
	}
	reverse(curbus.begin(),curbus.end());
	buses.pb(curbus);
	cout<<"Number of buses:"<<buses.size()<<endl;
	forl(i,buses.size())
	{
		cout<<"Bus "<<i+1<<": "<<buses[i].size()<<endl;
		cout<<"Order: ";
		for(int x:buses[i])
			cout<<x<<' ';
		cout<<N<<endl;
		cout<<endl;
	}
}