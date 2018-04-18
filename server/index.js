const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);

app.use('/combat-template', express.static('views/template/'));

app.get('/', function(req, res) {
	res.send("Hello");
});

app.get('/combat/', function(req, res) {
	res.sendFile(__dirname + "/views/template/index.html");
});

server.listen(3000, function() {
	console.log("Listenning on port 3000");
});

var combat = io.of('/combat');

combat.on('connection', function(socket) {
	console.log('someone connected');
});

