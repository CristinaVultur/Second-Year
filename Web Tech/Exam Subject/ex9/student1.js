window.onload=function(){
	if(localStorage.getItem("numere"))
		document.body.lastChild.nodeValue=localStorage.getItem("numere");
	document.getElementById("salveaza").onclick=function(){
		localStorage.setItem("numere",document.body.lastChild.nodeValue);
	}
	document.getElementById("sterge").onclick=function(){
		localStorage.removeItem("numere");
		document.body.lastChild.nodeValue="";
	}
	
}