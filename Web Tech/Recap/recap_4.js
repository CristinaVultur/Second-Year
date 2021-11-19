window.onload=function(){
	var btn=document.createElement("button");
	document.body.appendChild(btn);
	btn.innerHTML="ok";
	btn.onclick=function(){
		var tag=document.getElementById("lista");
		var list=Array.prototype.slice.call(tag.children);
		var nou=document.createElement("ol");
		document.body.appendChild(nou);
		for(i=0;i<list.length;i++)
			if(i%2==0){
				nou.appendChild(list[i])
			}
		
		}
	}
