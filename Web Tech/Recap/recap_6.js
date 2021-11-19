function init(){
	var newItem=document.createElement("p");
	newItem.innerHTML=new Date();
	document.body.insertBefore(newItem,document.body.firstChild);
}

window.onload=function(){
	init();/*2*/
	//3
	var table=document.createElement("table");
	table.id="tabel";
	var tbody=document.createElement("tbody");	
	table.appendChild(tbody);
	for(let i=0;i<4;i++){
		let row=document.createElement("tr");// Create an empty <tr> element and add it to the 1st position of the table:
		tbody.appendChild(row);
		for(let j=0;j<6;j++){
			let cell=document.createElement("td");//Insert new cells (<td> elements) at the 1st and 2nd position of the "new" <tr> element:
			row.appendChild(cell);
		}
	}
	var div=document.getElementById("vorbe");
	var parinte=div.parentNode;
	parinte.insertBefore(table,div.nextElementSibling);//insereaza imediat dupa divul cu id vorbe
	//4
	table.style.border="1px solid black"
	table.style.borderCollapse="collapse";
	table.style.padding="10px"
	var tr=table.querySelectorAll("tr");
	for(t of tr){
		t.style.border="1px solid black"
		t.style.borderCollapse="collapse";
		t.style.padding="10px"
	}
	var td=table.querySelectorAll("td");
		for(t of td){
		t.style.border="1px solid black"
		t.style.borderCollapse="collapse";
		t.style.padding="10px";
	}
	//5
	document.getElementById("atribuie_clase").onclick=function(){
		var list=document.getElementById("ac");
		vector=Array.prototype.slice.call(list.children);
		for(el of vector){
			if(el.innerHTML.endsWith("ac"))
				el.className="ok";
			else
				el.className="notok";
		}
		//6
		for(i=0;i<vector.length;i++){
			if(i%2==0)
				vector[i].classList.add("impar");
			else
				vector[i].classList.add("par");
		}
		//7
		var ok=document.getElementsByClassName("ok");
		var x=document.createElement("span");
		let t=document.createTextNode("-> bun");//!!atentie la creare el dinamice!! niciodata in for!!!!
		x.appendChild(t);
		for(el of ok){				
				el.onmouseover=function(){	
					this.appendChild(x);
				}
		}
		for(el of ok){
			el.onmouseout=function(){
			this.removeChild(x);
			delete x;
				
		}
		}
		var notok=document.getElementsByClassName("notok");
		var nx=document.createElement("span");
		let nt=document.createTextNode("->Da' tu ce cauti aici");
		nx.appendChild(nt);
		for(el of notok){				
				el.onmouseover=function(){	
					this.appendChild(nx);
				}
		}
		for(el of notok){
			el.onmouseout=function(){
			this.removeChild(nx);
			delete nx;
			}
		}
		//9
		document.onkeydown=function(e){
			if(e.key=='i'){
			var impar=document.getElementsByClassName("impar");
			for(el of impar)
				el.style.color=el.style.color="rgb("+Math.floor((Math.random() * 255) + 1)+", "+Math.floor((Math.random() * 255) + 1)+", "+Math.floor((Math.random() * 255) + 1)+")";
			}
			if(e.key=="p"){
				var par=document.getElementsByClassName("par");
				for(el of par)
				el.style.color="rgb("+Math.floor((Math.random() * 255) + 1)+", "+Math.floor((Math.random() * 255) + 1)+", "+Math.floor((Math.random() * 255) + 1)+")";
			
			}
		}
		document.onkeyup=function(e){
			if(e.key=="i"){
				var impar=document.getElementsByClassName("impar");
				for(el of impar)
					el.style.color="black"
			}
			if(e.key=="p"){
				var par=document.getElementsByClassName("par");
				for(el of par)
					el.style.color="black"
			}
		}
	}
		
	
	document.getElementById("sterge_clase").onclick=function(){
		var list=document.getElementById("ac");
		vector=list.querySelectorAll("li");
		for(el of vector){
			el.classList.remove("ok");
			el.classList.remove("notok");
		}
	}
	//8
	
	//10
	var ul=document.getElementById("ac");
	var ol=document.createElement("ol");
	var par=ul.parentElement;
	var list=ul.children;
	for(let i=0;i<list.length;i++){
		ol.appendChild(list[i]);
		i--;
	}
	ol.className=ul.className;
	ol.id=ul.id;
	par.replaceChild(ol,ul);
	delete ul;
	
	//11
	var test=document.getElementById("test");
	var p=test.previousElementSibling;
	var elem=p.childNodes;
	var nri=0, nrb=0,nr=0;
	for(el of elem){
		if(el.nodeType==1){
			var s=el.innerHTML;
			if(el.tagName=="B") nrb=nrb+parseInt(s.length);
			else nri=nri+parseInt(s.length);
		}
		else{
			nr=nr+parseInt(el.nodeValue.length);
		}
	}
	var txt=document.createTextNode("fara:"+nr+" i:"+nri+" b"+nrb);
	test.appendChild(txt);
		
		document.getElementById("ac").onmouseenter=function(e){
		var dv=document.createElement("div");
		var ok=document.getElementsByClassName("ok");
		var notok=document.getElementsByClassName("notok");
		var t=document.createTextNode("ok:"+ok.length+" notok:"+notok.length);
		dv.appendChild(t);		
		this.appendChild(dv);	
		dv.style.position="absolute";
		this.onmousemove=function(e){
		dv.style.top=e.clientY-3+'px';
		dv.style.left=e.clientX-3+'px';
		this.onmouseleave=function(){
		var x=this.lastChild;
		this.removeChild(x);
		delete x;
	}
	}
		
	}
	document.querySelector("p.cuvinte").onclick=function(){
		var list=document.createElement("ul");
		document.body.appendChild(list);
		for(el of this.children){
			if(el.nodeType==1){
				if(el.tagName=="B"){
					var b=document.createElement("b");
					b.innerHTML=el.innerHTML+" ";
					list.appendChild(b);
				}
				else{
					var i=document.createElement("i");
					i.innerHTML=el.innerHTML+" ";
					list.appendChild(i);
				}
			}
			
		}
		list.ondblclick=function(){
			var elem=Array.prototype.slice.call(this.children);
			elem.sort();
			elem.reverse();
			for(el of elem)
				this.appendChild(el);
		}
	}
	document.getElementById("numere").onchange=function(){
		 var tabel=document.getElementById("tabel");
		 var row=tabel.getElementsByTagName("tr");
		 var coll=tabel.getElementsByTagName("td");
		 var value=this.value;
		 for(r of row)
			 for(c of coll){
				 c.innerHTML=Math.floor(Math.random() * value) + parseInt(this.min);
			 }
	
	}
	var int=setInterval(function(){
		var x=document.createElement("img");
		x.setAttribute("src", "paianjen.png");
		x.style.float="right";
		document.body.appendChild(x);
		time=setTimeout(function(){
			document.body.removeChild(x);
			delete x;
			console.log("A disparut paianjenul");
		},5000)
	},60000);
	
	
}