#include <iostream>

using namespace std;
struct punct
{
    int x,y;
};
int det(int a1, int a2,int b1,int b2)
{
    return (a1*b2)-(b1*a2);
}
int apartine(punct *p,int x,int y)
{
    if(x<p[0].x||x>p[1].x)
        return -1;
    if(p[0].x==p[1].x)
        if(y<p[0].y||y>p[1].y)
            return -1;

    if(x<p[2].x||x>p[3].x)
        return -1;
    if(p[2].x==p[3].x)
        if(y<p[2].y||y>p[3].y)
            return -1;
    return 1;
}
void intersectie(Node *a,Node *b)
{
    int a1,a2,b1,b2,c1,c2;
    Point p[4];
    p[0]=a->s.up;
    p[1]=a->s.low;
    p[2]=b->s.up;
    p[3]=b->s.low;
        if(p[0].x>p[1].x)
            swap(p[0],p[1]);
        else
        {
            if(p[0].x==p[1].x&&p[0].y>p[1].y)
                swap(p[0],p[1]);
        }
        if(p[2].x>p[3].x)
            swap(p[2],p[3]);
        else
        {
            if(p[2].x==p[3].x&&p[2].y>p[3].y)
                swap(p[2],p[3]);
        }
    a1=p[1].y-p[0].y;
    a2=p[3].y-p[2].y;
    b1=p[1].x-p[0].x;
    b2=p[3].x-p[2].x;
    c1=-(p[0].x*(p[1].y-p[0].y))+p[0].y*(p[1].x-p[0].x);
    c2=-(p[2].x*(p[3].y-p[2].y))+p[2].y*(p[3].x-p[2].x);
    int delta;
    delta=det(a1,a2,b1,b2);
    if(delta!=0)
    {
        int deltax,deltay;
        float x,y;
        deltax=det(-c1,-c2,b1,b2);
        deltay=det(a1,a2,-c1,-c2);
        x=float(deltax)/float(delta);
        y=float(deltay)/float(delta);

        if(apartine(p,x,y)==-1)
        {
            cout<<"Multimea vida 1";
            return;
        }
        cout<<"intersectia este:"<<x<<","<<y;
        intersectie.insert(Point(x,y));
        return;

    }
    else
    {
        if(det(a1,a2,-c1,-c2)==0&&det(b1,b2,-c1,-c2)==0)
        {
            if(p[1].x<p[2].x)
            {
                cout<<"Multimea vida 2";
                return;
            }
            else
            {
                if(p[1].x==p[2].x)
                {
                    if(p[1].y<p[2].y)
                    {
                        cout<<"multimea vida 3";
                        return;
                    }
                }
            }
            cout<<"intersectia este segmentul determinat de:("<<p[2].x<<","<<p[2].y<<")si("<<p[1].x<<","<<p[1].y<<")";
            intersectie.insert(p[2]);
            intersectie.insert(p[1]);
            return;
        }
        else
        {
            cout<<"Multimea vida 4";
        }
    }

}
int main()
{
    punct p[4];
    cin >> p[0].x >> p[0] .y;
    cin >> p[1].x >> p[1] .y;
    cin >> p[2].x >> p[2] .y;
    cin >> p[3].x >> p[3] .y;
    intersectie(p);

    return 0;
}
