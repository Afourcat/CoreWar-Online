const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);
const path = require('path');
const fs = require('fs');
var bodyParser = require('body-parser');

app.use(express.static(path.join(__dirname, '/views/static')));
app.use(bodyParser.urlencoded({ extended: true })); 
var lobby_name = "Default";


for (let nb = 0; nb < 4; ++nb) {
	fs.unlink('warrior' + nb, (err) => {
		if (err) console.log("warrior " + nb + " already deleted :)");
	});
}

app.get('/', function(req, res) {
	res.sendFile(__dirname + "/views/template/index.html");
});

app.get('/combat/', function(req, res) {
	res.sendFile(__dirname + "/views/template/combat.html");
});

var lobby = io.of('/lobby');

app.get('/lobby/', function(req, res) {
	res.sendFile(__dirname + "/views/template/lobby.html")
});

lobby.on('connection', function(socket) {
	let i = 0;

	socket.emit('lobby-name', lobby_name);
	
	socket.on('input-file', function (data) {
		let nb = i++ % 4;

		fs.open("warrior" + nb, 'w', (err, fd) => {
			if (err) throw err;
			fs.writeFile("warrior" + nb, data, err => {
				if (err) throw err;
			});
		});

	});
});

app.post('/', function(req, res) {
	console.log("MABITE");

});

app.post('/warrior', function(req, res) {
	var warrior0 = req.body['warrior0'];
	var warrior1 = req.body['warrior1'];
	var warrior2 = req.body['warrior2'];
	var warrior3 = req.body['warrior3'];
	console.log("POPO" , warrior0);
});

app.post('/lobby/', function (req, res) {
	console.log("suce");
	lobby_name = req.body['suce'];
	res.redirect('/lobby/');
});

var combat = io.of('/combat');

combat.on('connection', function(socket) {
	console.log('socket ' + socket.id + ' connected on /combat');
});

server.listen(3000, function() {
	console.log("Listenning on port 3000");
});
