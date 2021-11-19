import java.util.Scanner;
class Inversiuni{
	int a[],n;
	void citire(){
		Scanner sc=new Scanner(System.in);
		System.out.print("nr de elemente=");
		n=sc.nextInt();
		a=new int[n];
		System.out.print("elementele:");
		for(int i=0;i<n;i++)
			a[i]=sc.nextInt();
	}
	int nrInvComplex(){ //algoritmul de complexitate n^2
		int nr=0;
		for(int i=0;i<n-1;i++)
			for(int j=i+1;j<n;j++)
				if(a[i]>a[j])
					nr++;
		return nr;			
	}
	
	int nrInv(int p,int u){//algoritmul bazat pe interclasare
	   if (p==u){
	       return 0;
	   }
	   else {
	   	   int m =(p+u)/2;
	        int n1=nrInv(p,m); 
	        int n2=nrInv(m+1,u);
	        return interclasare(p,m,u)+n1+n2;
	   }     	
	}
	
	int interclasare(int p,int m,int u){
		int b[]=new int[u-p+1];
	  	int i=p,j=m+1,k=0,nr=0;
	   	while ((i<=m)&&(j<=u)){
	    		if (a[i]<=a[j]){//!!daca sunt si egale - prioritate au cele din dr
	    			b[k]=a[i]; 
	    			i++;
	    			nr=nr+(j-m-1);
	    		}	 
	        	else{
	        		b[k]=a[j];
	        		j++;
	        		
	        	}	
	    		k++;
	    	}
   		while(i<=m){ //daca au mai ramas elemente din prima subsecventa a[p..m]
   		    	b[k]=a[i]; 
   		    	k++;
   		    	i++;	
   		    	nr=nr+(j-m-1);//adica u-m
   		}	
   		while(j<=u){ //daca au mai ramas elemente din a doua subsecventa a[m+1..u]
   		    	b[k]=a[j]; 
   		    	k++;
   		    	j++;
   		}	
	    	for (i=p;i<=u;i++)
	     	a[i]=b[i-p];
		return nr;
	}
	void afis(){
		for(int x:a)
			System.out.print(x+" ");
		System.out.println();	
	}
	
	public static void main(String sr[]){
		Inversiuni ob=new Inversiuni();
		ob.citire();
		System.out.println("nr de inversiuni calculat cu algoritmul n^2: "+ob.nrInvComplex());
		System.out.println("nr de inversiuni calculat cu interclasare: "+ob.nrInv(0,ob.n-1));
		System.out.print("Vectorul sortat: ");
		ob.afis();
	}
}	