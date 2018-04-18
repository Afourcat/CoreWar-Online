const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);
const path = require('path');
var bodyParser = require('body-parser');

app.use('/combat-template', express.static('views/template/'));
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
	lobby.emit('lobby-name', lobby_name);
	res.sendFile(__dirname + "/views/template/lobby.html")
});

app.post('/lobby/', function (req, res) {
	lobby_name = req.body.name;
	res.redirect('/lobby/');
});

server.listen(3000, function() {
	console.log("Listenning on port 3000");
});

var combat = io.of('/combat');

combat.on('connection', function(socket) {
	console.log('someone connected');
});
