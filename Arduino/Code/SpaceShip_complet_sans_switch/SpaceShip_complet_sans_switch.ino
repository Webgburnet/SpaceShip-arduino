int state = 0;
int switchstate = 0;
int Ready = 0;
int w8_key = 0;
String incomingString;

int led_verte=3;
int led_rouge1=4;
int led_rouge2=5;
int BP=2;

void setup() {
  Serial.begin(9600);
  Serial.println("Debut Initialisation");
  pinMode(led_verte, OUTPUT);
  pinMode(led_rouge1, OUTPUT);
  pinMode(led_rouge2, OUTPUT);
  
  pinMode(BP, INPUT);

  digitalWrite(led_verte, LOW); 
  digitalWrite(led_rouge1, LOW);  
  digitalWrite(led_rouge2, LOW);

  Serial.println("Debut Initialisation");
}

void loop() {
  switchstate = digitalRead(BP);
  Serial.print("Etat BP : ");
  Serial.println(switchstate);

  Serial.print("Etat Ready : ");
  Serial.println(Ready);

  Serial.print("MDP entree : ");
  Serial.println(incomingString);

  /* 1. Tant que le bouton poussoir n’est pas actionné
     LED verte allumée.
     LEDs rouge éteintes.
  */
  if(switchstate == LOW && Ready == 0) 
  {
    digitalWrite(led_verte, HIGH); 
    digitalWrite(led_rouge1, LOW);  
    digitalWrite(led_rouge2, LOW);
  }
  
  /* 2. A l’appuie sur le bouton poussoir
     LED verte s’éteint.
     LEDs rouge clignotent (250ms allumées, 250ms éteintes) tant que le bouton poussoir est activé 
  */
  else if (switchstate == HIGH)
  {
    digitalWrite(led_verte, LOW);
    digitalWrite(led_rouge1, HIGH); 
    digitalWrite(led_rouge2, HIGH);    
        delay(250);
    digitalWrite(led_rouge1, LOW);  
    digitalWrite(led_rouge2, LOW); 
    delay(250);
    Ready = 1;
  }
  /* 2. Au relachement sur le bouton poussoir
     LED verte s’éteint.
     LEDs rouge restent allumées lorsque le bouton poussoir est relâché.
  */
  else if (switchstate == LOW && Ready == 1)
  {
    digitalWrite(led_verte, LOW);
    digitalWrite(led_rouge1, HIGH); 
    digitalWrite(led_rouge2, HIGH);
  }
  
  /*3. L’utilisateur doit maintenant entrer le mot de passe « rdy »
     LED verte clignote (250ms allumé, 250ms éteinte).
     LEDs rouge éteintes.
  */
  if (Serial.available() > 0)
  {
    digitalWrite(led_rouge1, LOW);
    digitalWrite(led_rouge2, LOW);
    digitalWrite(led_verte, HIGH);
    delay(250);
    digitalWrite(led_verte, LOW);
    delay(250);
    incomingString = Serial.readString();
    Serial.print("mdp entree : ");
    Serial.println(incomingString);
  }

  /* 4. Lorsque le mot de passe « rdy » est reconnu
       Toutes les LEDs éteintes, puis chaque LED s’allume (pin5, puis pin 4, puis pin 3) avec un délai entre chaque allumage de 1000ms.
  */
  if (incomingString == "rdy")
  {
    digitalWrite(led_rouge1, LOW);
    digitalWrite(led_rouge2, LOW);
    digitalWrite(led_verte, LOW);
    delay(1000);
    digitalWrite(led_rouge2, HIGH);
    delay(1000);
    digitalWrite(led_rouge1, HIGH);
    delay(1000);
    digitalWrite(led_verte, HIGH);
    delay(1000);
    Serial.println("Space Ship is ready to initiate");
    w8_key = 0;
  }
  else if (incomingString == "")
  {
    w8_key = 0;
  }
  else
  {
    w8_key = 1;
  }
  
  /* 5. Si le mot de passe entré est le mauvais
      Afficher dans la communication série le message d’erreur : « Critical ERROR » avec un retour à la ligne automatique. Ce message sera répété toutes les 1000ms.
  */
  if(w8_key == 1)      
  {
    Serial.println("Critical ERROR");
    delay(1000);
  }    
}
