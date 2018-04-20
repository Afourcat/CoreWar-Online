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

//Root logic

app.get('/', function(req, res) {
	res.sendFile(__dirname + "/views/template/index.html");
});

//Combat logic ----

var image = io.of('/image');
var combat = io.of('/combat');
var dataImage = undefined;

image.on('connection', function (socket) {
	socket.on('image', function(data) {
		dataImage = data;
	});
});

app.get('/combat/', function(req, res) {
	res.sendFile(__dirname + "/views/template/combat.html");
});

combat.on('connection', function(socket) {
	socket.emit('datas', dataImage);
});



//Lobby logic ----

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

app.post('/lobby/', function (req, res) {
	console.log("suce");
	lobby_name = req.body['suce'];
	res.redirect('/lobby/');
});


//Listener on port 3000
server.listen(3000, function() {
	console.log("Listenning on port 3000");
});
