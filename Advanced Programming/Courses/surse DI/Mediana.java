import java.util.*;
import java.io.*;

public class Mediana {

    double a[],b[];
    int n;
    
    
    void citire(){
    		Scanner sc;
    		try{
    			sc=new Scanner(new File("mediana.txt"));
    		}	
    		catch(FileNotFoundException fnf){
    			sc=new Scanner(System.in);
    		}
    		sc.useLocale(Locale.ENGLISH);
    		n=sc.nextInt();
    		a=new double[n];
    		b=new double[n];
    		for(int i=0;i<n;i++)
    			a[i]=sc.nextDouble();
    		for(int i=0;i<n;i++)
    			b[i]=sc.nextDouble();	
    }
    
    double calculMediana(int pa, int ua,int pb, int ub){
	    	int n=ua-pa+1;
	    	if(n<=2){
	    		System.out.println(pa+"-"+ua+">:   "+pb+"-"+ub+">:calcul direct");//pentru a vedea subvectorii ramasi
	    	 	return (Math.max(a[pa],b[pb])+Math.min(a[ua],b[ub]))/2.0;
	    	}		
	    	double m1=mediana(a,pa,ua);//mediana lui a[pa..ua]
	    	double m2=mediana(b,pb,ub);//mediana lui b[pb..ub]
	    	System.out.println(pa+"-"+ua+">:"+m1+" "+pb+"-"+ub+">:"+m2);
	    	if(m1==m2)
	    		return m1;
	    	if (m1>m2)
	    		return calculMediana(pa, pa+n/2, pb+(n-1)/2,ub);//prima jumatate din a[pa..ua], a doua din b[pb..ub]
	    	else
	    		return calculMediana(pa+(n-1)/2, ua, pb,pb+n/2);
    }
    double calculMediana(){
    		return calculMediana(0,n-1,0,n-1);
    }
    
    double mediana(double[] v, int pv, int uv){//calculul direct al medianei unui vector sortat
	    	int n=uv-pv+1;
	    	int m=(uv+pv)/2;
	    	if (n%2==0) //par-> media elementelor din mijloc
	    		return(v[m]+v[m+1])/2.0;
	    	else //impar-> chair elementul din mijloc
	    		return v[m];	
    }
    
    public static void main(String ar[]){
    		Mediana ob=new Mediana();
    		ob.citire();
    	   	System.out.println("mediana= "+ob.calculMediana());
    }
    
    
}