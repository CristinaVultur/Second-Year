#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void mapare(unordered_map <string,int> &pp1,unordered_map<string,int> &pp2, string str,int dim3)
{
    float minn;
    if(pp1.find(str)!=pp1.end())
    {
        if(pp2.find(str)!=pp1.end())
        {
            minn=min(pp1.find(str)->second,min(pp2.find(str)->second,dim3));
            if(minn==pp1.find(str)->second)
            {
                pp1.erase(str);
                pp1.insert(make_pair(str,dim3));
            }
            if(minn==pp2.find(str)->second)
            {
                pp2.erase(str);
                pp2.insert(make_pair(str,dim3));
            }
        }
        else
            pp2.insert(make_pair(str,dim3));
    }
    else
        pp1.insert(make_pair(str,dim3));
}
int main()
{
    unordered_map<string, int> pp1,pp2;
    int n,L,f,h;
    string fL,hf,hL;
    float maxx=0;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>L>>f>>h;
        maxx=max(maxx,min(float(L)/2,min(float(f)/2,float(h)/2)));
        if(h>f) swap(h,f);
        if(f>L) swap(f,L);
        if(h>f) swap(h,f);
        fL=to_string(f)+" "+to_string(L);
        mapare(pp1,pp2,fL,h);
        hf=to_string(h)+" "+to_string(f);
        mapare(pp1,pp2,hf,L);
        hL=to_string(h)+" "+to_string(L);
        mapare(pp1,pp2,hL,f);
    }
    unordered_map<string,int>::iterator itr;
    for(itr=pp1.begin();itr!=pp1.end();itr++)
    {
        if(pp2.find(itr->first)!=pp2.end())
        {
            stringstream ss(itr->first);
            ss>>L>>f;
            h=itr->second+(pp2.find(itr->first))->second;
            maxx=max(maxx,min(float(L)/2,min(float(f)/2,float(h)/2)));
        }

    }
    cout<<maxx;
    return 0;
}
