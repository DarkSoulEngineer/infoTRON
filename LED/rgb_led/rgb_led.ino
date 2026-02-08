/*
 Acest program controleaza un LED RGB conectat la pinii 25, 26 si 27. 
 Fiecare pin controleaza o culoare (roșu, verde, albastru) a LED-ului.
 Programul aprinde fiecare culoare pe rand, apoi combina toate culorile pentru a crea alb si violet.
*/

// Definirea pinilor pentru LED RGB
int redPin = 25;    // Pinul conectat la LED-ul roșu
int greenPin = 26;  // Pinul conectat la LED-ul verde
int bluePin = 27;   // Pinul conectat la LED-ul albastru

void setup() {
    // Setăm fiecare pin ca ieșire pentru a putea controla LED-urile
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void loop() {
    // Secvență de culori

    setColor(255, 0, 0);     // Roșu: aprinde LED-ul roșu
    delay(1000);             // Așteaptă 1 secundă

    setColor(0, 255, 0);     // Verde: aprinde LED-ul verde
    delay(1000);             // Așteaptă 1 secundă

    setColor(0, 0, 255);     // Albastru: aprinde LED-ul albastru
    delay(1000);             // Așteaptă 1 secundă

    setColor(255, 255, 255); // Alb: aprinde toate LED-urile
    delay(1000);             // Așteaptă 1 secundă

    setColor(170, 0, 255);   // Violet: combinație roșu + albastru
    delay(1000);             // Așteaptă 1 secundă
}

// Funcție pentru setarea culorii LED-ului RGB
// redValue, greenValue, blueValue: valori între 0 și 255 (intenția este PWM)
void setColor(int redValue, int greenValue, int blueValue) {
    analogWrite(redPin, redValue);   
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
}

/*
 Funcția setColor(redValue, greenValue, blueValue) primește trei parametri care reprezintă intensitatea
  fiecărei culori (roșu, verde, albastru) și setează aceste valori pe pinii corespunzători.

 Funcția analogWrite(pin, value) este folosită pentru a seta o valoare PWM pe un pin digital,
    permițând controlul intensității LED-urilor. Valoarea poate fi între 0 (LED stins) și 255
    (LED la intensitate maximă).
*/