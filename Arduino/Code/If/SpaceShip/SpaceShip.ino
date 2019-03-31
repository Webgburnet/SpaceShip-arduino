int switchstate = 0;
int Ready = 0;
int w8_key = 0;
String incomingString;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(2, INPUT);

  Serial.begin(9600);
}

void loop() {
  switchstate = digitalRead(2);
    if (switchstate == LOW && Ready == 0) {
      digitalWrite(3, HIGH); 
      digitalWrite(4, LOW);  
      digitalWrite(5, LOW); 
    }  
    else if (switchstate == HIGH){
      digitalWrite(3, LOW);  
      digitalWrite(4, LOW);  
      digitalWrite(5, LOW); 
      delay(250);
      digitalWrite(4, HIGH); 
      digitalWrite(5, HIGH);  
      delay(250);
      Ready = 1;
    }
    else if (switchstate == LOW && Ready == 1 && Serial.available() > 0){
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      delay(250);
      digitalWrite(3, HIGH);
      delay(250);
      incomingString = Serial.readString();
      w8_key = 1;
    }
    else if (switchstate == LOW && Ready == 1 && incomingString == "rdy" && w8_key == 1){
       digitalWrite(3, LOW);
       delay(250);
       digitalWrite(3, HIGH);
       delay(250);
    }
    else if (switchstate == LOW && Ready == 1 && incomingString != "rdy" && w8_key == 1){
      Serial.println("Critical ERROR, Call 911 now!");
      delay(500);
    }
}
