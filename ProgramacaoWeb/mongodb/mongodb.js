const {
    MongoClient
} = require('mongodb');

var db;
var alunos;

async function conecta()
{
    var client = new MongoClient('mongodb://127.0.0.1:27017/');
    await client.connect();
    db = await client.db("AULAS");
    alunos = await db.collection("alunos");
}
async function inserte(x)
{
    try {
        let a = await alunos.insertOne({_id:x, idade:32, sexo:'f', CPF:'908989821982',profissao:'programador c++'});
        console.log(a);
    } catch (e) {
        console.log (e);
    }
}
async function remove()
{
    try {
        let a = await alunos.deleteOne({idade:32});
        console.log(a);
    } catch (e) {
        console.log (e);
    }
}
async function consulta ()
{
    let a = await alunos.findOne( {idade:44} );
    
    console.log(a);
}
async function atualiza ()
{
    let a = await alunos.updateOne(
        {_id: "Felipe"},
        { $set: { idade: 45 } },
        { upsert: true }
      )
    console.log(a);
}
async function init()
{
    await conecta();
    console.log("Insere um registro")


  //  await inserte('Maria');
  //  await inserte('Pedro');
  //  await inserte('Paulo');
    
    await consulta();


    //await inserte();
    //console.log("Consulta para ver se foi inserido");
    //await consulta();
    ///console.log("Remove o registro");
    //await remove();
    //console.log("Consulta para ver se foi removido");
    //await consulta();*/
    //await atualiza();
}

init();
