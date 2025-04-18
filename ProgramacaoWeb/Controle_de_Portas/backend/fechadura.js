if (process.argv.length != 4) {
  console.log("forma de usar:");
  console.log("node fechadura ID_FECHADURA SENHA_FECHADURA");
  process.exit();
}

let id = process.argv[2];
let passwd = process.argv[3];

var WebSocketClient = require("websocket").client;

var client = new WebSocketClient();

client.on("connectFailed", function (error) {
  console.log("Connect Error: " + error.toString());
});

client.on("connect", function (connection) {
  console.log("Fechadura conectada");

  connection.send(JSON.stringify({ tipo: "loginFechadura", id: id, passwd: passwd }));
  connection.on("error", function (error) {
    console.log("Erro: " + error.toString());
  });
  connection.on("close", function () {
    console.log("Desconectou");
  });
  connection.on("message", function (message) {
    let dados = JSON.parse(message.utf8Data);

    switch (dados.tipo) {
      case "abre":
        // aciona solenoide
        console.log("Abre a fechadura");
        break;
      case "falha":
        // aciona buzina
        console.log("Falha ao abrir a fechadura");
        break;
    }
    console.log("Fechadura abre a porta ");
  });
});

client.connect("ws://localhost:4000/");
