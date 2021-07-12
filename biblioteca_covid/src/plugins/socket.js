let host = null;
let base = null;

var currentPage = window.location.pathname.replace(host + base, "");
//var socket = io.connect('http://localhost:4000');

export function recievedDatiConfig() {
    console.log("RECIEVED DATI CONFIG");
    socket.emit('client');

    socket.on('configuration', function (data) {
        console.log("CONFIGURATION", data);
    });
}