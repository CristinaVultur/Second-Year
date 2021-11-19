const express = require('express');
var app = express();
const formidable = require('formidable');





// initializari socket.io
const http=require('http')
const socket = require('socket.io');
const server = new http.createServer(app);  
var  io= socket(server)
io = io.listen(server);//asculta pe acelasi port ca si serverul



io.on("connection", (socket) => {  
    console.log("Conectare!");
	//if(!conexiune_index)
	//	conexiune_index=socket
    socket.on('disconnect', () => {conexiune_index=null;console.log('Deconectare')});
});




// pentru folosirea ejs-ului 
app.set('view engine', 'ejs');

app.use(express.static(__dirname));
app.use('/css', express.static('css'));




app.post('/mesaj', function(req, res) {

	var form = new formidable.IncomingForm();
	form.parse(req, function(err, fields, files) {
		console.log("primit mesaj")
		//if(conexiune_index){
			io.sockets.emit('mesaj_nou', fields.nume, fields.culoare, fields.mesaj);
		//}
    res.send("ok");


    });
	
	
});






app.get('/', function(req, res) {

		res.render('html/index', {port:s_port});
	});

s_port=process.env.PORT || 5000
server.listen(s_port)

console.log('Serverul a pornit pe portul '+ s_port);