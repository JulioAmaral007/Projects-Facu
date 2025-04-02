var socket;

function conectaServidorSockets (url)
{
    socket = new ReconnectingWebSocket(url);  // <--- AQUI temos a biblioteca

    socket.onopen = function(evt) {
         console.log('app cliente se conectou com sucesso');

       
    }
    socket.onclose = function(evt) {
  
    }
    socket.onmessage = function(recebido) {
        console.log('Cliente recebeu:'+recebido.data);
        let msg = (recebido.data);

        switch (msg.tipo){
            case 'texto':
                document.getElementById('msg').value+=msg.valor+"\n";

            break;
            case 'listaConectados':
                console.log(msg.valor);
                document.getElementById('users').value+=msg.valor+"\n";

            break;
        }
       
    }

}
function fazLogin()
{
    console.log('fez login')
    let nome = document.getElementById('nome').value;
    let M = {tipo:'login', valor:nome};
    socket.send( JSON.stringify(M) );    
}
function envia()
{

    let  conteudo = document.getElementById('mensagem').value;
    document.getElementById('mensagem').value='';

    let m = {tipo:'texto', valor:conteudo}

    socket.send(JSON.stringify(m));


}

document.addEventListener("DOMContentLoaded", (event) => {
    console.log("Aplicacao do cliente comeca a rodar...");

    
    conectaServidorSockets('ws://localhost:10000');



  });