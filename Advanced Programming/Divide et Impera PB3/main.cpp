#include <iostream>
#include<bits/stdc++.h>
using namespace std;
double mediana(int *a,int *b,int n,int m)
{
    //a este vectorul cu nr cel mai mic de elem si b cu cel mai mare
    int mini=0,maxi=n,i,j,med; //maxi este lungimea celui mai mic vector
    while(mini<=maxi)//cat timp indicii max si min nu "trec unul de celalalt"
    {
        //partitionam cei 2 vectori in 2 submultimi("jumatati") ce contin elem din amandoua
        //toate elem din prima jumatate trebuie sa fie mai mici decat cea din a doua jumatate
        //daca aceasta conditie este indeplinita inseamna ca am gasit partitia buna care sa ne dea mediana
        i=(mini+maxi)/2;//aflam nr de elemente din a ce trebuie puse in prima jumatate
        j=((n+m+1)/2)-i;//nr de elem din b ce se afla in prima jumatate(-i pentru ca cele doua jumatati trebuie sa aiba cardinale egale, exceptie fiind cazul in care totalu(m+n) este impar, atunci avem cu un elem in plus in prima jumatate
        //restul elem din a si b se afla in a doua jumatate
        if(i<n&&j>0&&b[j-1]>a[i])//trebuie sa vedem daca partitia facuta a determinat ca prima jumatate a lui b sau a doua jumatate a lui a sa fie multimea vida sau nu
            mini=i+1;
        //daca nu sunt vide, atunci vefificam daca ultimul element din prima jumatate a lui b este mai mare decat primul element din a doua jum a lui a
        //daca da atunci partia facuta nu este corecta deoarece exita elemente in prima jumatate mai mari decat cele din a doua jumatate, deci mutam indexul minim la dreapta

        else if(i>0&&j<m&&b[j]<a[i-1]) //verificam daca prima jumatate a lui a si a doua jumatate a lui b nu sunt vide
                    maxi=i-1;
        //verificam daca ultimul elem din prima jumatate a este mai mare decat primul elem din a doua jum a lui b
        //daca da atunci partitia nu e buna,si trebuie sa ne mutam la stanga (deoarece exista elem mai mari in prima jumatate decat in a doua

        //daca conditiile sunt satisfacute atunci am gasit partitia buna
        else
        {
            if(i==0)//daca nu avem in prima jumatate elemente din a, returnam ultimul elemt din b, din prima jumatate
                med=b[j-1];
            else if(j==0) //daca nu avem in prima jumatate elem dn b, returnam ultimul elem din a care apartine primei jumatati
                med=a[i-1];
            else
                med=max(a[i-1],b[j-1]);//daca nr de elem este impar mediana este max dintre ultimele 2 numere din prima jumatate (nu apartin aceluias vector), dca este par verificam mai jos
            break;
        }
    }
    if((m+n)%2==1)
        return (double)med;//daca nr de elem este impar returnam mediana gasita mai sus cu fct max,exista un elem de mijloc
    //daca nr de elem este par atunci mediana va fi media dintre maximul dintre ultimele 2 elem din prima jum si minimul dintre primele 2 elem din a 2a jum
    if(i==n)
        return (med+b[j])/2.0;//daca nu exista elem din a in a doua jum
    if(j==m)
        return (med+a[i])/2.0;//daca nu exista elem din b in a doua jumatate
    return(med+min(a[i],b[j]))/2.0;
}
int main()
{
    int a[100],b[100],n,m;
    cin>>n;
    cin>>m;
    for(int i=0; i<n; i++)
        cin>>a[i];
    for(int i=0; i<m; i++)
        cin>>b[i];
    //apelam functia a.i. variabila a din ea sa fie vectorul cu dimensinea mai mica
    if(n<m)
        cout<<"Mediana este:"<<mediana(a,b,n,m);
    else
        cout<<"Mediana este:"<<mediana(b,a,m,n);
    return 0;
}
