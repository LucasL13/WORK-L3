


var fifoJoueurs = [];
var listSalons = [];

var http = require('http');
var url = require('url');
var mysql = require('mysql');
var c = require('./const');

var connection = mysql.createConnection({
  host : '217.182.69.175',
  user : 'Vinspi',
  password : 'vinspi13',
  database : 'DropDaBomb',
});

connection.connect();

var server = http.createServer();
var io = require('socket.io').listen(server);

server.listen(8080);
console.log("server pret");

io.sockets.on("connection", function(socket){
    socket.on("CREATE_ACCOUNT_CHECK", function(obj){check_account(obj, socket);});
    socket.on("CREATE_ACCOUNT_SEND", function(obj){create_account(obj, socket);});
});


function check_account(obj, sock){
        console.log(obj.mdp.length + " " + c.MIN_SIZE_PASSWORD);

        if(obj.mdp.length < c.MIN_SIZE_PASSWORD){
            return c.ERR_MDP;
        }

        var r = c.CREATE_ACCOUNT_FAILED_PSEUDO;

        var req = "SELECT Pseudo, mailCompte FROM CompteJoueur WHERE (Pseudo LIKE "+connection.escape(obj.pseudo)+" OR " +
                "mailCompte LIKE " +connection.escape(obj.email) +");";

        console.log(req);

        connection.query(req, function(err, rows, fields){
            if (err) throw err;
            if(rows.length != 0){
                sock.emit("CREATE_ACCOUNT_CHECK_FAIL_ALREADYEXIST", 0);
            }
            else{
                sock.emit("CREATE_ACCOUNT_CHECK_SUCCESS", 0);
            }
        });
}

function create_account(obj, sock){

            console.log("Jai recu final create : " + JSON.stringify(obj));
        
                var queryInsertion = [];


        //         connection.query("INSERT INTO CompteJoueur (Pseudo, mailCompte, mdpCompte, nomGuilde, id_Division) " +
        //                     "VALUES ("+connection.escape(obj.pseudo)+","+connection.escape(obj.email)+","+connection.escape(obj.mdp)+",NULL, NULL);");
        //         connection.query("INSERT INTO Deck(id_Deck,estActif) VALUES ("+connection.escape(obj.pseudo+'0')+",0);");
        //         connection.query("INSERT INTO Deck(id_Deck,estActif) VALUES ("+connection.escape(obj.pseudo+'1')+",1);");
        //         connection.query("INSERT INTO Deck(id_Deck,estActif) VALUES ("+connection.escape(obj.pseudo+'2')+",0);");   

        //         for(var i=0; i<8; i++){
        //             connection.query("INSERT INTO JoueurCarteDeck(qteCarteDeck, id_Deck, Pseudo, id_Carte) VALUES (1, "+connection.escape(obj.pseudo+'0')+","+connection.escape(obj.pseudo)+","+i+");");
        //             connection.query("INSERT INTO JoueurCarteDeck(qteCarteDeck, id_Deck, Pseudo, id_Carte) VALUES (1, "+connection.escape(obj.pseudo+'1')+","+connection.escape(obj.pseudo)+","+i+");");
        //             connection.query("INSERT INTO JoueurCarteDeck(qteCarteDeck, id_Deck, Pseudo, id_Carte) VALUES (1, "+connection.escape(obj.pseudo+'2')+","+connection.escape(obj.pseudo)+","+i+");");
        //        }   

        //         connection.query("INSERT INTO posséderIconeJoueur(Pseudo,id_IconeJoueur) VALUES ("+connection.escape(obj.pseudo)+",0)");

        //         connection.query("INSERT INTO posséderSkinMap(Pseudo,id_SkinMap) VALUES ("+connection.escape(obj.pseudo)+",0)");

        //         connection.query("INSERT INTO posséderSkinCartonCarte(Pseudo,id_SkinCartonCarte) VALUES ("+connection.escape(obj.pseudo)+",0)");

        //         sock.emit("CREATE_ACCOUNT_SUCCESS", 0);
        //     }
        // });

}