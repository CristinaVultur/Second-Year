function helper(str,par){
	var person=prompt(str);
	var rez=par.replace("___",person);
	return rez;
}

function inlocuire(string){
	
	var s;
	s=helper("Cum va numiti, va rog?",string.innerHTML);
	s=helper("Imi puteti indica varsta dumneavoastra?",s);
	s=helper("Indicati felul de mancare preferat.",s);
	s=helper("Care este culoarea ochilor dumneavoastra?",s);
	s=helper("Dar culoarea parului?",s);
	s=helper("Precizati un obiect de mobilier pe care ati dori sa-l achizitionati in urmatoarea perioada.",s);
	string.innerHTML=s;
}
window.onload=function(){
	inlocuire(document.getElementById("para"));
}