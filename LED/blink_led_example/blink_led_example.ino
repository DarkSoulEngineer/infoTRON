/*
 LED Blink Example
    Acest program aprinde si stinge un LED conectat la pinul 25 la intervale de 1 secunda.
*/

int ledPin = 25;                  // Pinul la care este conectat LED-ul 

// Functia setup() este apelata o singura data la pornirea programului
void setup(){
    pinMode(ledPin, OUTPUT);      // Seteaza pinul LED-ului verde ca iesire
}

// Functia loop() este apelata in mod repetat dupa ce setup() s-a executat
void loop(){
    digitalWrite(ledPin, HIGH);   // seteaza valoarea 1 (HIGH) pe pinul ledPin -> LED aprins
    delay(1000);                  // Asteapta 1 secunda
    digitalWrite(ledPin, LOW);    // seteaza valoarea 0 (LOW) pe pinul ledPin -> LED stins
    delay(1000);                  // Asteapta 1 secunda
}

/*
 Functia digitalWrite(parametru1, parametru2) este folosita pentru a seta starea unui pin digital (HIGH sau LOW).
 Functia delay(miliseconds) este folosita pentru a introduce o intarziere in executia
   programului, masurata in milisecunde (1000 ms = 1 secunda).
 
 parametru1: numarul pinului digital pe care dorim sa-l controlam
 parametru2: starea pe care dorim sa o setam pe pin (HIGH sau LOW sau valori intre 0 si 255)
*/