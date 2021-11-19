#include <iostream>
//2Sat kosaraju
#include <bits/stdc++.h>
using namespace std;
const int MAX = 100000;
vector<int> adj[MAX];
vector<int> adjInv[MAX];
bool vizitat[MAX],vizitatInv[MAX];//inv=invers
stack <int> s;
int scc[MAX];
int counter=1;
void dfs(int n)
{
    if(vizitat[n])
        return;
    vizitat[n]=1;
    for (int i=0;i<adj[n].size();i++)
        dfs(adj[n][i]);
    s.push(n);
}
void dfsInv(int n)
{
    if(vizitatInv[n])
        return;

    vizitatInv[n] = 1;

    for(int i=0;i<adjInv[n].size();i++)
        dfsInv(adjInv[n][i]);

    scc[n] = counter;
}
void Sat2(int n,int m,int *a,int *b)
{
    //adaugam muchii la graf
    for(int i=0; i<m; i++)
    {
        //x=>x,-x=>n+x
        //-a[i] -> b[i],-b[i] -> a[i]
        if (a[i]>0 && b[i]>0)
        {
            adj[a[i]+n].push_back(b[i]);
            adjInv[b[i]].push_back(a[i]+n);
            adj[b[i]+n].push_back(a[i]);
            adjInv[a[i]].push_back(b[i]+n);
        }
        else if (a[i]>0 && b[i]<0)
        {
            adj[a[i]+n].push_back(n-b[i]);
            adjInv[n-b[i]].push_back(a[i]+n);
            adj[-b[i]].push_back(a[i]);
            adjInv[a[i]].push_back(-b[i]);
        }

        else if (a[i]<0 && b[i]>0)
        {
            adj[-a[i]].push_back(b[i]);
            adjInv[b[i]].push_back(-a[i]);
            adj[b[i]+n].push_back(n-a[i]);
            adjInv[n-a[i]].push_back(b[i]+n);
        }

        else
        {
            adj[-a[i]].push_back(n-b[i]);
            adjInv[n-b[i]].push_back(-a[i]);
            adj[-b[i]].push_back(n-a[i]);
            adjInv[n-a[i]].push_back(-b[i]);
        }
    }
    //pasul 1 din algoritmul lui Kosaraju, traversam graful original
    for (int i=1;i<=2*n;i++)
        if (!vizitat[i])
            dfs(i);
    //pasul 2 traversam graful invers
     while (!s.empty())
    {
        int n = s.top();
        s.pop();
        if (!vizitatInv[n])
        {
            dfsInv(n);
            counter++;
        }
    }
    //scc[]-valorile corespunzatoare
      for (int i=1;i<=n;i++)
    {
        //-x si x nu au voie sa fie in acelasi scc
        if(scc[i]==scc[i+n])
        {
            cout << "Expresia nu este satisfiabila";
            return;
        }
    }
    cout <<"Expresia este satisfiabila";
    return;

}
int main()
{
    int n,m;
    cin>>n>>m;//vr de variabile,m nr de clauze
    int *a,*b;
    a=new int[m];
    b=new int[m];
    for(int i=0; i<m; i++)
        cin>>a[i];
    for(int i=0; i<m; i++)
        cin>>b[i];
    Sat2(n,m,a,b);
    return 0;
}
