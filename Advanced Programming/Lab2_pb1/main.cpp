#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct interval
{
    int p,u;
};
bool compare(interval i1,interval i2)
{
    if(i1.u<i2.u)
        return true;
    if(i1.u>i2.u)
        return false;
    if(i1.p<i2.p)
        return true;

    return false;

}
int main()
{
    vector<interval> v;
    int a,b;
    cin>>a>>b;
    int n;
    cin>>n;
    v.resize(n);
    for(int i=0; i<n; i++)
        cin>>v[i].p>>v[i].u;
    sort(v.begin(),v.end(),compare);
    vector<interval> sol;
    cout<<endl;
00000000
    for(int i=1; i<n; i++)
    {
        if(sol.size()==0)
        {
            if(v[i].p<=a&&v[i].u>=a)
                sol.push_back(v[i]);
        }
        else
        {
            if(sol.size()==1)//ajungem la ultimul interval care il contine pe a
            {
                if(v[i].p<=a)//cu cat ma duc mai in dr sa il contina pe a cu atat intervalul va fi mai mare pt ca sunt ordonate crescator dupa primul
                {

                    sol.clear();
                    sol.push_back(v[i]);
                }
                if(sol[0].u!=v[i].u)
                    sol.push_back(v[i]);//adaugam urmatorul interval care "lungeste intervalul" solutiilor
            }
            else
            {
                if(sol[sol.size()-1].u>=b)//daca am gasit deja sol iesim fortat
                    break;
                else
                {
                    if(v[i].u>sol[sol.size()-1].u)
                    {
                        if(v[i].p<=sol[sol.size()-2].u)//verificam daca intervalul nou pe care vrem sa il adaugam poate inlocui intervlul precedent pt o solutie mai buna
                        {
                            sol[sol.size()-1]=v[i];
                        }
                        else
                        {
                            //daca nu inlocuieste precedentul atunci prelungeste intervalul
                            sol.push_back(v[i]);
                        }
                    }
                }
            }
        }



    }
    for(int i=0;i<sol.size();i++)
        cout<<sol[i].p<<" "<<sol[i].u<<endl;
    if(sol.size()<=1)
        cout<<"-1";
    return 0;
}
