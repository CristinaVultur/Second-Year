window.onload=function(){
	var p=document.querySelectorAll("div+p");
	for(el of p){
		el.onclick=function(){
		this.innerHTML=this.previousElementSibling.querySelectorAll("li").length;
	}
	}
	
}