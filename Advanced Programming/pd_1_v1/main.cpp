#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{

	int n,i;
	vector<pair<int, int>> v;
	int m[100],mmax = 0;
	int next[100];
	int posb[100];

	cin>>n;
	for(i=0;i<n;i++)
	{
		pair<int, int> domino;
		cin>>domino.first;
		cin>>domino.second;
		v.push_back(domino);
		m[i]=1;
		posb[i]=0;
		next[i]=-1;
	}


	for(i=n-2;i>=0;i--)
	{
		int nr=0;
		for(int j=i+1;j<n;j++)
		{
			if (v[i].second==v[j].first&&m[i]<=m[j])
			{
				nr++;
				m[i]=m[j]+1;
				if (mmax<m[i])
					mmax=m[i];
				next[i]=j;
			}
			posb[i]=nr;
		}
	}

	for (i=0;i<n;i++)
	{
		if (next[i]!=-1&&m[i]==mmax)
			break;
	}
	cout<<posb[i]<<"\n";
	while(i!=-1)
	{
		cout<<v[i].first<<' '<<v[i].second;
		cout<<endl;
		i=next[i];
	}
	return 0;
}
