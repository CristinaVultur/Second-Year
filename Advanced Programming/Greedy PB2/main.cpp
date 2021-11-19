#include <iostream>

using namespace std;
//Complexitate: O(n)
//trecem o singura data prin toate nodurile, si maximul de comparatii facute pentru un nod este 3, deci O(n)
//citirea si primul si ultimul for au amandoua complexitate O(n)
int main()
{
    int *tata,*v,i,n,x,y,elsol=0;
    bool *sol;
    cin>>n;
    tata=new int[n+1];
    v=new int[n+1];//nr de vecini ai fiecarui nod
    sol=new bool[n+1];
    for(i=1;i<=n;i++)
    {
        tata[i]=0;
        sol[i]=false;
        v[i]=0;
    }
    for(i=1;i<n;i++)
    {
        cin>>x>>y;
        v[x]++;
        v[y]++;//incrementam nr de vecini ai nodurilor citite
        tata[y]=x;//reprezentam arborele prin vectorul de tati
    }
    for(i=1;i<=n;i++)
    {
        if(elsol==0)//daca solutia nu are inca elemente adaugam el curent, deorece cardinalul minim al multimii cerute este 1(un sg nod)
            {
                sol[i]=true;
                elsol++;
            }
        else{
            if(sol[tata[i]]==false)
            {
                //daca tatal nodului nu apartine solutiei atunci nodul este candidat pt solutie
                sol[i]=true;
                elsol++;
            }
            else{//daca tatal nodului apartine solutiei curente
                if(v[i]<v[tata[i]])//daca nodul curent are mai putini vecini (este adiacent cu mai putine noduri) decat tatal sau, atunci este un candidat mai bun la solutia noastra
                {
                    sol[tata[i]]=false;//tatal il scoatem din solutie si punem fiul
                    sol[i]=true;
                }
            }
        }
    }
    cout<<elsol<<endl;
    for(i=1;i<=n;i++)
    {
       if(sol[i]==true)
        cout<<i<<" ";
    }
    return 0;
}
