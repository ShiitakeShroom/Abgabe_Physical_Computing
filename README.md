# Abgabe_Physical_Computing
Das Github Repository für meine Semesterabgabe im 3_Gig Kurs Pysical Computing

# LED Simon Says with Joystick Input

Ein Simon Says Spiel das sich über einen Joystick steuern lässt. 

# Komponenten 

- Arduino Mega 2560 oder Arduino Uno
![image](https://drive.google.com/uc?export=view&id=1hiSJd5yH1DAKw2uczMnSHecqDYghV3IY)

-	Breadboard Generic
![image](https://drive.google.com/uc?export=view&id=1oxqVTpfvMHfTqh1F5q-e1xWvR4XHH10V)

-	Kabel

-	Full Color LED Pixel
![image](https://drive.google.com/uc?export=view&id=1OAr1PHcfVrhtdUGPnMAF0_blbZDhqW9o)

-	Resistor 100 ohm 

-	Arduino Daten Kabel

-	HW-504 JoyStick breakout Modul 
![image](https://drive.google.com/uc?export=view&id=1wR6mCGvW-e9sHc2xZfoCmoy3RmReKXpb)


# Schematic
Über das Breadboard werden die Komponenten (LED Pixel x4 und JoyStick breakout Modul) mit dem Ground und den fünf Volt verbunden. 
Es besteht auch die Möglichkeit den JoyStick mit dem 3,3 VOlt PIN zu verbinden, da der Joystick auch unter dieser Spannung funktioniert
Die RGB kontrolle wird über den vierten (4) PIN eingesteckt. 
Die X-Achse des JoySticks (VRx) wird in den PIN von A0 eingesteckt.
die Y-Achse des JoySticks (Vry) wird in den Pin von A1 eingesteckt.
![image](https://drive.google.com/uc?export=view&id=13__wiImGdgXW7VIOFSbN7H9BF-pF25Rl)

# Code 
```
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define PIN            4
#define NUMPIXELS      4// LEDS auf den dem Strip
#define BRIGHTNESS     10
int delayval = 1500;
int LED [5] = {0,1,2,3,4};
const int xAxisController = A0;
const int yAxisController = A1; // wo der Joystcik X und Y im Pin ist
boolean returnLed [] = {10};
int SensorWert = 0;

//Spielmechaniks
int turn = 0;// turn counter
int buttonstate = 0; //button State Checker
int randomArray[100]; //stores die Inputs 
int inputArray[100];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void fail()//funktion wird benutzt wenn der Spieler die falsche eingabe macht, die vier LEDs leuchten gleichzeitig rot auf; Funktion wird über die anderen Funktionen gestellt geschrieben, da sie sonst nicht erkannt wird
{
    for(int y=0; y<=2; y++)
    {
        pixels.setBrightness(10);
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.setPixelColor(1, pixels.Color(255, 0, 0));
        pixels.setPixelColor(2, pixels.Color(255, 0, 0));
        pixels.setPixelColor(3, pixels.Color(255, 0, 0));
        pixels.show();
        delay(200);

        pixels.setBrightness(10);
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.setPixelColor(1, pixels.Color(0, 0, 0));
        pixels.setPixelColor(2, pixels.Color(0, 0, 0));
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.show();
        delay(200);
    }
    delay(500);
    turn = -1; //Resets turn value so the game starts over
}

void setup() 
{   pixels.begin();
    Serial.begin(9600);

    LED [0] = pixels.Color(255, 255,255);
    LED [1] = pixels.Color(255, 0, 255);
    LED [2] = pixels.Color(0, 0,255);
    LED [3] = pixels.Color(0, 255, 0);
    LED [4] = pixels.Color(0, 0, 0);

    pinMode(PIN, OUTPUT); //output
    pinMode(xAxisController, INPUT);
    pinMode(yAxisController, INPUT);
    delay(1000);
}

void input()//funktion erlaubt es den Spieler input übert den Joystick einzugeben 
//funktion muss über der Loop funktion sein, damit sie in der loop funktion erkannt wird
{

   for(int x = 0; x <= turn;)
    {//kontrolliertr durch den turn count
        
        for(int y = 0; y<2; y++)
        {   
            SensorWert = analogRead(A0);   // Auslesen des Wertes, der an A0 anliegt. Hier : VRx - X-Achse
            Serial.print("X:");
            Serial.print(SensorWert, DEC); // Darstellung des Wertes als Dezimalzahl

            if(SensorWert == 1023)//Muss maximalwert angeben mit dem Joystick; mit dem größer als... oder kleiner als wert werden die meisten eingaben als Fehlermeldung angegeben; X-Achse wird nach rechts gedrückt für die weiße Farbe
            {
                pixels.setBrightness(10);
                pixels.setPixelColor(0, pixels.Color(255, 255,255));
                pixels.show();
                delay(200);
                pixels.setPixelColor(0, LED[4]);//schaltet den das Licht wieder aus nach der Eingabe 
                pixels.show();
                inputArray[x] = 1;
                delay(250);
                Serial.print("-");
                Serial.print(1);
                if (inputArray[x] != randomArray[x]){//schaut auf den wert des inputs des users und checkt es wieder
                    fail();                          // der wert im selben spot wie in der generierten Array
                }                                    //die fail funktion wird aufgerufen wenn es nicht matched
                x++;
            }

            if(SensorWert == 0)// xAchse nach links; Stick wird nach links gedrückt um die Farbe rot wiederzugeben
            {
                pixels.setBrightness(10);
                pixels.setPixelColor(1, pixels.Color(255, 0, 0));
                pixels.show();
                delay(200);
                pixels.setPixelColor(1, LED[4]);
                pixels.show();
                inputArray[x] = 2;
                delay(250);
                Serial.print("-");
                Serial.print(2);
                if (inputArray[x] != randomArray[x]){//schaut auf den wert des inputs des users und checkt es wieder
                    fail();                          // der wert im selben spot wie in der generierten Array
                }                                    //die fail funktion wird aufgerufen wenn es nicht matched
                x++;
            }

            SensorWert = analogRead(A1);   // Auslesen des Wertes, der an A0 anliegt. Hier : VRy - Y-Achse
            Serial.print(" |Y:");      
            Serial.print(SensorWert, DEC);


            if(SensorWert == 1023)// y-Achse unten; Den Stick nach unten drücken für die blaue Farbe
            {
                pixels.setBrightness(10);
                pixels.setPixelColor(2, pixels.Color(0, 0,255));
                pixels.show();
                delay(200);
                pixels.setPixelColor(2, LED[4]);
                pixels.show();
                inputArray[x] = 3;
                delay(250);
                Serial.print("-");
                Serial.print(3);
                if (inputArray[x] != randomArray[x]){//schaut auf den wert des inputs des users und checkt es wieder
                    fail();                          // der wert im selben spot wie in der generierten Array
                }                                    //die fail funktion wird aufgerufen wenn es nicht matched
                x++;
            }

            if(SensorWert == 0) //y-achse nach Oben; Stick wird nach oben gedrück für die Grüne Farbe
            {
                pixels.setBrightness(10);
                pixels.setPixelColor(3, pixels.Color(0, 255, 0));
                pixels.show();
                delay(200);
                pixels.setPixelColor(3, LED[4]);
                pixels.show();
                inputArray[x] = 4;
                delay(250);
                Serial.print("-");
                Serial.print(4);
                if (inputArray[x] != randomArray[x]){//schaut auf den wert des inputs des users und checkt es wieder
                    fail();                          // der wert im selben spot wie in der generierten Array
                }                                    //die fail funktion wird aufgerufen wenn es nicht matched
                x++;
            }
        }
    }
    delay(500);
    turn++; //der nächste turn fängt an, die letzte action bis die output funktion wieder beginnt 
}

void loop() 
{       
    

    for(int y = 0; y <= 99; y++)
    {
        pixels.setBrightness(10);
        pixels.setPixelColor(0, pixels.Color(255, 255, 255)); //Lässt alle LEDs kurz aufleuchten für einen positive bestätigung und auch als Signal für die aktivierung des Spieles
        pixels.setPixelColor(1, pixels.Color(255, 0, 0));
        pixels.setPixelColor(2, pixels.Color(0, 0, 255));
        pixels.setPixelColor(3, pixels.Color(0, 255, 0));
        pixels.show();
        delay(500);

        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.setPixelColor(1, pixels.Color(0, 0, 0));
        pixels.setPixelColor(2, pixels.Color(0, 0, 0));
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.show();
        delay(200);
        delay(1000);


        for(int y = turn; y <= turn; y++)
        {//Limitiert bei den runden die verfügbar sind
            Serial.println(""); //Serial input um das geschehen zu verfolgen
            Serial.print("Turn: ");
            Serial.print(y);
            Serial.println("");
            randomArray[y] = random(1,5); //ordnet eine random nummer von 1 - 4 zum randomArray[y], und y ist der turn count
            for(int x = 0; x <= turn; x++)
            {
                Serial.print(randomArray[x]);

                for(int y = 0; y<4; y++)
                {
                    if(randomArray[x] == 1 && y == 0)
                    {
                        pixels.setPixelColor(y, pixels.Color(255, 255,255));//LED leuchtet weiß auf
                        pixels.show();

                        delay(1000);
                        pixels.setPixelColor(y, LED[4]);//die Farbe des LEDs ist hier fix auf den wert (0, 0, 0)
                        pixels.show();

                        delay(100);
                    }

                    if(randomArray[x] == 2 && y == 1)
                    {
                        pixels.setBrightness(10);
                        pixels.setPixelColor(y, pixels.Color(255, 0, 0));//leuchtet rot auf
                        pixels.show();

                        delay(1000);
                        pixels.setPixelColor(y, LED[4]);
                        pixels.show();

                        delay(100);
                    }

                    if(randomArray[x] == 3 && y == 2)
                    {
                        pixels.setBrightness(10);
                        pixels.setPixelColor(y, pixels.Color(0, 0,255));//leuchtet blau auf
                        pixels.show();
                        delay(1000);
                        pixels.setPixelColor(y, LED[4]);
                        pixels.show();

                        delay(100);
                    }

                    if(randomArray[x] == 4 && y == 3)
                    {
                        pixels.setBrightness(10);
                        pixels.setPixelColor(y, pixels.Color(0, 255, 0));//leuchtet grün auf
                        pixels.show();
                        delay(1000);
                        pixels.setPixelColor(y, LED[4]);
                        pixels.show();
                        delay(100);
                    }
                }
            }
        }
        input();
    }
}
```
