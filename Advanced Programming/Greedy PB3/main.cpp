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

}//sortam dupa timpul de finalizare
int main()
{
    int n;
    cin>>n;
    vector <interval> v;
    v.resize(n);
    for(int i=0; i<n; i++)
    {
        cin>>v[i].p>>v[i].u;
    }
    int ok;
    sort(v.begin(),v.end(),compare);
    vector<list<interval>> sali;
    list<interval> l;
    l.push_back(v[0]);
    sali.push_back(l);
    l.pop_back();
    list <interval> :: iterator it;
    for(int i=1; i<n; i++)
    {
        ok=-1;
        for(int j=0; j<sali.size(); j++)
        {
            if((sali[j].back()).u<v[i].p)
            {
                if(ok==-1)
                {
                    ok=j;
                }
                else
                {
                    if(sali[ok].back().u>sali[j].back().u)
                    {
                        ok=j;
                    }
                }
            }

        }
        if(ok==-1)
        {
            l.push_back(v[i]);
            sali.push_back(l);
            l.pop_back();//daca nu a fost gasita nic o activitate de care putem lipi int curent creem o submultime noua
        }
        else
        {
            sali[ok].push_back(v[i]);
        }
    }

for(int j=0; j<sali.size(); j++)
{
    cout<<"Sala "<<j+1<<": activitati";
    for(it = sali[j].begin(); it != sali[j].end(); ++it)
        cout<<"["<<(*it).p<<","<<(*it).u<<"] ";
    cout<<endl;
}
return 0;
}
