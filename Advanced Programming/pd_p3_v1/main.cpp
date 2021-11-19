#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int N,M,DP[100][100],c1,c2,c3;
char S1[100],S2[100];

void Citire()
{
	cin.getline(S1, 100);
	cin.getline(S2, 100);
	cin >>c1>>c2>>c3;
	N = strlen(S1);
	M = strlen(S2);
}

void Rezolvare()
{
	int i,j;
	//DP[i][j] - numarul minim de operatii pentru a transforma //sirul format din primele i caractere din S1
	//in sirul format din primele j caractere din S2

	for (i=1;i<=N;i++)
		DP[i][0]=i;

	for (j=1;j<=M;j++)
		DP[0][j]=j;

	for (i=1;i<=N;i++)
		for (j=1;j<=M;j++)
		{
			if (S1[i]!=S2[j])
			{
				DP[i][j]=min(DP[i-1][j-1]+min(c1,min(c2,c3)), min(DP[i][j-1]+1,DP[i-1][j]+1));
			}
			else
			{
				DP[i][j]=min(DP[i-1][j-1], min(DP[i][j-1]+1,DP[i-1][j]+1));
			}
		}
}

void Afisare()
{

	cout <<DP[N][M]<<'\n';
}
int main()
{
	Citire();
	Rezolvare();
	Afisare();
	int i,j;
	i=N-1;
	j=M-1;
	cout<<"lista este invers:"<<endl;
	while(i >0&&j>0)
	{
		if(S1[i]==S2[j]&&i>0&&j>0)
		{
            cout<<"pastram "<<S1[i]<<endl;
			i--;
			j--;
		}

		// inlocuire
		else if(DP[i][j]==DP[i-1][j-1]+c1&&i>0&&j>0)
		{
			cout<<"am schimbat "<<S1[i]<<" cu "<<S2[j]<<endl;
			i--;
			j--;
		}

		// stergere
		else if(DP[i][j]==DP[i-1][j]+c2&&i>0)
		{
			cout<<"am sters "<<S1[i]<<endl;
			i--;
		}

		// Adaugare
		else if(DP[i][j]==DP[i][j-1]+c3&&j>0)
		{
			cout<<"am adaugat "<<S2[j]<< endl;
			j--;
		}
	}
	if (i>0&&DP[i][j]==DP[i-1][j]+c2)
		cout<<"am sters "<<S1[0]<<endl;

	if (DP[i][j]==DP[i][j-1]+c3&&j>0)
		cout<<"am adaugat "<<S2[0]<<endl;

	cout<<endl;
	for (int i=0;i<=N;i++)
	{
		for (int j=0;j<=M;j++)
			cout<<DP[i][j]<< " ";
		cout<<endl;
	}

	return 0;
}
