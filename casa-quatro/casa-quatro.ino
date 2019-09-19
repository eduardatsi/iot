#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//wi-fi e autenticação no Firebase
#define FIREBASE_HOST "casa-29317.firebaseio.com"
#define FIREBASE_AUTH "FhXqsaE6XWVxHLIbtPfc0EmFeTrWh382yMDPrhS7"
#define WIFI_SSID "ifdoce"  //"Eduarda"
#define WIFI_PASSWORD "10tifsul" //"02051995"

#define LED_AZUL 2
#define LED_VERMELHO 16


void autenticarFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void conectarWiFi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("\nconnecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  autenticarFirebase();
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  conectarWiFi();
  
}

void setLamp(boolean state) {
  Serial.println(state);
  if(state){
    digitalWrite(LED_VERMELHO, LOW);
    Serial.println("Lâmpada LIGADA - LED VERMELHO");
  }
  else{
    digitalWrite(LED_VERMELHO, HIGH);
    Serial.println("Lâmpada DESLIGADA - LED VERMELHO");
  }
}

void setAirConditioner(boolean state) {
  if(state){
    digitalWrite(LED_AZUL, LOW);
    Serial.println("Ar Condicionado LIGADO - LED AZUL");
  }
    
  else{ 
    digitalWrite(LED_AZUL, HIGH);
    Serial.println("Ar Condicionado DESLIGADO - LED AZUL");
  }
    
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    if(Firebase.success()) {
      FirebaseObject casa = Firebase.get("casa");

      // ÁREA DE SERVIÇO
      if(casa.getBool("/areaDeServico/lampada"))
        setLamp(true);
      else
        setLamp(false);

      //CLOSET
      if(casa.getBool("/closet/lampada"))
        setLamp(true);
      else
        setLamp(false);

      //COZINHA
      if(casa.getBool("/cozinha/lampada"))
        setLamp(true);
      else
        setLamp(false);

      //GARAGEM
      if(casa.getBool("/garagem/lampada"))
        setLamp(true);
      else
        setLamp(false);

      //PISCINA
      if(casa.getBool("/piscina/lampada"))
        setLamp(true);
      else
        setLamp(false);

      //QUARTO 1
      if(casa.getBool("/quarto1/lampada"))
        setLamp(true);
      else
        setLamp(false);
      if(casa.getBool("/quarto1/arCondicionado"))
        setAirConditioner(true)
      else
        setAirConditioner(false)

      //QUARTO 2
      if(casa.getBool("/quarto2/lampada"))
        setLamp(true);
      else
        setLamp(false);
      if(casa.getBool("/quarto2/arCondicionado"))
        setAirConditioner(true)
      else
        setAirConditioner(false)

      //SALA DE ESTAR
      if(casa.getBool("/salaDeEstar/lampada"))
        setLamp(true);
      else
        setLamp(false);

      //SALA DE JANTAR
      if(casa.getBool("/salaDeJantar/lampada"))
        setLamp(true);
      else
        setLamp(false);
      
      //SUITE
      if(casa.getBool("/suite/lampada"))
        setLamp(true);
      else
        setLamp(false);
      if(casa.getBool("/suite/arCondicionado"))
        setAirConditioner(true)
      else
        setAirConditioner(false)

      //VARANDA
      if(casa.getBool("/varanda/lampada"))
        setLamp(true);
      else
        setLamp(false);
      
      //WC
      if(casa.getBool("/wc/lampada"))
        setLamp(true);
      else
        setLamp(false);
      
      //WC2
      if(casa.getBool("/wc2/lampada"))
        setLamp(true);
      else
        setLamp(false);
      
    }
    else {
    Serial.println("Erro na autenticão com o Firebase");
    }
  }else{
    conectarWiFi();
  }
  
  delay(500);

}