const express = require('express');
const cors = require('cors')
const app = express();

app.use(cors());

app.get('/configura', (req, res) => {
    console.log('Servidor recebeu msg do cliente');
    res.end();
});

app.get('/events', (req, res) => {
    res.setHeader('Content-Type', 'text/event-stream');
    res.setHeader('Cache-Control', 'no-cache');
    res.setHeader('Connection', 'keep-alive');

    setInterval(() => {
        res.write(`data: Mensagem do servidor em ${new Date().toLocaleTimeString()}\n\n`);
    }, 2000);
});

app.listen(3000, () => console.log('Servidor rodando na porta 3000'));