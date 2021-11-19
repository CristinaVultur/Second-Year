#include <iostream>
#include <bits/stdc++.h>
//problema rucsacului branch and bound
using namespace std;
struct obiect
{
    float g;//greutatea
    int c;//costul
};
//structura nod o folosim pentru a retine informatii pentru deciziile pe care o sa le facem
struct nod
{
    int niv,profit,bound;
    float g;
};
bool comp(obiect a,obiect b)
{
    float r1=(float)b.c/b.g;
    float r2=(float)b.c/b.g;
    return r1>r2;
}
int bound(nod u,int n,int G, vector<obiect> ob)
{
    if(u.g>=G)//daca greutatea depaseste cea a rucsacului
        return 0;
    int pt=u.profit;//profit toatal
    int i=u.niv+1;//incepem sa adaugam elemente
    int gt=u.g;//greutatea totala initiala
    while(i<n&&gt+ob[i].g<=G)
    {
        gt+=ob[i].g;
        pt+=ob[i].c;
        i++;
    }
    if(i<n) //adaugam ultimul ob partial
    {
        pt+=(G-gt)*ob[i].c/ob[i].g;
    }
    return pt;

}
int main()
{
    int G,n;
    cin>>G>>n;
    vector <obiect>ob;
    obiect o;
    for(int i=0; i<n; i++){
        cin>>o.g>>o.c;
        ob.push_back(o);
    }

    sort(ob.begin(),ob.end(),comp);//sortam toate obiectele in ordie descrescatoare dupa raportul cost/greutate
    queue<nod> q;
    nod u,v;//u auxiliar la inceput, v nod propriuzis flosit pt calcule
    u.niv=-1;
    u.profit=u.g=0;
    q.push(u);//nod auxiliar de decizie
    int maxp=0;//initial profitul maxim e 0
    while(!q.empty())
    {
        //scoatem un nod
        u=q.front();
        q.pop();
        //if(u.niv==-1)//inseamna ca suntem la primul pas, deci niv nodului propriuzis va fi 1
        // v.niv=0;
        if(u.niv==n-1)//nu mai exista nivele dupa
            continue;
        v.niv=u.niv+1;//daca nu e ultimul nod, crestem nivelul, calculam profitul copiilor
        v.g=u.g+ob[v.niv].g;//adunam greutatea nodului de la niv curent cu greutatea nodului u
        v.profit=u.profit+ob[v.niv].c;//la fel si la cost
        if(v.g<=G&&v.profit>maxp)//daca greutatea cumulata este mai mare decat greutatea rucsacului si profitul e mai mare updatam profitul
            maxp=v.profit;
        v.bound=bound(v,n,G,ob);//calculam "bound of profit" in subarborele care are ca radacina nodul v

        if(v.bound>maxp)//, daca e mai mare decat maxp adaugam nodul in coada
            q.push(v);

        //cazul in care v nu este considerat parte din solutie:
        v.g=u.g;
        v.profit=u.profit;
        v.bound=bound(v,n,G,ob);
        if(v.bound>maxp)
            q.push(v);
    }
    cout<<maxp;
    return 0;
}
