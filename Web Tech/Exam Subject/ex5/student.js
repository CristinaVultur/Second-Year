window.onclick=function(e){
	var div=document.createElement("div");
	div.className="animat";
	document.body.appendChild(div);
	div.style.position="absolute";	
	div.style.top=e.clientY-parseInt(getComputedStyle(div).height)/2+"px";
	div.style.left=e.clientX-parseInt(getComputedStyle(div).width)/2+"px";
	if(Math.random()<0.5)
		div.style.animationName="miscare1";
	else
		div.style.animationName="miscare2";
	div.onclick=function(e){e.stopPropagation();}
}