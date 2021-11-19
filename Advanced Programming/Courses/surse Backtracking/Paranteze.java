import java.util.Scanner;

class Paranteze{
	char x[];
	int n,dif;
	void citire(){
		Scanner sc=new Scanner(System.in);
	    System.out.print("n=");
		n=sc.nextInt();
		x=new char[n+1];	
		
	}
	void retsol(char[] x){
		for(int i=1;i<=n;i++)
		     System.out.print(x[i]);
		System.out.println();      
	}
	
	void back(){
		dif=0;
		back(1);
	}
	void back(int k){
		if(k==n+1)
		    retsol(x);
		else{
		    x[k]='('; 
        	dif++;
			if (dif<= n-k) 
				back(k+1);
			dif--;
			x[k]=')'; 
        	dif--;
			if (dif>= 0) 
				back(k+1);
			dif++;
		}

	}
	

	public static void main(String arg[]){
		Paranteze p=new Paranteze();
		p.citire();
		p.back();
	}
}