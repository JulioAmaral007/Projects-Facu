const WebSocket = require('ws');
var listaClientes = [] // 



const wss = new WebSocket.Server({ port: 10000 },function (){
	console.log('SERVIDOR WEBSOCKETS na porta 10000');
});


function broadcast(message) {
    listaClientes.forEach((Alvo) => {
        if (Alvo.readyState === WebSocket.OPEN) {
            Alvo.send(message);
        }
    });
}

function pegaLista()
{
    let v=[];
    listaClientes.forEach((Alvo) => {
        if (Alvo.ID ) v.push(Alvo.ID);
    });
    return v;

}
wss.on('connection', function connection(ws) {
    console.log('Cliente novo se conectou...');
    // Envia um 'ola' para o cliente
    listaClientes.push(ws);
    ws.send('Cliente novo conectou');


    ws.on('message', function MSG (message) {
        console.log('servidor recebeu msg')
        message = JSON.parse(message);
        let M;
        switch (message.tipo)
        {
            case 'login':
                console.log('Usuario trocou seu nick para ',message.valor);
                ws.ID = message.valor;

                let lista = pegaLista();
                 M = {tipo:'listaConectados',valor:lista};

                 broadcast(JSON.stringify(M));
                break;
            case 'texto':
                console.log('Servidor recebeu:'+message.valor);
                 M = {tipo:"texto",valor:'>>>'+ws.ID+":"+message.valor}
                broadcast(JSON.stringify(M));
                break;
            
        }
        
    });
    
    ws.on('close',function (x) {
        listaClientes = listaClientes.filter(function (valor) {

            return valor !== ws;
        });
        let lista = pegaLista();
        M = {tipo:'listaConectados',valor:lista};

        broadcast(JSON.stringify(M));
    });

});

