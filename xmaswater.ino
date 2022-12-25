//pin czujnika wilgotnosci
const byte pin_tree_water=A0;

// pin sterujacy przkaznikiem od pompy
const byte pin_relay=7;

//piny do czujnika ultrasonograficznego
const byte pin_echo=2;
const byte pin_trig=3;

//zmienne sterujace
const float max_tree_water = 0.30;
const int bucket_height = 30;
const int min_water_height = 5;

//zmienne
float tree_water=0;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int water_in_bucket;



void setup()
{
  pinMode(pin_relay, OUTPUT); // Relay
  pinMode(pin_trig, OUTPUT); // Sets the pin_trig as an OUTPUT
  pinMode(pin_echo, INPUT); // Sets the pin_echo as an INPUT
  Serial.begin(9600);
}
void loop()
{
  
  //Zmierz poziom wody w choince
  tree_water=analogRead(pin_tree_water);
  tree_water = tree_water*5/1024;

  //Zmierz poziom wody w pojemniku
  digitalWrite(pin_trig, LOW);// Clears the pin_trig condition
  delayMicroseconds(2);
  digitalWrite(pin_trig, HIGH); // Sets the pin_trig HIGH (ACTIVE) for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(pin_trig, LOW);
  duration = pulseIn(pin_echo, HIGH);// Reads the pin_echo, returns the sound wave travel time in microseconds
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Odleglosc");
  Serial.println(distance);

    //Wody w wiadrze mamy z roznicy pomiedzy wysokoscia wiadra i lustrem wody z sensora sonicznego
    water_in_bucket = bucket_height - distance;
    
    if ( water_in_bucket > min_water_height) {
      //Mamy wode we wiadrze możemy podelwac
      Serial.print("Mamy we wiadrze ");
      Serial.print(water_in_bucket);
      Serial.print(" wody, sensor w choince wskazuje  ");
      Serial.print(tree_water);

        if (tree_water < max_tree_water) {
        // Trzeba podlać
        Serial.println("zatem PODLEWAMY");
        digitalWrite(pin_relay,LOW);

        } else {
        // Nie potrzeba podlewać
        Serial.println("NIE Podlewamy");
        digitalWrite(pin_relay,HIGH);
        }

    } else {
      //Nie mamy wody we wiadrze
      Serial.print("NIE MAMY wody we wiadrze ");
      Serial.print(water_in_bucket);
    }
     


  delay(1000);
}
