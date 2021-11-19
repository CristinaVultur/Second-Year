#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
struct aparitii
{
    int v1,v2;
};
ifstream in1("fisier1.txt");
ifstream in2("fisier2.txt");
int main()
{
    string line;
    aparitii v;
    unordered_map <string,aparitii> tokens1;
    while(getline(in1,line))
    {

        char linie[line.size()+1];
        strcpy(linie, line.c_str());
        char *pt;
        pt=strtok(linie," ,.");
        while(pt!=NULL)
        {
            string key(pt);
            if(tokens1.find(key)==tokens1.end())
            {
                v.v1=1;
                v.v2=0;
                tokens1.insert(make_pair(key,v));
            }
            else
            {
                //unordered_map<string, aparitii>:: iterator itr;
                (tokens1.find(key)->second).v1++;
            }
            pt=strtok(NULL," ,.");
        }

    }
    while(getline(in2,line))
    {
        char linie[line.size()+1];
        strcpy(linie, line.c_str());
        char *pt;
        pt=strtok(linie," ,.");
        while(pt!=NULL)
        {
            string key(pt);
            if(tokens1.find(key)==tokens1.end())
               {
                v.v1=0;
                v.v2=1;
                tokens1.insert(make_pair(key,v));
            }
            else (tokens1.find(key)->second).v2++;
            pt=strtok(NULL," ,.");
        }

    }
    int suma1=0, suma2=0, sumaprod=0;
    unordered_map<string,aparitii>:: iterator itr;
    for (itr = tokens1.begin(); itr != tokens1.end(); itr++)
    {
        int a1,a2;
        a1=(itr->second).v1;
        a2=(itr->second).v2;
        suma1=suma1+a1*a1;
        suma2=suma2+a2*a2;
        sumaprod=sumaprod+a1*a2;

    }
    double dcos;
    dcos=sumaprod/(sqrt(suma1)*sqrt(suma2));
    cout<<dcos;

    return 0;
}
