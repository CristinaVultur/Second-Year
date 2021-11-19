window.onload=function(){
	setTimeout(function(){
		for(let i=0;i<10;i++){
		var btn=document.createElement("button");
		document.body.appendChild(btn);
		btn.innerHTML="0"
		btn.active=0;
		
		btn.onclick=function(){
			if(this.active==0){
			this.active=setInterval(function(b){
				b.innerHTML=parseInt(b.innerHTML)+1;
			},1000,this);
			}
			else{
				clearInterval(this.active);
				this.active=0;
			}
		}
	}
		}
	,1500);
	
}