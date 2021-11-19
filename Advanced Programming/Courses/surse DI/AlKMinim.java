import java.util.*;
class KMin{
	int a[],n,k;
	void citire(){
		Scanner sc=new Scanner(System.in);
		System.out.print("nr de elemente=");
		n=sc.nextInt();
		a=new int[n];
		System.out.print("elementele: ");
		for(int i=0;i<n;i++)
			a[i]=sc.nextInt();
		System.out.print("k:");	
	     k=sc.nextInt();
	}
	int pozRand(int p,int u){
		Random ob=new Random();
		int r=ob.nextInt(u-p+1)+p;//translatat, rezultat inte p si u
		int aux=a[r];a[r]=a[p];a[p]=aux;
		return poz(p,u);
		
	}
	int poz(int p,int u){
		int i=p,j=u, depli=0,deplj=-1;
		while(i<j){
			if(a[i]>a[j]){
				int aux=a[i]; a[i]=a[j];	a[j]=aux;
				aux=depli; depli=-deplj; deplj=-aux;
			}
			i+=depli;j+=deplj;
		}
		return i;		
	}
	void afis(){
		for(int i=0;i<n;i++) 
			System.out.print(a[i]+" ");
		System.out.println();
	}
	int selKMin(int p, int u){
		int m=poz(p,u);
		if(m==k-1) return a[m];
		if(m<k-1) return selKMin(m+1,u);
		return selKMin(p,m-1);
	}
	int selKMin(){
		return selKMin(0,n-1);
	}
	public static void main(String arg[]){
		KMin ob=new KMin(); 
		ob.citire();
		System.out.println(ob.selKMin());
		ob.afis();
	}
}