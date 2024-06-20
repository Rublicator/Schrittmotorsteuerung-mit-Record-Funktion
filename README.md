# Schrittmotorsteuerung-mit-Record-Funktion

## Automatisieren mit Schrittmotoren ohne Programmierkenntnisse!

Version: 1.0 
Datum: Q2/2021

### Infos als Video: https://www.youtube.com/watch?v=FaB-Ntj-hgk

![Bild1Github](https://user-images.githubusercontent.com/88074525/128541693-08dbbe73-fd18-4f83-a0e8-5ca66fbf0264.png)
![Bild2Github klein](https://user-images.githubusercontent.com/88074525/128542330-0e08cf18-ec22-4a1b-a347-cdd9624a0e67.png)
***

Hier gibt es die [Software](https://github.com/Rublicator/Schrittmotorsteuerung-mit-Record-Funktion/archive/refs/heads/main.zip) zur "Rublicator Schrittmotorsteuerung mit Record Funktion".

### Eine detaillierte Projektbeschreibung zu der Schrittmotorsteuerung kann man [**hier**](https://github.com/Rublicator/Schrittmotorsteuerung-mit-Record-Funktion/files/6947505/Projekt_V1_Rublicator_Schrittmotorsteuerung.pdf) als Pdf herunterladen:
https://github.com/Rublicator/Schrittmotorsteuerung-mit-Record-Funktion/blob/main/Projektbeschreibung_V2_Rublicator_Schrittmotorsteuerung.pdf

Mit der Steuerung kann man Schrittmotoren komplett ohne Programmierkentnisse automatisieren.
Dazu wird die Schrittmotor-Bewegung händisch mit dem Record-Mode aufgenommen. Anschließend kann diese Bewegung mit dem Play-Mode wieder abgespielt werden. Selbst komplexeste Schrittmotor-Bewegungen können, ohne aufwändiges Programmieren, schnell und unkompliziert umgesetzt werden.

***
### Für das Projekt braucht man:
1x Kit: [**Rublicator Schrittmotorsteuerung mit Record-Mode**]

1x Arduino Nano

1x 12V 2A DC Netzteil

***
## Software:

### Schnelle und einfache Installation:

1.) Um die Software auf dem Arduino zu installieren muss
    auf dem PC dieses Programm [dieses Tool "Xloader"](https://github.com/binaryupdates/xLoader aufrufen, auf günen Knopf "code" drücken und als zip herunterladen) geöffnet werden.

2.) Wenn das Programm Xloader offen ist, wir der Arnuino Nano in den PC gesteckt, bei dem Reiter "Hex file"
    wird die Datei: "Einfache_Software_installation_Rublicator_Schrittmotorsteuerung_V1.1.ino.hex" (welche man hier auf der Seite als 
    Zip Datei herunterladen kann) ausgewählt. Unter dem Reiter Device wird dann "Duemilanove/nano(ATmega328) 
    ausgewählt. Bei "Baud rate" muss 115200 stehen und bei "COM port" wält man den USB Anschluss aus, wo der
    Arduino angeschlossen ist. (zu not alle ausprobieren bis ganz unten in XLoader "*** bytes uploaded" steht.
    Fertig! 
    
    Bei Misserfolg kann es sein, dass man je nach Arduino Nano board noch mit [dieser Software](https://www.wch.cn/downloads/file/5.html)
    den CH340 Treiber installieren muss. Dazu einfach die SETUP.exe öffnen und auf Install drücken. Dann   Schritt 2.) wiederholen und
    der upload der Software gelingt.
    
    
***

### Installation mit der Arduino IDE:

1.) Um die Software auf den Arduino zu Installieren, muss
man die Arduino IDE [hier](https://www.arduino.cc/en/software) herunterladen.

2.) Anschließend muss die Datei, welche [hier](https://github.com/Rublicator/Schrittmotorsteuerung-mit-Record-Funktion/archive/refs/heads/main.zip) heruntergeladen wurde mit der Arduino IDE geöffnet werden.

3.) Jetzt muss man die "Rublicator_Schrittmotorsteuerung_V1.1.ino.hex" Datei mit der Arduino IDE öffnen und hochladen.
    Dazu müssen noch die sogenannten "libarys" in der Arduino Software installiert werden.
    Weitere Schritte stehen in der Datei selber drin oder können in dieser Projektbeschreibung nachgelesen werden. 



***
(C) Copyright by Rublicator Innovation, Inhaber Ruben Rodermann

Rechtlicher Hinweis: 
*Die Software darf ausschließlich für den privaten Gebrauch verwendet werden. 
Eine Weiterverbreitung ist in jeglicher Art verboten. Die komerzielle Nutzung 
sowie Verbreitung der Software ist verboten. Dies gilt auch, wenn die Software 
nur verändert wurde. Alle Rechte liegen ausschließlich bei dem Urheber.*

