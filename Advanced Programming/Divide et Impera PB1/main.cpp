#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int *v=new int[n];
    for(int i=0; i<n; i++)
        cin>>v[i];
    int st=0, dr=n,mij;
    while(st<=dr)
    {
        mij=(st+dr)/2;
        if(v[mij]==mij)
        {
            cout<<mij;
            break;
        }
        if(v[mij]>mij)
            dr=mij-1;
        else st=mij+1;
    }
    if(v[mij]!=mij)
        cout<<"nu s-a gasit";
    return 0;
}
