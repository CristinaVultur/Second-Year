#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//date:
/*3 11

4
3 5 10 8

3
4 3 7

4
6 8 2 9
*/
int main()
{

    int n, k;
    int vectors[100][100];
    int size[100];
    bool t[100][100];
    int prev[100][100];

    cin>>n>>k;
    for(int i=0;i<n;i++)
    {

        cin>>size[i];
        for(int j=0;j<size[i];j++)
        {
            cin>>vectors[i][j];
        }
    }

    for(int j=0; j<size[0];j++)
    {
        t[0][vectors[0][j]]=true;
        prev[0][vectors[0][j]]=-1;

    }

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<size[i+1];j++)
        {
            for(int l=0;l<k;l++)
            {

                if(t[i][l]==true)
                {
                    t[i+1][l+vectors[i+1][j]]=true;
                    prev[i+1][l+vectors[i+1][j]]=vectors[i+1][j];
                }
            }
        }
    }

    if(t[n-1][k]==true)
    {
        int i=n-1;
        while(i>0)
        {
            cout<<prev[i][k]<<' ';
            k=k-prev[i][k];
            i--;
        }
        if (prev[i][k]==-1)
            cout<<k;
    }
    else
    {
        cout<<"0";
    }
    return 0;
}
