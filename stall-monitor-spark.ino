//code for Spark Core - spark.io //

int reed = 0;
int led = 7;
int state = 0;
int previousState = 0;
char stateString[43];

TCPClient client;
char serverOccupied[ ] = "http://yourdomain.com/update/true";
char serverUnoccupied[ ] = "http://yourdomain.com/update/false";

void setup() {
  Spark.variable("state", &stateString, STRING);
  pinMode(reed, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  previousState = state;
  state = digitalRead(reed);
  strcpy(stateString, state > 0 ? "true" : "false");
  
  if (state != previousState) {
    Spark.publish("state", stateString);
    digitalWrite(led, state > 0 ? HIGH : LOW);
    if (state == 0){
		if (client.connect(serverUnoccupied, 3000))
		{
		    Serial.println("connected");
		}
		else
		{
		    Serial.println("connection failed");
		}
    }else{
        if (client.connect(serverOccupied, 3000))
		{
		    Serial.println("connected");
		}
		else
		{
		    Serial.println("connection failed");
		}  
    }
  }
}