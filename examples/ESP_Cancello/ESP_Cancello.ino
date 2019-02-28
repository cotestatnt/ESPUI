#include <ESPUI.h>
#include <Time.h>

// Variabili per aggiornare la data corrente con server NTP
time_t now;
struct tm lt;

const char *ssid = "PuccosNET";
const char *password = "Tole76tnt";
unsigned long updateTime = 0;
const int outCancello = D4;
const int outBasculante = D5;

// Variabili per memorizzare l'id (HTML) del componente creato dinamicamente dalla libreria
// In questo modo possiamo accedere rapidamente alle proprietà per aggiornarlo
int idCancello, idBasculante = 0;

// handler per gestire gli eventi di connessione/disconnessione al wifi
WiFiEventHandler connectedHandler;
WiFiEventHandler disconnectedHandler;

void onConnection(const WiFiEventStationModeConnected& evt) {   
  // appena ho una connessione valida, sincronicco la data attuale con un server NTP
  #define TIMEZONE 1       // (UTC+) Standard TimeZone in hours  
  configTime(TIMEZONE * 3600, 3600, "pool.ntp.org", "time.nist.gov");
  setenv("TZ", "GMT+01:00,M3.5.0/02:00:00,M10.5.0/03:00:00", 1);
  // Daylight saving time starts on the last(5) Sunday(0) of March(3) at 2:00 A.M.,
  // and ends on the last(5) Sunday(0) of October(10) at 2 : 00 A.M.    
  tzset();
  delay(1000);
  now = time(nullptr);
  lt = *localtime(&now);
}

void onDisconnection(const WiFiEventStationModeDisconnected& evt) {
  Serial.print("WiFi disconnesso. Motivo: ");  
  Serial.println(evt.reason); 
}


void updateESPUI(){  
  if(digitalRead(outCancello) == HIGH){            
    // L'aggiornamento del testo delle label può essere fatto usando il testo oppure l'id progressivo
    ESPUI.print("Stato attuale cancello", " APERTO");   
    // Per i pulsanti invece usiamo esclusivamente l'id (almeno per il momento)    
    ESPUI.printButton(idCancello, "Cancello APERTO", "CHIUDI");             
  } 
  else{        
    ESPUI.print("Stato attuale cancello", " CHIUSO");  
    ESPUI.printButton(idCancello, "Cancello CHIUSO",  "APRI");               
  }
  
  if(digitalRead(outBasculante) == HIGH){               
    ESPUI.print("Stato attuale basculante", " APERTA");       
    ESPUI.printButton(idBasculante, "Basculante APERTA", "CHIUDI");             
  } 
  else{        
    ESPUI.print("Stato attuale basculante", " CHIUSA");  
    ESPUI.printButton(idBasculante, "Basculante CHIUSA",  "APRI");               
  }  
}

// Funzioni che saranno eseguite alla pressione del relativo tasto
void buttonCancello(Control sender, int type) {      
  // Se pulsante premuto
  if (type == B_DOWN) {    
    // Inverto lo stato dell'uscita
    if(digitalRead(outCancello) == HIGH){    
      Serial.println("Cancello APERTO");         
      digitalWrite(outCancello, LOW);    
    } 
    else{
      Serial.println("Cancello CHIUSO");           
      digitalWrite(outCancello, HIGH);
    }
  }
  updateESPUI();
}

void buttonBasculante(Control sender, int type) {  
  // Se pulsante premuto
  if (type == B_DOWN) {    
    // Inverto lo stato dell'uscita    
    if(digitalRead(outBasculante) == HIGH){    
      Serial.println("Basculante APERTA");       
      digitalWrite(outBasculante, LOW);    
    } 
    else{
      Serial.println("Basculante CHIUSA");        
      digitalWrite(outBasculante, HIGH);
    }            
  }
  updateESPUI();
}


void setup(void) {
  Serial.begin(115200);
  pinMode(outCancello, OUTPUT);
  pinMode(outBasculante, OUTPUT);
    
  WiFi.begin(ssid, password);
  Serial.println("");
  // Attendo la connessione WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  connectedHandler = WiFi.onStationModeConnected(&onConnection);
  disconnectedHandler = WiFi.onStationModeDisconnected(&onDisconnection);
  
  // Quando sono connesso forzo il richiamo la funzione una prima volta (workaround)
  if (WiFi.isConnected()) {    
    WiFiEventStationModeConnected nullEvent;
    onConnection(nullEvent);
  }
   
  ESPUI.label("Heap", COLOR_CARROT, "0", "color: black;width:40%;");      // Id 0  
  ESPUI.label("Data", COLOR_CARROT, "0", "color: black;width:40%;");      // Id 1         
  
  ESPUI.label("Stato attuale cancello", COLOR_ALIZARIN, "CHIUSO", "clear:left;height:87px;width:50%;");                        
  idCancello = ESPUI.button("Cancello CHIUSO", &buttonCancello, COLOR_WETASPHALT, "APRI", "width:30%;");           
  
  ESPUI.label("Stato attuale basculante", COLOR_ALIZARIN, "CHIUSA", "clear:left;height:87px;width:50%;"); 
  idBasculante = ESPUI.button("Basculante CHIUSA", &buttonBasculante, COLOR_WETASPHALT, "APRI", "width:30%;");        

  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
   */

  /*
   * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a SECURE way of limiting access.
   * Anyone who is able to sniff traffic will be able to intercept your password since it is transmitted 
   * in cleartext ESPUI.begin("ESPUI Control", "myuser", "mypassword");
  */
  
  ESPUI.begin("Controllo apertura.");
  ESPUI.list(); // Solo se si usa ESPUI.beginSPIFFS()  
}

void loop(void) {
  if (millis() - updateTime > 1000) {
    updateTime = millis(); 
    // Aggiorno la data e l'orario attuale
    now = time(nullptr);   
    lt = *localtime(&now);
    char buf[24];
    strftime(buf, sizeof(buf), "%d/%m/%Y - %H:%M:%S", &lt);
    Serial.println(buf); 
    ESPUI.print("Data", buf);       
    ESPUI.print("Heap", String(ESP.getFreeHeap()));    
  }
}
