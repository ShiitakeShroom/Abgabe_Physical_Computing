# Dokumentation

Zu Beginn des Monats und hin zur Abgabe wollte ich einen Amazon Alexa mithilfe eines Arduinos und
einem 1Sheeld wie in diesem Tutorial nachbauen:

https://create.arduino.cc/projecthub/ahmedismail3115/arduino-based-amazon-echo-using-1sheeld-
84fa6f?ref=platform&amp;ref_id=424_trending___&amp;offset=53

Davon wurde mir jedoch schnell abgeraten und aufgrund meines Studentendaseins und der daraus
resultierenden fianzellen Lage wäre dieses Projekt auch nicht realisierbar gewesen.
![image](https://drive.google.com/uc?export=view&amp;id=1aa5OUiu2Ba9FkO2ouKvoy2v38dYOUvDQ)

Deswegen habe ich dann nach einem neuen Projekt gesucht.
Von einem Bekannten konnte ich mir zum Glück einige Bauteile leihen und daraus innerhalb
kürzester Zeit ein Ersatzprojekt verwirklichen:

![image](https://drive.google.com/uc?export=view&amp;id=1eI2QroJiqDm77rjcbEbb_S03Gp_wSA4x)

Das Sammelsurium der Teile enthielt unter anderem verschiedene Sensoren, LEDs, einen Joystick,
usw.

## Projekt

Unter den Teilen waren ein Joystick und eine Pixel-LED.
Das brachte mich auf die Idee ein &quot;Simons Says&quot; Spiel nachzubauen.

## Simons Says

Das Prinzip hinter dem Spiel ist es den Anweisungen von Simon zu folgen. In der elektrischen
Variante besitzt das Spiel vier verschieden farbige Knöpfe, die zufällig aufleuchten.
Ziel des Spieles ist es, in der durch farbiges Aufleuchten angezeigten Reihenfolge die der jeweiligen
Farbe zugeordneten Knöpfe zu drücken.
Wenn der Spieler die richtige Reihenfolge einhält, bekommt er eine positive Bestätigung; alle Lichter
leuchten auf und die nächste Runde beginnt.

Falls der Spieler jedoch den falschen Knopf erwischt, leuchten die Tasten in Rot auf und das Spiel
beginnt von vorne.
Mit jeder erfolgreich abgeschlossenen Runde wird zur Reihenfolge ein zusätzliches Licht hinzugefügt.

# Das Projekt
## Auseinandersetzung mit der Hardware

### Joy-Stick

Mit Hilfe dieses Tutorials habe ich dann getestet ob der Input über meinen Joystick in meinem Code
eine Antwort generiert.
Tutorial
https://funduino.de/nr-22-joystick-modul

### LED Pixel

Hier bestand die Übung darin das LED blinken zu lassen. Funktioniert soweit auch so mit dem Code.
Tutorial
https://arduinomodules.info/ky-009-rgb-full-color-led-smd-module/

### Kombinierte LED aktivieren

Der Besitzer der Teile half mir dann, die vier LEDs aneinander zu löten. Über den Code aus dem
vorherigen Tutorial wurden diese LEDs allerdings nicht mehr angesprochen.
Mit ein wenig Internet Recherche bin ich über die „Adafruit_Neopixel“ Liberay gestoßen.
Mit diesem Tutorial sowie dem dazugehrigen Code, gelang es mir, die LEDs in den ihnen
zugeordneten Farben in zufälliger Weise aufblinken zu lassen:
https://github.com/adafruit/Adafruit_NeoPixel

## Die Herausforderung
Nachdem ich mich mit den verschiedenen Komponenten auseinander gesetzt hatte, musste ich
einen Code schreiben mit dem ich den Joystick als Input und die LEDs als Output anspreche.

Als totaler Anfänger hatte ich allerdings überhaupt keine Ahnung wo ich anfangen sollte und die
Tutorials gaben mir nur einen Einblick, wie man die einzelnen Komponenten anspricht, nicht jedoch
wie man sie in Kombination nutzen kann.
Das Tutorial von faziefazie vermittelte mir dann eine Ahnung, wie ich den Code schreiben konnte.
Dank der dortigen Übungen war es dann recht einfach den Code auf die Komponenten anzupassen
und zu konfigurieren.

das Tutorial von _faziefazie_
https://www.instructables.com/Arduino-Simple-Simon-Says-Game/

## Der Aufbau der Schaltkreises

Schritt 1. Das Breadboard und das Arduino bereitstellen und den Ground und die 5V über Kabel an
das Breadboard anschließen
![image](https://drive.google.com/uc?export=view&amp;id=1yqWPTNw7CM-bDCXt3srCTicOBYDhPk3w)
![image](https://drive.google.com/uc?export=view&amp;id=1xBmRgFFi-__kPan4EJiY6euynfpXXgGO)

Schritt 2: Die Kabel an die Komponenten anschließen
![image](https://drive.google.com/uc?export=view&amp;id=1YffoRbdV1k2WwZmN-4REde0tiTDDPNgG)
![image](https://drive.google.com/uc?export=view&amp;id=1iqX59vGz8PmEdaVLbAVm-EwOlCekCJ01)
![image](https://drive.google.com/uc?export=view&amp;id=1WM5itZ1Iu6y0WhtUdG_SZaBnQB4mNssv)

Schritt 2.5: LEDs verkabeln und anschließen
![image](https://drive.google.com/uc?export=view&amp;id=1JTCkvKeNAIodpCqtLEJc4ydG12UiVLD3)
![image](https://drive.google.com/uc?export=view&amp;id=1GmpeywmBTSnVG1nGGMR8eedMGH0Mfp
0Y)

Am Output der LEDs ist ein Wiederstand verlötet
![image](https://drive.google.com/uc?export=view&amp;id=1sMm9My6rx2ILVAn0Xucrhsr54n5A78bR)

Das LED wird mit den Kabeln verbunden
![image](https://drive.google.com/uc?export=view&amp;id=1Z-FADF-P9d7N11qOIsT-7YT6uLR3JbnA)

Im Code spricht der PIN Nummer 4 die LEDs an.
![image](https://drive.google.com/uc?export=view&amp;id=1fhn0izGCTbqpU9B93PMdggElH7ckslRV)

Die Kabel mit denen die X- und Y-Achsen des Joysticks verbunden sind werden in die PINs A0 und A1
gesteckt.
![image](https://drive.google.com/uc?export=view&amp;id=1IJx95v9oKq4-GAuWfasjK-ugPl6vUbbe)

Wie auch die LED Kabel werden die Kabel des JoySticks mit dem Ground sowie mit dem 5 Volt PIN
verbunden.
![image](https://drive.google.com/uc?export=view&amp;id=1_BPiSSkGVgG63QeLUy8wCLkAW0_QOTsq)

Das ist der Endstand des Projektes.

## Wie funktioniert es
Mit der Hilfe des Codes funktioniert das Spiel.
Die Anleitung ist einfach. Wenn das Spiel bzw. das Arduino eingeschaltet wird, leuchtet es in den vier
voreingestellten Farben auf. Nach einem kurzen Delay fängt das erste LED an aufzuleuchten und
verlischt darauf hin. Hier muss der User dann mit dem Joystick eine Eingabe machen. Wenn der User
in die richtige Richtung drückt leuchtet das selbe LED auf. Wenn man die falsche Richtung drückt
leuchtet das jeweilige LED auf und kurz darauf blinken alle LEDs rot. Das Spiel beginnt von vorne.

## Reflektion zu dem Kurs und der Abgabe
Mit der Anmeldung zum Kurs wollte ich meine vorhandenen Coding Kenntnisse vertiefen und
allgemein mein Verständnis für Coding verbessern, was mir auch gelungen ist!
Hier habe ich mich zum ersten mal mit C/C++ auseinder gesetzt und gelernt, wie ich vorhandene
Codes für die mir gegebenen Komponenten umschreiben kann.
Mit den gewonnenen Erfahrungen möchte ich mich gerne mal an komplizierteren Projekten als
„Simon Says“ versuchen. Wer weiß? Vielleicht realisiere ich irgendwann doch noch die &quot;Aexa&quot;-Idee.
