#include<iostream>
#include <bits/stdc++.h>

using namespace std;
struct tablou
{
	int x;
	int y;
};
int main()
{
	tablou B[201][201],v[201];
    int n,i,j,x,y,a[201][201],m,k;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}

	for(j=2;j<=m;j++)
	{
		a[1][j]=a[1][j]+a[1][j-1];
		B[1][j].x=1;
		B[1][j].y=j-1;
	}
	for (i=2;i<=n;i++)
	{
		a[i][1]=a[i][1]+a[i-1][1];
		B[i][1].x=i-1;
		B[i][1].y=1;
	}

	for (i=2;i<=n;i++)
	{
		for (j=2;j<=m;j++)
		{
			if(a[i-1][j]>a[i][j-1])
			{
				a[i][j]=a[i][j]+a[i-1][j];
				B[i][j].x=i-1;
				B[i][j].y=j;
			}
			else
			{
				a[i][j]=a[i][j]+a[i][j-1];
				B[i][j].x=i;
				B[i][j].y=j-1;
			}
		}
	}

	cout<<a[n][m]<<endl;
	i=n;
	j=m;
	k=1;
	v[k].x=i;
	v[k].y=j;

	while(j!=1||i!=1)
	{
		k++;
		x=B[i][j].x;
		y=B[i][j].y;
		v[k].x=x;
		v[k].y=y;
		i=x;
		j=y;
	}

	for(i=k;i>=1;i--)
	{
		cout<<v[i].x<<" "<<v[i].y<<endl;
	}
	return 0;


}
