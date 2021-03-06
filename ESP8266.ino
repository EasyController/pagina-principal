// librerias para la LCD


//librerias modulo WiFi Access Point

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int PIRU = 5; //D1
int PIRD = 4; //D2
int Contador = 0;
int LEDV = 14;
int LEDR = 12;
int Buzz = 13;

//Definir las credenciales de acceso

const char* ssid = "Vasquez";
const char* password = "carlosycesar2019";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  pinMode(PIRU,INPUT);
  pinMode(PIRD,INPUT);
  pinMode(LEDV,OUTPUT);
  pinMode(LEDR,OUTPUT);
  pinMode(Buzz,OUTPUT);
  digitalWrite(LEDV,LOW);
  digitalWrite(LEDR,LOW);
  digitalWrite(Buzz,LOW);

  //configuramos el modo Access Point
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Conectando");

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }   
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);
  server.begin();
}

void loop() {
  Aforo();
  server.handleClient();
  }
  
void handleRoot(){
  String html ="<!DOCTYPE html> <html lang=\"es\"> <head> <meta charset=\"UTF-8\"> <meta http-equiv=\"refresh\" content=\"2\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>EasyController</title> <style> *{ margin:0; padding: 0; box-sizing: border-box; } body{ font-family: 'Courier New', Courier, monospace; } .contenedor{ padding: 60px 0; width: 90%; max-width: 1000px; margin: auto; overflow: hidden; } .titulo{ color: #642a73; font-size: 30px; text-align: center; margin-bottom: 60px; } /*Header*/ header{ width: 100%; height: 600px; background: #00416A; background: -webkit-linear-gradient(to right, hsla(200, 6%, 90%, 0.5), hsla(203, 100%, 21%, 0.637)), url(https://uploads-ssl.webflow.com/5ec994b5518a6ecd19d5d11c/5fc274ede4b22255ed774001_web-1012467_1920a.jpg); background: linear-gradient(to right, hsla(200, 6%, 90%, 0.5), hsla(203, 100%, 21%, 0.637)), url(https://uploads-ssl.webflow.com/5ec994b5518a6ecd19d5d11c/5fc274ede4b22255ed774001_web-1012467_1920a.jpg) ; background-size: cover; background-attachment: fixed; position: relative; } nav{ text-align: right; padding: 30px 50px 0 0; } nav > a{ color: white; font-weight: 300; text-decoration: none; margin-right: 10px; } nav > a:hover{ text-decoration: underline; } header .textos-header{ display: flex; height: 430px; width: 100%; align-items: center; justify-content: center; flex-direction: column; text-align: center; } .textos-header h1{ font-size: 50px; color: white; } .textos-header h2{ font-size: 20px; color: white; } .wave{ position: absolute; bottom: 0; width: 100%; } /*About us */ .contenedor-sobre-nosotros{ display: flex; justify-content: space-evenly; } .imagen-about-us{ width: 40%; } .sobre-nosotros .contenido-textos{ width: 40%; } .texto{ margin-top: 10px; margin-bottom: 10px; text-align: justify; } .imagen-control{ width: 60%; } .recuadro{ background-color: rgb(0, 0, 0); width: 150px; height: 50px; margin: auto; } .recuadro1{ background-color: rgb(255, 255, 255); width: 142px; height: 43px; margin-top: -46px; margin-left: 41px; } .Personas{ font-size: 30px; margin-left: 105px; margin-top: -37px; } .contenido-textos1{ margin-top: 80px; } </style> </head> <body> <header> <nav> <a href=\"#\">Acerca de Nosotros</a> <a href=\"#\">Control de Aforo</a> </nav> <section class=\"textos-header\"> <h1>EasyController</h1> <h2>Tan seguro como en casa</h2> </section> <div class=\"wave\" style=\"height: 150px; overflow: hidden;\" ><svg viewBox=\"0 0 500 150\" preserveAspectRatio=\"none\" style=\"height: 100%; width: 100%;\"><path d=\"M0.00,49.99 C149.77,150.00 352.23,-49.99 499.26,49.99 L499.26,150.00 L0.00,150.00 Z\" style=\"stroke: none; fill: rgb(255, 255, 255);\"></path></svg></div> </header> <main> <section class=\"contenedor sobre-nosotros\"> <h2 class=\"titulo\">Acerca de Nosotros</h2> <div class=\"contenedor-sobre-nosotros\"> <img src=\"https://i.pinimg.com/originals/50/67/c3/5067c39eb4fcf6b4852e34a207b7bcfe.png\" alt=\"\" class=\"imagen-about-us\"> <div class=\"contenido-textos\"> <h3>Misi??n</h3> <p class=\"texto\">Somos una empresa que desea satisfacer las necesidades de los restaurantes de mediana y alta categor??a, a trav??s de un sistema tecnol??gico integral de conteo de aforo y men?? digital, con el fin de incrementar las ventas y contribuir con el cumplimiento de est??ndares de bioseguridad posicionando la imagen de los restaurantes.</p> <h3>Visi??n</h3> <p class=\"texto\">Ser un referente a nivel nacional en la venta de nuestro producto integral de conteo de aforo autom??tico y la instalaci??n de un men?? digital personalizado en los restaurantes de mediana y alta categor??a, que logre generar un plus de manera eficiente e innovadora en sus negocios.</p> </div> </div> </section> <section class=\"ControlAforo\"> <div class=\"contenedor\"> <h2 class=\"titulo\">Control de Aforo</h2> <div class=\"contenedor-sobre-nosotros\"> <img src=\"https://gunnebointegratedsecurity.es/wp-content/uploads/2020/04/counter-supervisor-info-pass.png\" alt=\"\" class=\"imagen-control\"> <div class=\"contenido-textos1\"> <h3>Cantidad de Personas</h3> <div class=\"recuadro\"></div> <div class=\"recuadro1\"></div> <p class=\"Personas\">"+String(Contador)+"</p> </div> </div> </div> </section> </main> </body> </html>";
  server.send(200,"text/html",html);
  }

void Aforo(){
  int Up = digitalRead(PIRU);
  int Down = digitalRead(PIRD);
  digitalWrite(LEDV,LOW);
  digitalWrite(LEDR,LOW);
  digitalWrite(Buzz,LOW);
  if (Up == 1 and Down == 1){
    Contador = Contador; 
    }
  if (Up == 1 and Down == 0 and Contador<5 ){
    Contador++;
    digitalWrite(LEDV,HIGH);
    }
  if (Down == 1 and Up == 0 and Contador>0){
    Contador--;
    digitalWrite(LEDR,HIGH);
    }
  if (Contador == 5) {
    digitalWrite(Buzz,HIGH);
    }  
  Serial.println(Contador);
  delay(4000);
  }
