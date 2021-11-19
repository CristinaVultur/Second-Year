import java.util.Scanner;
import java.io.*;
class Harti{
	int a[][],x[],n, nr;
	void citire(){
		int i,j,p,q,m;
		Scanner sc;
		try{
			sc=new Scanner(new File("Harti.in"));
		}
		catch(FileNotFoundException ex)	{
			System.out.println("Fisier inexistent. Introduceti lungimea si sirul de la tastatura.");
			sc=new Scanner(System.in);
		}
		n=sc.nextInt();
		m=sc.nextInt();
		a=new int[n+1][n+1];
		
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				a[i][j]=0;
		for(i=1;i<=m;i++){
			p=sc.nextInt();
			q=sc.nextInt();
			a[p][q]=a[q][p]=1;
		}
		x=new int[n+1];	
		
	}
	void retsol(int[] x){
		for(int i=1;i<=n;i++)
		     System.out.print("tara "+i+"-"+x[i]+" ");
		System.out.println();      
	}
	
	void backrec(int k){
		if(k==n+1)
		    retsol(x);
		else 
		    for(int i=1;i<=4;i++){
				x[k]=i;
				if (cont(k))
				    backrec(k+1);
		    }
	}
	
	boolean cont(int k){
		for(int i=1;i<k;i++)
			if(a[i][k]==1 && x[i]==x[k])
				return false;
		return true;		
	}

	void back(){
		int k=1;
		x=new int[n+1];
		for(int i=1;i<=n;i++)
		    x[i]=0;
		while(k>0){
			if(k==n+1){
			    retsol(x);
			    k--;	
			}
			else{
			    if(x[k]<4){
			    	x[k]++;
			       	if (cont(k))
			    	    k++;
			    } 
			    else{
			    	x[k]=0;
			    	k--;
			    }
			}    
		}    
	}
	public static void main(String arg[]){
		Harti h=new Harti();
		h.citire();
		System.out.println("Varianta nerecursiva");		
		h.back();
		System.out.println("Varianta recursiva");		
		h.backrec(1);
	}
}