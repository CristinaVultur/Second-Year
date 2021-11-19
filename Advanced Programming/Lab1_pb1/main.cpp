#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    unordered_set <string> triplet;
    int n,x,st,dr,sum;
    vector<int> v;
    cin>>n;

    for(int i=0; i<n; i++)
    {
        cin>>x;
        v.push_back(x);
    }
    v.resize(n);
    sort(v.begin(),v.end());

    for(int i=0; i<n-1; i++)
    {
        st=i+1;
        dr=n-1;
        while(st<dr)
        {
            sum=v[i]+v[st]+v[dr];
            if(sum<0)
                st++;
            else
            {
                if(sum>0)
                    dr--;
                else
                {
                    string s=to_string(v[i])+"*"+to_string(v[st])+"*"+to_string(v[dr]);
                    if(triplet.find(s)==triplet.end())
                    {
                        cout<<s<<endl;
                        triplet.insert(s);
                    }
                    st++;
                    dr--;
                }
            }
        }
    }
    return 0;
}
