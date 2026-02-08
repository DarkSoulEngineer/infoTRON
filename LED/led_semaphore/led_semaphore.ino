/*
    Acest program simuleaza un semafor folosind trei LED-uri: rosu, galben si verde.
    Fiecare LED este conectat la un pin digital diferit al placii de dezvoltare.
    Programul va aprinde LED-urile in secventa specifica unui semafor: rosu -> galben -> verde -> rosu, etc.
    
    Pinul pentru LED-ul rosu este conectat la pinul 25
    Pinul pentru LED-ul galben este conectat la pinul 26
    Pinul pentru LED-ul verde este conectat la pinul 27
    
    Fiecare stare a semaforului dureaza un anumit timp:
        - Semafor rosu: 5 secunde
        - Semafor galben: 2 secunde
        - Semafor verde: 5 secunde
*/

int redPin    = 25;                        // Pinul la care este conectat LED-ul rosu
int yellowPin = 26;                        // Pinul la care este conectat LED-ul galben
int greenPin  = 27;                        // Pinul la care este conectat LED-ul verde

void setup(){
    pinMode(redPin, OUTPUT);               // Seteaza pinul LED-ului rosu ca iesire
    pinMode(yellowPin, OUTPUT);            // Seteaza pinul LED-ului galben ca iesire
    pinMode(greenPin, OUTPUT);             // Seteaza pinul LED-ului verde ca iesire
}

void loop(){
    // Semafor rosu
    digitalWrite(redPin, HIGH);            // LED rosu aprins
    digitalWrite(yellowPin, LOW);          // LED galben stins
    digitalWrite(greenPin, LOW);           // LED verde stins
    delay(5000);                           // Asteapta 5 secunde

    // Semafor galben
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
    delay(2000);                           // Asteapta 2 secunde

    // Semafor verde
    digitalWrite(redPin, LOW);             // LED rosu stins
    digitalWrite(yellowPin, LOW);          // LED galben stins
    digitalWrite(greenPin, HIGH);          // LED verde aprins
    delay(5000);                           // Asteapta 5 secunde
}