window.onkeydown=function(e){
	var dvs=document.getElementsByClassName("d1");
	if (e.key=='q') pas=1;
	if (e.key=='w') pas=-1;
	for(dv of dvs){
		inalt=parseInt(getComputedStyle(dv).height);
		inalt=Math.max(inalt+pas,0);
		dv.style.height=inalt+"px";
	}
}