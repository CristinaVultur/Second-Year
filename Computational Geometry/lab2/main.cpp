#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
struct punct
{
    int x, y;
} pivot;
int sens ( punct a, punct b, punct c )
{
    //-1 daca a,b,c sunt in sens anti-orar
    //1 daca a,b,c sunt in sens orar
    //0 daca sunt coliniare
    int area = ( b.x - a.x ) * ( c.y - a.y ) - ( b.y - a.y ) * ( c.x - a.x );

    if ( area > 0 )
        return -1;

    else if ( area < 0 )
        return  1;

    return 0;
}
int DistComp ( punct a, punct b )
{
    //fct folosita la compararea dist daca sunt coliniare
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}
bool Ordinea_polara ( punct a, punct b )
{
    //deterimina ordinea polara in fct de pivot
    int  ord = sens ( pivot, a, b );

    if ( ord == 0 )
        return DistComp ( pivot, a ) < DistComp ( pivot, b ); //daca sunt coliniare se ia "segemtul cel mai mare"

    return ( ord == -1 ); //true daca e in sens antiorar
    //false daca e in sens orar
}
stack<punct> grahamScan ( punct *p )
{
    stack<punct>a;
    int leasty = 0; //cel mai "mic punct"  in fct de y

    //daca y sunt egali se compara x
    for ( int i = 1; i < 4; i++ )
    {
        if ( p[i].y < p[leasty].y )
            leasty = i;

        else
        {
            if ( p[i].y ==p[leasty].y )
            {
                if ( p[i].x < p[leasty].x )
                    leasty = i;
            }
        }
    }
    punct cp[4];
    for(int i=0;i<4;i++)
        cp[i]=p[i];
    punct temp = p[0];
    p[0] = p[leasty];
    p[leasty] = temp; //schimbam a.i cel mai mic sa fie pe prima pozitie
    pivot = p[0];
    //sortam restul punctelor in fct de ordinea polara fata de pivot
    sort ( p + 1, p + 4, Ordinea_polara );
    int arrsize=1;
    for(int i=1;i<4;i++)
    {
        while(i<3&&sens(pivot,p[i],p[i+1])==0)
            i++;
        cp[arrsize]=p[i];
        arrsize++;
    }
    if(arrsize<3)
    {
        a.push(cp[0]);
        a.push(cp[1]);
        return a;
    }
    a.push ( p[0] );
    a.push ( p[1] );
    a.push ( p[2] );
    //for ( int i = 3; i < 4; i++ )
    int i = 3;
    punct top = a.top();
    a.pop();

    while (sens ( a.top(), top, p[i] ) != -1 )
    {
        top = a.top();
        a.pop();
    }

    a.push ( top );
    a.push ( p[i] );
    return a;
}
int apartine ( punct *p, punct stk )
{
    for ( int i = 0; i < 4; i++ )
    {
        if ( p[i].x == stk.x && p[i].y == stk.y )
            return i;
    }

    return -1;
}
int main()
{
    punct p[4];
    cin >> p[0].x >> p[0] .y;
    cin >> p[1].x >> p[1] .y;
    cin >> p[2].x >> p[2] .y;
    cin >> p[3].x >> p[3] .y;
    stack<punct> acoperire = grahamScan ( p );
    int n =acoperire.size() ;
    bool v[4];
    for(int i=0; i<4; i++)
        v[i]=false;
    cout<<n;
    punct a, b;

    a = acoperire.top();

    if ( apartine ( p, a ) != -1 )  v[apartine ( p, a )] = true;

    acoperire.pop();
    b = acoperire.top();

    if ( apartine ( p, b ) != -1 )  v[apartine ( p, b )] = true;

    acoperire.pop();

    if ( n == 4 )
    {
        punct c, d;
        c = acoperire.top();
        acoperire.pop();
        d = acoperire.top();
        acoperire.pop();  //ca sa fie diagoanle sunt perechile de puncte: primul cu al 3lea si al 2lea cu al 4lea
        cout << "I={(" << a.x << " " << a.y << "),(" << c.x << "  " << c.y << ")}";
        cout << "J={(" << b.x << " " << b.y << "),(" << d.x << "  " << d.y << ")}";
    }

    else
    {
        if ( n == 3 )
        {
            punct c;
            c = acoperire.top();
            if ( apartine ( p, c ) != -1 )
                v[apartine ( p, c )] = true;
            acoperire.pop();
            int i,in;
            for ( i = 0; i < 3; i++ )
                if ( v[i] == false )
                    in=i;

            cout << "I={(" << a.x << " " << a.y << "),(" << b.x << "  " << b.y << "),(" << c.x << "  " << c.y << ")}";
            cout << "J={(" << p[in].x << " " << p[in].y << ")}";
        }

        else
        {


            int i1 = -1;
            int  i2 = -1;

            for ( int i = 0; i < 3; i++ )
                if ( v[i] == false )
                {
                    if ( i1 == -1 )
                        i1 = i;
                    else i2 = i;
                }
            cout << "I={(" << a.x << " " << a.y << "),(" << b.x << "  " << b.y << ")}";
            cout << "J={(" << p[i1].x << " " << p[i1].y << "),(" << p[i2].x << "  " << p[i2].y << ")}";

        }
    }



    return 0;
}
