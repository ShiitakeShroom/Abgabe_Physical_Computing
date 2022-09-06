#include <Arduino.h> // der code für das Projekt nochmal seperat

/*int ledUnten = 6;
int ledOben = 7;
int ledLinks = 8;
int ledRechts = 9;                                                                                
int SensorWert = 0;   // Festlegen der Variablen
 
void setup() 
    {
     pinMode(ledUnten, OUTPUT);   // Definieren der LEDs
     pinMode(ledOben, OUTPUT);
     pinMode(ledLinks, OUTPUT);
     pinMode(ledRechts, OUTPUT);
     Serial.begin(9600);
    }
 
void loop() 
{
       SensorWert = analogRead(A0);   // Auslesen des Wertes, der an A0 anliegt. Hier : VRx - X-Achse
       
       Serial.print("X:");  // Darstellung des Wertes im Seriellen Monitor
       Serial.print(SensorWert, DEC); // Darstellung des Wertes als Dezimalzahl
       
       
             if (SensorWert > 1010)  // Wenn der Wert größer als 1010 ist, dann...
                 {
                  digitalWrite(ledLinks, HIGH); // ...soll ledLinks leuchten
                 }
             
             if (SensorWert < 1010) // Wenn der Wert kleiner als 1010 ist, dann...
                 {
                  digitalWrite(ledLinks, LOW); // ...soll ledLinks nicht mehr leuchten
                 }
             
             if (SensorWert < 20 )  // Wenn der Wert größer als 20 ist, dann...
                 {
                  digitalWrite(ledRechts, HIGH); // ...soll ledRechts leuchten
                 }
             
             if (SensorWert > 20)  // Wenn der Wert kleiner als 20 ist, dann...
                 {
                  digitalWrite(ledRechts, LOW); // ...soll ledRechts nicht mehr leuchten
                 }
       
      
       SensorWert = analogRead(1); // Auslesen des Wertes, der an A1 anliegt. Hier : VRy - Y-Achse
              
       Serial.print(" |Y:");      
       Serial.print(SensorWert, DEC);

       
       
             if (SensorWert > 1010) // Wenn der Wert größer als 1010 ist, dann...
                 {  
                  digitalWrite(ledOben, HIGH); // ...soll ledOben leuchten
                 }
             
             if (SensorWert < 1010) // Wenn der Wert kleiner als 1010 ist, dann...
                 { 
                  digitalWrite(ledOben, LOW);  // ...soll ledOben nicht mehr leuchten
                 }
             
             if (SensorWert > 20) // Wenn der Wert größer als 20 ist, dann...
                 {  
                  digitalWrite(ledUnten, LOW); // ...soll ledUnten leuchten
                 }
             
             if (SensorWert < 20) // Wenn der Wert kleiner als 20 ist, dann...
                 {  
                  digitalWrite(ledUnten, HIGH); // ...soll ledUnten nicht mehr leuchten
                 } 
}*/

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
int turn = 0;// trun counter
int buttonstate = 0; //button State Checker
int randomArray[100]; //stores die Inputs 
int inputArray[100];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/*void randomPixel()
{
    int pixelId = random(pixels.numPixels());

    pixels.setBrightness(10);

    if (pixelId == 0)
    {
        pixels.setPixelColor(pixelId , pixels.Color(255, 255,255));
        pixels.show();
        delay(delayval);
    }
    
    if (pixelId == 1)
    {
        pixels.setPixelColor(pixelId , pixels.Color(255, 0,255));
        pixels.show();
        delay(delayval);
    }
    
    if (pixelId == 2)
    {
        pixels.setPixelColor(pixelId , pixels.Color(0, 0,255));
        pixels.show();
        delay(delayval);
    }

    if (pixelId == 3)
    {
        pixels.setPixelColor(pixelId , pixels.Color(0, 255, 0));
        pixels.show();
        delay(delayval);
    }

    pixels.setPixelColor(pixelId, pixels.Color(0, 0, 0 ));
    pixels.show();
    delay(delayval);
}*/


void fail()//funktion wird benutzt wenn der Spieler die falsche eingabe macht, die vier LEDs leuchten gleichzeitig rot auf
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

            if(SensorWert == 1023)//Muss maximalwert angeben mit dem Joystick; mit dem größer als... oder kleiner als wert werden die meisten eingaben als Fehlermeldung angegeben
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

            if(SensorWert == 0)
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


            if(SensorWert == 1023)
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

            if(SensorWert == 0)
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



    //randomPixel();

    /*for(int i = 0; i < pixels.numPixels(); i++)
    {
        pixels.setPixelColor(i, LED[i]);
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(delayval); // Delay for a period of time (in milliseconds).

        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(delayval);
    }
}*/

