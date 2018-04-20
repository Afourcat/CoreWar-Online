const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);
const path = require('path');
var bodyParser = require('body-parser');

app.use(express.static(path.join(__dirname, '/views/static')));
app.use(bodyParser.urlencoded({ extended: true })); 
var lobby_name = "Default";

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
	socket.emit('lobby-name', lobby_name);
});

lobby.on('input-file', function (data) {
	console.log('SALUT', data);
});

app.post('/warrior', function(req, res) {
	var warrior0 = req.body['warrior0'];
	var warrior1 = req.body['warrior1'];
	var warrior2 = req.body['warrior2'];
	var warrior3 = req.body['warrior3'];
	console.log("POPO" , warrior0);
});

app.post('/lobby/', function (req, res) {
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