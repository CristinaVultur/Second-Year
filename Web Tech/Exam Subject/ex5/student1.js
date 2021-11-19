window.onclick=function(e){
	var dv=document.createElement("div");
	dv.style.position="absolute";
	document.body.appendChild(dv);
	stil=getComputedStyle(dv);
	dv.style.top=e.clientY-parseInt(stil.height)/2+"px";
	dv.style.left=e.clientX-parseInt(stil.width)/2+"px";
	dv.style.animationName=Math.random()<0.5?"miscare1":"miscare2";
	dv.className="animat";
	dv.onclick=function(e){e.stopPropagation()}
}