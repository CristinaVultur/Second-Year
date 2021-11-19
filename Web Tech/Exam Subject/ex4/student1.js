window.onkeydown=function(e){
	if(e.key=="q") pas=1;
	if(e.key=="w") pas=-1;
	var div=document.getElementsByClassName("d1");
	for(d of div){
		stil=parseInt(getComputedStyle(d).height);
		d.style.height=Math.max(stil+pas,0)+"px";
	}
	
}