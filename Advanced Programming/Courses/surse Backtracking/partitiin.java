import java.util.Scanner;
class Partitie{
	int n,x[],s;
	Partitie(int n1){
		n=n1;
		x=new int[n+1];	
	}
	void retsol(int[] x,int k){
		for(int i=1;i<=k;i++)
		    System.out.print(x[i]+" ");
		System.out.println();        
	}
	void back(){
		int k=1,s=0;
		int x[]=new int[n+1];
		x[1]=0;
		while(k>=1){
			if(x[k]<n){
				x[k]++;
				s++;
				if(s<=n){//cont
					if(s==n){//dc este sol
						retsol(x,k);
						s-=x[k];
						//x[k]=0;//revenire
						k--;
					}
					else{
						k++;
						x[k]=x[k-1]-1;
						s+=x[k];
					}
				}
				else{
					s=s-x[k];
					//x[k]=0;
					k--;
				}
				
				
			}
		}
	}
	
	
	void backrec(){
		x=new int[n+1];	
		x[0]=1;
		s=0;
		backrec(1);
	}
	void backrec(int k){
		if(s==n){//este solutie
			         retsol(x,k-1);
			         return;
			    }
	   for(int i=x[k-1];i<=n;i++){
			x[k]=i;
			if(s+x[k]<=n){//cont
			     	s+=x[k];
			    	backrec(k+1);
			    	s-=x[k];
			    }
			else
			 	return;   
		}   
	}
	
	
	public static void main(String arg[]){
		Scanner sc=new Scanner(System.in);
		System.out.print("n=");
		int n=sc.nextInt();
		Partitie p=new Partitie(n);
		System.out.println("Varianta nerecursiva");
		p.back();
		System.out.println("Varianta recursiva");
		
		p.backrec();
	}
}