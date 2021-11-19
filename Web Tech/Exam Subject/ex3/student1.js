window.onload=function(){
	//1
	var range=document.getElementById("rng");
	range.onchange=function(){
		document.body.style.fontSize=parseInt(this.value)+"px";
		if(this.value>=parseInt(this.min)+(this.max-this.min)/2)
			document.body.style.color="red";
		else
			document.body.style.color="black"
	}
	//2
	var grup=document.querySelectorAll("input[type=radio]");
	for(el of grup){
		el.name="r";
	}
	document.getElementById("btn").onclick=function(){
		for(el of grup)
			if(el.checked)
				this.innerHTML=el.nextSibling.nodeValue;
	}
	
}