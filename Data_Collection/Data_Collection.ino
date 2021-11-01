#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* ssid     = "Wireless 2.4Ghz";
const char* password = "dozerhank";

#define CD_API "/v1/bpi/currentprice.json"
#define CD_URL "api.coindesk.com"

static char respBuffer[4096];

WiFiClient client;

float BitcoinUSD, previousBUSD;


void setup()  {
  //Arduino Communication Setup
  Serial1.begin(115200);
  delay(100);
  
  //WiFi initialization 
  Serial.begin(115200);
  delay(10);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Updating Bitcoin price
  previousBUSD = BitcoinUSD;
  BitcoinUSD = getData();
  if (BitcoinUSD == 0)  {
    BitcoinUSD = previousBUSD;
  } 
  Serial1.println(BitcoinUSD);
}


//Request and return the value of Bitcoin
float getData()  {
  const char request[] = 
    "GET " CD_API " HTTP/1.1\r\n"
    "User-Agent: ESP8266/0.1\r\n"
    "Accept: */*\r\n"
    "Host: " CD_URL "\r\n"
    "Connection: close\r\n"
    "\r\n";    
  
  //delay(1000);
  
  if (!client.connect(CD_URL, 80))
  {
    Serial.println("Connection failed");
    return 0.0;
  }

  client.print(request);
  client.flush();
  //delay(100);

  uint16_t index = 0;
  while(client.connected())
  {
    if(client.available())
    {
      respBuffer[index++] = client.read();
      delay(1);
    }
  }
  client.stop();
  char * json = strchr(respBuffer,'{');
  String json_str = String(json);
  
  uint16_t idx_d = json_str.lastIndexOf('d');
  json_str.remove(idx_d,3);
    
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, json);
  
  JsonObject bpi = doc["bpi"];
  JsonObject usd = bpi["USD"];
  float rate_float = usd["rate_float"];
  Serial.print("BTC (USD): $");
  Serial.println(rate_float);
  return rate_float;
}
