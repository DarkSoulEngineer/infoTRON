/*
    Acest program controleaza trei LED-uri (rosu, galben, verde) si un buton. 
    Apasarea butonului schimba modelul de iluminare al LED-urilor.
    
    Pinout:
        - Buton: pinul 34
        - LED rosu: pinul 25
        - LED galben: pinul 26
        - LED verde: pinul 27
*/

// Definirea pinilor pentru buton și LED-uri
int buttonPin = 34;                            // Pinul la care este conectat butonul

int redPin    = 25;                            // Pinul la care este conectat LED-ul rosu
int yellowPin = 26;                            // Pinul la care este conectat LED-ul galben
int greenPin  = 27;                            // Pinul la care este conectat LED-ul verde

int currentPattern = 0;                        // Variabila pentru a tine evidenta modelului curent

// Functie pentru schimbarea modelului de iluminare
void change_pattern() {
    currentPattern = (currentPattern + 1) % 3; // Incrementam currentPattern si revenim la 0 dupa ce ajungem la 2
}

// Functia setup() este apelata o singura data la pornirea programului
void setup(){
    pinMode(buttonPin, INPUT_PULLUP);          // Seteaza pinul butonului ca intrare

    pinMode(redPin, OUTPUT);                   // Seteaza pinul LED-ului rosu ca iesire
    pinMode(yellowPin, OUTPUT);                // Seteaza pinul LED-ului galben ca iesire
    pinMode(greenPin, OUTPUT);                 // Seteaza pinul LED-ului verde ca iesire
}

// Functia loop() este apelata in mod repetat dupa ce setup() s-a executat
void loop(){
    if(digitalRead(buttonPin) == LOW) { // LOW când este apăsat
        change_pattern();
        delay(200); // Debounce pentru a preveni multiple schimbari de pattern la o singura apasare
    }

    // Alege modelul de iluminare in functie de valoarea lui currentPattern
    switch (currentPattern)                    
    {
    case 0:
        digitalWrite(redPin, HIGH);            // LED rosu aprins
        digitalWrite(yellowPin, LOW);          // LED galben stins
        digitalWrite(greenPin, HIGH);          // LED verde stins
        delay(1000);                           // Asteapta 1 secunda
        digitalWrite(redPin, LOW);             // LED rosu stins
        digitalWrite(yellowPin, HIGH);         // LED galben aprins
        digitalWrite(greenPin, LOW);           // LED verde stins
        delay(1000);                           // Asteapta 1 secunda
        digitalWrite(redPin, LOW);             // LED rosu stins
        digitalWrite(yellowPin, LOW);          // LED galben stins
        digitalWrite(greenPin, LOW);           // LED verde aprins
        delay(500);                            // Asteapta 0.5 secunda
        break;
    case 1:
        digitalWrite(redPin, HIGH);            // LED rosu aprins
        digitalWrite(yellowPin, HIGH);         // LED galben aprins
        digitalWrite(greenPin, HIGH);          // LED verde aprins
        delay(1000);                           // Asteapta 1 secunda
        digitalWrite(redPin, LOW);             // LED rosu stins
        digitalWrite(yellowPin, LOW);          // LED galben stins
        digitalWrite(greenPin, LOW);           // LED verde stins
        break;
    case 2:
        digitalWrite(redPin, HIGH);            // LED rosu aprins
        digitalWrite(yellowPin, LOW);          // LED galben stins
        digitalWrite(greenPin, LOW);           // LED verde stins
        delay(500);                            // Asteapta 0.5 secunda
        digitalWrite(redPin, LOW);             // LED rosu stins
        digitalWrite(yellowPin, HIGH);         // LED galben aprins
        digitalWrite(greenPin, LOW);           // LED verde stins
        delay(500);                            // Asteapta 0.5 secunda
        digitalWrite(redPin, LOW);             // LED rosu stins
        digitalWrite(yellowPin, LOW);          // LED galben stins
        digitalWrite(greenPin, HIGH);          // LED verde aprins
        delay(500);                            // Asteapta 0.5 secunda
        break;
    default:
        break;
    }
}
