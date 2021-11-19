#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Complexitate:O(n)
//citire: O(n)
//calcularea sumelor in fct de indici :O(n)
//Jocul in sine: se trece o sg data prin vector, din 2 in 2 pasi , iar pt cei doi indici de la un pas se fac in total 2 comparatii maxim, deci jocul are comp :O(n)

int main()
{
    list <int> secv;
    vector <int> s;
    vector<char> suma1,suma2;
    int j1=0,j2=0;
    int x,n;
    cin>>n;
    list <int> :: iterator fr,bk;
    secv.assign(0,n);
    for(int i=0; i<n; i++)
    {
        cin>>x;
        s.push_back(x);
    }
    int sp=0,si=0;
    for(int i=0; i<n; i++)
    {
        if(i%2==0)
            sp+=s[i];
        else
            si+=s[i];
    }
    int pas=0,st=0,dr=n-1;
    if(sp>si)
    {
        while(pas<n)
        {
            if(st%2==0)
            {
                j1+=s[st];
                cout<<"jucatorul 1 alege"<<s[st]<<endl;
                st++;
            }
            else
            {
                j1+=s[dr];
                cout<<"jucatorul 1 alege"<<s[dr]<<endl;
                dr--;
            }
            pas++;
            x=rand()%2;
            if(x==0)
            {
                j2+=s[st];
                cout<<"jucatorul 2 alege"<<s[st]<<endl;
                st++;
            }
            else
            {
                j2+=s[dr];
                cout<<"jucatorul 2 alege"<<s[dr]<<endl;
                dr--;
            }
            pas++;
        }
    }

    if(si>sp)
    {
        while(pas<n)
        {
            if(dr%2!=0)
            {
                j1+=s[dr];
                cout<<"jucatorul 1 alege"<<s[dr]<<endl;
                dr--;
            }
            else
            {
                j1+=s[st];
                st++;
                cout<<"jucatorul 1 alege"<<s[st]<<endl;
            }
            pas++;
            x=rand()%2;
            if(x==0)
            {
                j2+=s[st];
                st++;
                cout<<"jucatorul 2 alege"<<s[st]<<endl;
            }
            else
            {
                j2+=s[dr];
                dr--;
                cout<<"jucatorul 2 alege"<<s[dr]<<endl;
            }
            pas++;
        }
    }
    cout<<"Suma juc 1:"<<j1<<endl;
    cout<<"Suma juc 2:"<< j2<<endl;
    return 0;
}
