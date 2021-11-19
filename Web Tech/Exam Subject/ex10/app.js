const express=require('express');
app=express();
app.use('/ex10.html',express.urlencoded({extended:false}));

persoane=[
	{
		nume:"Georgescu",
		prenume:"Ion"
	},
	{
		nume:"Alexandrescu",
		prenume:"Gogu"
	},	
	{
		nume:"Andreescu",
		prenume:"Andreea"
	},
	{
		nume:"Georgescu",
		prenume:"Monica"
	},
	{
		nume:"Andreescu",
		prenume:"Costel"
	},
	{
		nume:"Costache",
		prenume:"Costel"
	},
	{
		nume:"Alexandrescu",
		prenume:"Monica"
	},
]
app.get("/ex10.html", function(req,res){

	res.sendFile(__dirname+"/ex10.html");
});

//Completati 


app.listen(8080);
console.log("Serverul a pornit");
