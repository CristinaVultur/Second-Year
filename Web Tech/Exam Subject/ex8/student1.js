window.onload=function(){
	//1
	var clase=document.querySelectorAll(".a.b");
	for(cl of clase){
		cl.onclick=function(){
		if(!this.classList.contains("c")&&!this.classList.contains("d")){
			this.classList.add("zzz");
		}
		}
	}
	//2
	but=document.getElementById("clase_multe");
	but.onclick=function(){
		for(let i=0;i<this.classList.length;i++){
			if(this.classList.item(i)[this.classList.item(i).length-1]%2==0){
				this.classList.remove(this.classList.item(i));
				i--;
			}
		}
	}
}