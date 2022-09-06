# Dokumentation

Zu Beginn des Monats und hin zur Abgabe wollte ich einen Amazon Alexa mithilfe eines Arduinos und einem 1Sheeld wie in diesem Tutorial nachbauen:

https://create.arduino.cc/projecthub/ahmedismail3115/arduino-based-amazon-echo-using-1sheeld-84fa6f?ref=platform&ref_id=424_trending___&offset=53

Davon wurde mir jedoch schnell abgeraten und aufgrund meines Studentendaseins und der daraus folgenden finanziellen Lage nicht realisierbar.
![image](https://drive.google.com/uc?export=view&id=1aa5OUiu2Ba9FkO2ouKvoy2v38dYOUvDQ)

Aufgrund dessen hab ich dann nach einem neuen Projekt gesucht. 
Von einem Bekannten konnte ich mir zum Glück einige Bauteile leihen und daraus innerhalb kürzester Zeit ein Ersatzprojekt verwirklichen:

![image](https://drive.google.com/uc?export=view&id=1eI2QroJiqDm77rjcbEbb_S03Gp_wSA4x)

Das Sammelsorium der Teile enthielt unter anderem verschiedene Sensoren, LED´s, ein Joystick, usw. 

## Projekt

Unter den Teilen waren ein Joystick und eine Pixel-LED. 
Mit den kam mir Idee einen Simons Says Spiel nachzubauen.

## Simons Says  

Das Prinzip hinter dem Spiel ist es den Anweisungen von Simon zu folgen. In der elektrischen Variante besitzt das Spiel vier verschieden farbige Knöpfe, die zufällig aufleuchten. 
Der Spieler muss die Anweisung des Spiels selbst folgen, indem der Spieler in der Reihenfolge auf den Knöpfen drücke in der sie aufleuchten. 
Wenn der Spieler die richtige Reihenfolge einhält, bekommt er eine positive Bestätigung wo alle Lichter aufleuchten und die nächste Runde beginnt. 
falls der Spieler jedoch fehlschlägt, leuchten die Tasten in Rot auf und das Spiel beginnt von vorne.
Mit jeder erfolgreich abgeschlossenen runde leuchtet in der Reihenfolge ein zusätzliches Licht auf. 

# Der Projekt
## Auseinandersetzung mit der Hardware

### Joy-Stick 

Mit Hilfe des Tutorials habe ich mich an dem Joystick getestet und versucht ihn wie im Code eine Antwort von dem Input über den Joystick zu bekommen.
Tutorial
https://funduino.de/nr-22-joystick-modul

### LED Pixel 

Hier war die Übung drin das LED blinken zu lassen. Funktioniert soweit auch so mit dem Code. 
Tutorial
https://arduinomodules.info/ky-009-rgb-full-color-led-smd-module/

### Kombinierte LED aktivieren 

Mit dem Bekannt haben wir dann vier LED´s aneinander gelötet. Über den Code aus dem vorherigen Tutorial wurden die LED´s nicht angesprochen. 
Mit ein wenig Internet Recherche bin ich über die „Adafruit_Neopixel“ Liberay gestoßen. 
Mit diesem Tutorial und diesen Code versuchen konnte ich die LED´s zufällig in fixen Farben aufblinken lassen. 
https://github.com/adafruit/Adafruit_NeoPixel


## Die Herausforderung 
Jetzt nachdem ich mich mit den verschiedenen Komponenten auseinander gesetzt habe  musste ich einen Code schreiben mit dem ich den Joystick als Input und die LED´s als Input anspreche. 
Aber da ich als totaler Anfänger keinen Ahnung hab wie ich da überhaupt anfangen soll und die Tutorials mir nur Einblick gaben wie man die Komponenten ansprechen kann und nicht wie man sie in Kombination benutzen kann.

Mit Hilfe des Tutorials von faziefazie hab ich dann die Ahnung bekommen wie ich den Code schreiben kann. 
Mit den Übungen vorher war es dann recht einfach den Code auf die Komponenten anzupassen und zu konfigurieren. 

das Tutorial von _faziefazie_
https://www.instructables.com/Arduino-Simple-Simon-Says-Game/

Der orginale Code aus des Tutorial von fayiefazie:
```
/*Simon Says game. Now with sound effects. 

Originaly made by Robert Spann
Code trimmed and sound effects added by digimike

Buttons are to be set on there designated pins without pull down resistors
and connected to ground rather then +5. 
*/
#include <Tone.h>
Tone speakerpin;
int starttune[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4};
int duration2[] = {100, 200, 100, 200, 100, 400, 100, 100, 100, 100, 200, 100, 500};
int note[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5};
int duration[] = {100, 100, 100, 300, 100, 300};
boolean button[] = {2, 3, 4, 5}; //The four button input pins
boolean ledpin[] = {8, 9, 10, 11};  // LED pins
int turn = 0;  // turn counter
int buttonstate = 0;  // button state checker
int randomArray[100]; //Intentionally long to store up to 100 inputs (doubtful anyone will get this far)
int inputArray[100];  


void setup() 
{
  Serial.begin(9600);
  speakerpin.begin(12); // speaker is on pin 12

  for(int x=0; x<4; x++)  // LED pins are outputs
  {
    pinMode(ledpin[x], OUTPUT);
  }
  
  for(int x=0; x<4; x++) 
  {
    pinMode(button[x], INPUT);  // button pins are inputs
    digitalWrite(button[x], HIGH);  // enable internal pullup; buttons start in high position; logic reversed
  }

  randomSeed(analogRead(0)); //Added to generate "more randomness" with the randomArray for the output function
  for (int thisNote = 0; thisNote < 13; thisNote ++) {
     // play the next note:
     speakerpin.play(starttune[thisNote]);
     // hold the note:
     if (thisNote==0 || thisNote==2 || thisNote==4 || thisNote== 6)
     {
       digitalWrite(ledpin[0], HIGH);
     }
     if (thisNote==1 || thisNote==3 || thisNote==5 || thisNote== 7 || thisNote==9 || thisNote==11)
     {
       digitalWrite(ledpin[1], HIGH);
     }
     if (thisNote==8 || thisNote==12)
     {
       digitalWrite(ledpin[2], HIGH);
     }  
     if (thisNote==10)
     {   
       digitalWrite(ledpin[3], HIGH);
     }
     delay(duration2[thisNote]);
     // stop for the next note:
     speakerpin.stop();
     digitalWrite(ledpin[0], LOW);
     digitalWrite(ledpin[1], LOW);
     digitalWrite(ledpin[2], LOW);
     digitalWrite(ledpin[3], LOW);
     delay(25);
    }
  delay(1000);
}
 
void loop() 
{   
  for (int y=0; y<=99; y++)
  {
    //function for generating the array to be matched by the player
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
  
    for (int thisNote = 0; thisNote < 6; thisNote ++) {
     // play the next note:
     speakerpin.play(note[thisNote]);
     // hold the note:
     delay(duration[thisNote]);
     // stop for the next note:
     speakerpin.stop();
     delay(25);
    }
    
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    delay(1000);
  
    for (int y=turn; y <= turn; y++)
    { //Limited by the turn variable
      Serial.println(""); //Some serial output to follow along
      Serial.print("Turn: ");
      Serial.print(y);
      Serial.println("");
      randomArray[y] = random(1, 5); //Assigning a random number (1-4) to the randomArray[y], y being the turn count
      for (int x=0; x <= turn; x++)
      {
        Serial.print(randomArray[x]);
      
        for(int y=0; y<4; y++)
        {
      
          if (randomArray[x] == 1 && ledpin[y] == 8) 
          {  //if statements to display the stored values in the array
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_G3, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }

          if (randomArray[x] == 2 && ledpin[y] == 9) 
          {
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_A3, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
  
          if (randomArray[x] == 3 && ledpin[y] == 10) 
          {
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_B3, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }

          if (randomArray[x] == 4 && ledpin[y] == 11) 
          {
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_C4, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
        }
      }
    }
    input();
  }
}
 
 
 
void input() { //Function for allowing user input and checking input against the generated array

  for (int x=0; x <= turn;)
  { //Statement controlled by turn count

    for(int y=0; y<4; y++)
    {
      
      buttonstate = digitalRead(button[y]);
    
      if (buttonstate == LOW && button[y] == 2)
      { //Checking for button push
        digitalWrite(ledpin[0], HIGH);
        speakerpin.play(NOTE_G3, 100);
        delay(200);
        digitalWrite(ledpin[0], LOW);
        inputArray[x] = 1;
        delay(250);
        Serial.print(" ");
        Serial.print(1);
        if (inputArray[x] != randomArray[x]) { //Checks value input by user and checks it against
          fail();                              //the value in the same spot on the generated array
        }                                      //The fail function is called if it does not match
        x++;
      }
       if (buttonstate == LOW && button[y] == 3)
      {
        digitalWrite(ledpin[1], HIGH);
        speakerpin.play(NOTE_A3, 100);
        delay(200);
        digitalWrite(ledpin[1], LOW);
        inputArray[x] = 2;
        delay(250);
        Serial.print(" ");
        Serial.print(2);
        if (inputArray[x] != randomArray[x]) {
          fail();
        }
        x++;
      }

      if (buttonstate == LOW && button[y] == 4)
      {
        digitalWrite(ledpin[2], HIGH);
        speakerpin.play(NOTE_B3, 100);
        delay(200);
        digitalWrite(ledpin[2], LOW);
        inputArray[x] = 3;
        delay(250);
        Serial.print(" ");
        Serial.print(3);
        if (inputArray[x] != randomArray[x]) {
          fail();
        }
        x++;
      }

      if (buttonstate == LOW && button[y] == 5)
      {
        digitalWrite(ledpin[3], HIGH);
        speakerpin.play(NOTE_C4, 100);
        delay(200);
        digitalWrite(ledpin[3], LOW);
        inputArray[x] = 4;
        delay(250);
        Serial.print(" ");
        Serial.print(4);
        if (inputArray[x] != randomArray[x]) 
        {
          fail();
        }
        x++;
      }
    }
  }
  delay(500);
  turn++; //Increments the turn count, also the last action before starting the output function over again
}

void fail() { //Function used if the player fails to match the sequence
 
  for (int y=0; y<=2; y++)
  { //Flashes lights for failure
    
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    speakerpin.play(NOTE_G3, 300);
    delay(200);
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    speakerpin.play(NOTE_C3, 300);
    delay(200);
  }
  delay(500);
  turn = -1; //Resets turn value so the game starts over without need for a reset button
}
```

## Der Aufbau der Schaltkreises

Schritt 1. Das Breadboard und das Arduino bereitstellen und den Ground und die 5V über Kabel an das Breadboard anschließen. 
![image](https://drive.google.com/uc?export=view&id=1yqWPTNw7CM-bDCXt3srCTicOBYDhPk3w)
![image](https://drive.google.com/uc?export=view&id=1xBmRgFFi-__kPan4EJiY6euynfpXXgGO)

Schritt 2: Die Kabel an die Komponenten anschließen 
![image](https://drive.google.com/uc?export=view&id=1YffoRbdV1k2WwZmN-4REde0tiTDDPNgG)
![image](https://drive.google.com/uc?export=view&id=1iqX59vGz8PmEdaVLbAVm-EwOlCekCJ01)
![image](https://drive.google.com/uc?export=view&id=1WM5itZ1Iu6y0WhtUdG_SZaBnQB4mNssv)

Schritt 2.5: LED´s verkabeln und anschließen
![image](https://drive.google.com/uc?export=view&id=1JTCkvKeNAIodpCqtLEJc4ydG12UiVLD3)
![image](https://drive.google.com/uc?export=view&id=1GmpeywmBTSnVG1nGGMR8eedMGH0Mfp0Y)

Am Output der LED´s ist ein Wiederstand verlöhtet
![image](https://drive.google.com/uc?export=view&id=1sMm9My6rx2ILVAn0Xucrhsr54n5A78bR)


Das LED wird mit den Kabeln verbunden. 
![image](https://drive.google.com/uc?export=view&id=1Z-FADF-P9d7N11qOIsT-7YT6uLR3JbnA)


Im Code spricht der PIN Nummer 4 die LED´s an. 
![image](https://drive.google.com/uc?export=view&id=1fhn0izGCTbqpU9B93PMdggElH7ckslRV)

Die Kabel mit den die x- und y-Achsen des Joysticks verbunden sind werden in die PIN´s A0 und A1 gesteckt.
![image](https://drive.google.com/uc?export=view&id=1IJx95v9oKq4-GAuWfasjK-ugPl6vUbbe)

Wie auch die LED Kabel werden die Kabel des JoySticks mit dem Ground mit dem 5 Volt PIN verbunden. 
![image](https://drive.google.com/uc?export=view&id=1_BPiSSkGVgG63QeLUy8wCLkAW0_QOTsq)

Das ist der Endstand des Projektes.

## Wie funktioniert es 
Mit der Hilfe des Codes funktioniert das Spiel. 
Die Anleitung ist einfach. Wenn das Spiel bzw. das Arduino eingeschaltet wird leuchtet es in den vier voreingestellten Farben auf und nach einem kurzen Delay fängt das erste LED an aufzuleuchten und verlischt darauf hin. Hier muss der User dann mit dem Joystick eine Eingabe machen. Wenn der User in die richtige Richtung drückt leuchtet das selbe LED auf. Wenn man die Falsche Richtung drückt leuchtet das jeweilige LED auf und kurz darauf blinken alle LED´s rot auf und das Spiel beginnt von vorne.

## Reflektion zu dem Kurs und der Abgabe
Mit der Anmeldung zum Kurs wollte ich mich etwas mehr mit meinem Coding Kenntnissen auseinandersetzen. Mit dem Verlauf des Kurses habe ich das auch gelernt mich C/C++ auseinanderzusetzen und wie ich Codes für die mir gegeben Komponenten umschreiben kann. Mit den gewonnenen Erfahrungen würde ich weiterhin an gerne solchen Projekten arbeiten die etwas Komplizierte sind als „Simon Says“. Zudem will ich weiter an der „Übersetzung“ von Codes für den Eigengebrauch erarbeiten und für meine Projekte benutzen.  


