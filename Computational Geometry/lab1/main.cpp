
#include <iostream>
using namespace std;
struct punct {
    float x,y,z;
};
float verificare(punct A1, punct A2, punct A3)
{
    float a;
    if((A1.x-A2.x)==0)
        if((A1.y-A2.y)==0)
            if((A1.z-A2.z)==0)
                return 1;
            else {
                a=(A3.z-A1.z)/(A2.z-A1.z);
            }
        else {
            a=(A3.y-A1.y)/(A2.y-A1.y);
            if(a*(A2.z-A1.z)!=(A3.z-A1.z))
                return 0;
        }
    else {
        a=(A3.x-A1.x)/(A2.x-A1.x);
        if(a*(A2.z-A1.z)!=(A3.z-A1.z))
            return 0;
        else if(a*(A2.y-A1.y)!=(A3.y-A1.y)) return 0;
    }

    return a;
}
int main()
{
    punct A1,A2,A3;
    float a;
    cin>>A1.x>>A1.y>>A1.z;
    cin>>A2.x>>A2.y>>A2.z;
    cin>>A3.x>>A3.y>>A3.z;
    a=verificare(A1,A2,A3);
    cout<<a<<endl;
    if(a==1) {
        cout<<"Coliniare"<<endl;
        cout<<"A2=1*A1+0*A3";
    } else {
        if(a==0)
            cout<<"Necoliniare";
        else {
            cout<<"Coliniare"<<endl;
            cout<<"A3="<<1-a<<"*A1+"<<a<<"*A2";
        }

    }

    return 0;
}

