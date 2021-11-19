import java.util.Scanner;

class Dama{
	int x[],n;
	void citire(){
		Scanner sc=new Scanner(System.in);
	    System.out.print("n=");
		n=sc.nextInt();
		x=new int[n+1];	
		
	}
	void retsol(int[] x){
		for(int i=1;i<=n;i++)
		     System.out.print("("+i+","+x[i]+") ");
		System.out.println();      
	}
	
	void backrec(int k){
		if(k==n+1)
		    retsol(x);
		else 
		    for(int i=1;i<=n ;i++){
				x[k]=i;
				if (cont(k))
				    backrec(k+1);
		    }
	}
	
	boolean cont(int k){
		for(int i=1;i<k;i++)
			if((x[i]==x[k]) || (Math.abs(x[k]-x[i])==k-i))
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
			    if(x[k]<n){
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
		Dama d=new Dama();
		d.citire();
		System.out.println("Varianta nerecursiva");		
		d.back();
		System.out.println("Varianta recursiva");		
		d.backrec(1);
	}
}