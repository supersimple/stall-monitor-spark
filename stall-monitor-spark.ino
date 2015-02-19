// spark code //
int reed = 0;
int led = 7;
int state = 0;
int previousState = 0;
char stateString[43];

TCPClient client;
byte server[] = { 104, 131, 138, 105 };


void setup() {
  Spark.variable("state", &stateString, STRING);
  pinMode(reed, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void sendGetRequest(const char * url) {
    while (!client.connect(server, 3000)) {
      delay(100);
    }
    Serial.println(client.connected());
    if (client.connected()) {
      client.print("GET ");
      client.print(url);
      client.println(" HTTP/1.0");
      client.println("Connection: close");
      client.println();
      client.flush();
      delay(100);
      client.stop();
    }
}

void loop() {
  previousState = state;
  state = digitalRead(reed);
  strcpy(stateString, state > 0 ? "/update/true" : "/update/false");
  
  if (state != previousState) {
    //Spark.publish("state", stateString);
    digitalWrite(led, state > 0 ? HIGH : LOW);
    sendGetRequest(stateString);
  }
}
