var express = require('express');/*include modulul express
memorand in variabila express obiectul asociat modulului(exportat de modul)*/
var app = express();

// pentru folosirea ejs-ului 
app.set('view engine', 'ejs');


// cand se face o cerere get catre pagina de index 
app.get('/', function(req, res) {
	/*afiseaza(render) pagina folosind ejs (deoarece este setat ca view engine) */
    res.render('html/index');
});

 
app.get('/stelute', function(req, res) {
    res.render('html/stelute');
});
app.get('/prajituri', function(req, res) {
    res.render('html/prajituri');
});
app.use('/css', express.static('css'));


app.listen(8080);
console.log('Aplicatia se va deschide pe portul 8080.');