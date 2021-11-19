#include <iostream>
#include<bits/stdc++.h>
using namespace std;
struct punct
{
    int x,y;
};
long int distanta(punct a,punct b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
bool compararex(punct a,punct b)
{
    if(a.x<b.x)
        return true;
    if(a.x>b.x)
        return false;
    if(a.y<b.y)
        return true;
    return false;
}
bool compararey(punct a,punct b)
{
    if(a.y<b.y)
        return true;
    if(a.y>b.y)
        return false;
    if(a.x<b.x)
        return true;
    return false;
}
long int divide(vector <punct>v,int ns,int nd)
{
    long int dmin,d=0;
    int i,j;
    dmin=distanta(v[ns],v[nd]);
    if(nd-ns<=3)//daca sunt mai putin de 3 puncte consideram toate perechile posibile di de retine dist minima
    {
        for(i=ns; i<nd-1; i++)
            for(j=ns+2; j<nd; j++)
            {
                d=distanta(v[i],v[j]);
                if(dmin>d)
                    dmin=d;
            }
    return dmin;
    }
}
long int cucereste(vector<punct> v,int ns,int nd)
{
    long int dim=distanta(v[ns],v[nd]);
    //dmin=min(divide(v,0,nd/2),divide(v,nd/2,nd));
    if(nd>ns+3){
            int ds=cucereste(v,ns,nd/2);
            int dd=cucereste(v,nd/2,nd);
            if(dim>ds)
                dim=ds;
            if(dim>dd)
                dim=dd;
            return dim;
    }

     int d=divide(v,ns,nd);
     return d;


}
long int solutie(vector <punct> v,int n)
{
    long int dmin=cucereste(v,0,n);
    int drx=v[n/2].x;
    //abscisa dreptei verticale ce va imparti multimea punctelor in stanga si dreapta
    //am aflat dist minima dintre punctele separate
    //trb sa det daca exista o pereche de puncte (unul in ps si unul in pd) cu distanta mai mica decat mai mica decat dmin
    //det toate punctele care au distanta fata de dreapta dr mai mica decat dmin
    vector <punct> y;
    for(int i=0; i<n; i++)
    {
        if( (v[i].x-drx)<=dmin||(drx-v[i].x)<=dmin )
            y.push_back(v[i]);
    }
    //sortam vectorul dupa ordonata
    sort(y.begin(),y.end(),compararey);
    //cautam daca exista in y o perecehe de pct cu prop precendnta
    long int d;
    int m=y.size();
    for(int i=0; i<m-1; i++)
        for(int j=i+1; j<=i+7; j++)
        {
            d=distanta(y[i],y[j]);
            if(d<dmin)
                dmin=d;
        }
    return dmin;

}
int main()
{
    vector <punct> p;
    int n,i;
    long int d;
    punct a;
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>a.x>>a.y;
        p.push_back(a);
    }
    sort(p.begin(),p.end(),compararex);
    d=solutie(p,n);
    cout<<sqrt(d);
    return 0;
}
