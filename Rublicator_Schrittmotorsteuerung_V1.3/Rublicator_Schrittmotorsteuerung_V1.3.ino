/* (C)Copyright by Rublicator Innovation Inhaber Ruben Rodermann
 *  Rublicator Schrittmotorsteuerung mit Record Funktion V1
 *  Version: 1.3 (Q1/2024)
 *    
 *    
 *  Rechtlicher Hinweis: 
 *  Die Software darf ausschließlich für den privaten Gebrauch verwendet werden. 
 *  Eine Weiterverbreitung ist in jeglicher Art verboten. Die komerzielle Nutzung 
 *  sowie Verbreitung der Software ist verboten. Dies gilt auch, wenn die Software 
 *  nur verändert wurde. Alle Rechte liegen ausschließlich bei dem Urheber. 
 *  
 * Installation auf dem Arduino:
 * 1.) Werkzeuge -> Board: "Arduino Nano" auswählen
 * 2.) Werkzeuge -> Prozessor: ATmega328p (old Bootloader)
 * 3.) Sketch -> Bibliothek einbinden -> "Bibliothek verwalten..." öffnen
 * 4.) Im Fenster: "Adafruit GFX" suchen und "Adafruit GFX Libary" Version: 1.10.10 installieren
 * 5.) Fenster erneut öffnen wie in 4.), "SSD1306" suchen und 
 *     "Adafruit SSD1306 Libary" Version 2.4.5 installieren
 * 6.) Arduino aus dem Mainboard entfernen, per USB mit dem PC verbinden
 * 7.) Werkzeuge -> Port: COM... (den angezeigten Auswählen)
 * 8.) Den Pfeil, welcher nach rechts zeigt im runden Icon (oben links)"Hochladen" drücken 
 * 
 * 
 * 
 * Neu bei Version V1.2 "1028 - analogRead(Potiometer)": 1028 statt 1023, damit der Wert niemals 0 wird! 
 * 
 *  --- Fertig! Erfolgreich wenn die Meldug "Hochladen abgeschlossen" kommt. (untere/linke Ecke) ---
 *  Bei Fragen: "ruben.r.rodermann82@gmail.com" einfach kontaktieren!
 *  
 *  
 */ 



////////////////////////////////////////////////////////// Einstellungen anpassbar //////////////////////////////////////////////////////////

uint16_t Speed_Setting = 200; // Gibt den Geschwindigkeitsbereich des Motors an: 50 = langsam; 1000 = schnell
uint8_t Beschleunigung = 6; // Gibt die Beschleunig des Motors an: 1 = sehr schnelle Beschleunigung; 15 = sehr langsame Beschleunigung;

////////////////////////////////////////////////////////// Einstellungen anpassbar //////////////////////////////////////////////////////////




// Ist dass Logo als Bitmap
 const unsigned char PROGMEM logo [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x3f, 0xf0, 0x00, 0x30, 0x00, 
  0x00, 0x1e, 0x00, 0x3f, 0xf0, 0x00, 0x78, 0x00, 0x00, 0x3f, 0x00, 0xff, 0xfe, 0x00, 0xfc, 0x00, 
  0x00, 0x7f, 0x87, 0xff, 0xfe, 0xe1, 0xfe, 0x00, 0x00, 0xff, 0xdf, 0xff, 0xff, 0x7b, 0xff, 0x00, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x80, 0x00, 0xff, 0xff, 0xfe, 0xff, 0xcf, 0xff, 0x00, 
  0x00, 0x7f, 0xff, 0xc0, 0x07, 0xef, 0xfe, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x01, 0xe7, 0xfc, 0x00, 
  0x00, 0x1f, 0xfc, 0x00, 0x00, 0x77, 0xf8, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x33, 0xf8, 0x00, 
  0x00, 0x1f, 0xe0, 0x00, 0x00, 0x13, 0xf8, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x0b, 0xfc, 0x00, 
  0x00, 0x7f, 0xc3, 0xe0, 0x3e, 0x01, 0xfe, 0x00, 0x00, 0x7f, 0x83, 0xf8, 0x3f, 0x85, 0xfe, 0x00, 
  0x00, 0x7f, 0x83, 0x18, 0x31, 0x81, 0xfe, 0x00, 0x00, 0xff, 0x03, 0x18, 0x31, 0x83, 0xff, 0x00, 
  0x00, 0xff, 0x03, 0xf8, 0x3f, 0x80, 0xff, 0x00, 0xff, 0xfe, 0x03, 0xe0, 0x3e, 0x00, 0xff, 0xff, 
  0xff, 0xfe, 0x03, 0x30, 0x33, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x03, 0x18, 0x31, 0x80, 0xff, 0xff, 
  0xff, 0xfe, 0x03, 0x18, 0x31, 0xc0, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0xff, 0xfe, 0x80, 0x07, 0xe0, 0x00, 0xff, 0xff, 0x00, 0xfe, 0x80, 0x07, 0xf0, 0x00, 0xff, 0x00, 
  0x00, 0xff, 0x40, 0x07, 0x30, 0x01, 0xff, 0x00, 0x00, 0x7f, 0x40, 0x07, 0x30, 0x01, 0xfe, 0x00, 
  0x00, 0x7f, 0xa0, 0x07, 0xf0, 0x01, 0xfe, 0x00, 0x00, 0x7f, 0xb0, 0x07, 0xe0, 0x01, 0xfe, 0x00, 
  0x00, 0x3f, 0xd8, 0x07, 0x60, 0x0b, 0xfc, 0x00, 0x00, 0x3f, 0xec, 0x07, 0x30, 0x03, 0xfc, 0x00, 
  0x00, 0x1f, 0xf6, 0x07, 0x30, 0x13, 0xf8, 0x00, 0x00, 0x1f, 0xfb, 0x82, 0x00, 0x77, 0xf8, 0x00, 
  0x00, 0x3f, 0xfd, 0xf0, 0x08, 0xf7, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0x3f, 0xc3, 0xef, 0xfe, 0x00, 
  0x00, 0xff, 0xff, 0xe0, 0x0f, 0xef, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x80, 
  0x03, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x80, 0x00, 0xff, 0x8f, 0xff, 0xff, 0xf9, 0xff, 0x00, 
  0x00, 0x7f, 0x03, 0xff, 0xfc, 0xc0, 0xfe, 0x00, 0x00, 0x3e, 0x00, 0x7f, 0xf8, 0x00, 0x7c, 0x00, 
  0x00, 0x1c, 0x00, 0x3f, 0xf0, 0x00, 0x38, 0x00, 0x00, 0x08, 0x00, 0x3f, 0xf0, 0x00, 0x10, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00
};


// Ist dass Motor Icon als Bitmap
const unsigned char Motor [] PROGMEM = {
  // 'motor bild, 50x30px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 
  0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0xff, 
  0x80, 0x7e, 0x00, 0x00, 0x7b, 0xff, 0xff, 0x80, 0x5f, 0x00, 0x00, 0xf3, 0x00, 0x01, 0x80, 0x4f, 
  0x00, 0x00, 0xe3, 0xff, 0xff, 0x80, 0x47, 0x00, 0x00, 0xe3, 0x00, 0x01, 0x80, 0x47, 0x00, 0x00, 
  0xe3, 0x00, 0x01, 0x80, 0x47, 0x00, 0x00, 0xe3, 0xff, 0xff, 0x80, 0x47, 0x00, 0x7f, 0xe3, 0xff, 
  0xff, 0x80, 0x47, 0x00, 0x7f, 0xe3, 0x00, 0x01, 0x80, 0x47, 0x00, 0xff, 0xe3, 0x00, 0x01, 0x80, 
  0x47, 0x00, 0xf0, 0x23, 0xff, 0xff, 0x80, 0x47, 0x00, 0xff, 0xe3, 0xff, 0xff, 0x80, 0x47, 0x00, 
  0xff, 0xe3, 0x00, 0x01, 0x80, 0x47, 0x00, 0x7f, 0xe3, 0x00, 0x01, 0x80, 0x47, 0x00, 0x00, 0xe3, 
  0xff, 0xff, 0x80, 0x47, 0x00, 0x00, 0xe3, 0xff, 0xff, 0x80, 0x47, 0x00, 0x00, 0xe3, 0x00, 0x01, 
  0x80, 0x47, 0x00, 0x00, 0xe3, 0xff, 0xff, 0x80, 0x47, 0x00, 0x00, 0xf3, 0xff, 0xff, 0x80, 0x47, 
  0x00, 0x00, 0xfb, 0x00, 0x01, 0x80, 0x4f, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x80, 0x5e, 0x00, 0x00, 
  0x3f, 0xff, 0xff, 0x80, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 
  0xff, 0xff, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00
};


// Libarys 
#include <EEPROM.h>
#include <Wire.h>  // I2C EEprom


//////////////////// Display //////////////////////
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Display Breite 128 Pixel
#define SCREEN_HEIGHT 64 // Display Höhe 64 Pixel

// SSD1306 Ic start (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//////////////////// Display //////////////////////




// Definiert an welchen Pins die Taster angeschlossen sind
#define START_STOP 2
#define Drehrichtung 4
#define Record_Taste 7
#define Play_Taster 8
#define Manuell_Taster 9
#define Trimmung_Taster 10


#define Potiometer A2     //Poti um die Geschwindigkeit zu verstellen
#define Poti2_Endschalter_Pin A6 // Pin von den externen Endschaltern und Poti2 (Gecshwindigkeitsbereich)

#define PLAY_START_Out 13 //Generiert ein Ausgangssignal an PLAY_START Anschluss, um z.B. ein 2 Steuerung zu aktivieren
#define PLAY_START_In A7  //Input um Play / record zu starten


// LEDs Pinbelegung
#define brightness_red 15   // Helligkeit der RGB LEDS
#define brightness_blue 15  // Helligkeit der RGB LEDS
#define brightness_green 15 // Helligkeit der RGB LEDS

#define RGB_red 5
#define RGB_blue 3 // Blau hat Tim2 wie tone() -> kein Blau während Motor dreht
#define RGB_green 6

#define Start_Stop_LED A1 // Anschluss Start Stopp LED
#define DIR_LED A0 // Anschluss Direction LED

#define Puls_Treiber 11
#define Direction_Treiber 12
// LEDs Pinbelegung


// DIP Schalter Pins
#define DIP_1 A3 // 0 = Im loop Play abspielen, 1 = Auf Externen taster warten -> dann erst abspielen
#define DIP_2 0  // Hat keine Funktion / frei (NC)
#define DIP_3 1  // Beschleunigung: 1 = OFF;  0 = ON;




//////////////////////////////////// Allgemeine Variablen ////////////////////////////////////
uint8_t Beschleunigung_aktiv = 0; // DIP3 auslesen: 0 = aktiv, 1= deaktiviert
uint8_t Trimmmodus_aktiv = 0; // beendet loop von Play() wenn im Trimmungs Modus ist

long LastTimerValue[12]; //Arrays Speichern den letzten Wert von millis(), damit z.B. Tastendücke nicht mehrfach gewertet werden
long MaxPressTime = 800; // Maximaler Länge des Tastendrucks, bis als 2. Tastendruck gewertet wird

long Record_Start_Time; // Speichert den millis() wert, um verstrichene Zeit seit Record / Play Startzu berechnen
long Play_Start_Time;

uint16_t Poti2_Endschalter = 0; // PIN A6 liest Poti2 und Enschalter aus, Wert wird hier gespeichert
uint16_t V_Play; //Berechnet geschwindigkeitsbereich aus Speed_Setting und Poti2

uint8_t Trimonoff; //Wird Play vom Trimmodus aufgerufen?
uint8_t DIP_123 = 0; // Speichert DIP Schalter 00000111; 3 Bits = An/Aus Zustand
//////////////////////////////////// Allgemeine Variablen ////////////////////////////////////





//////////////////////////////////// EEprom - Speicherung von Record ////////////////////////////////////

////////////////// Internes Eeprom Speicherverfahren Info: //////////////////

// 0 -990 Speichert Motorbewegung
// 993 Poti2 letzter Wert für den Geschwindigkeitsbereich
// 994 Max_Adresse (höchstens 500 bei internem EEprom)
// 995 Max_Adress, wenn Größe als 8 bit (Externes EEprom)
// 996 = Direction & Start_Stop während Manueller Modus -> Neustart 
// 997 Start_Stop_alt im Manuellen Modus
// 998 Speichert den letzen Modus (bei Reset) 0 kein Modus, 1 Play(), 2 Manuell
// 999 Play ohne Trimmung = 0; Play bereits getrimmt = 1;

////////////////// Internes Eeprom Speicherverfahren Info: //////////////////

uint8_t EEdeviceaddress = 0x50; // 80 = 0x50 , Adresse vom externen EEprom
uint8_t Hardware_part_EEprom = 0; // Erkennt externes Eeprom: 0 = nichts, 1 = EEprom erkannt
uint8_t Extern_Eepromaviable = 0; // Prüft kontinuierlich ob EEprom angeschlossen, 0 = ok; >0 = Fehler -> zeigt auf dem Display den Status an
uint8_t Max_play_time; // Speichert die maximale Dauer von Play für das Display in Sekunden

uint16_t Max_Adresse; // max. 500 bei internem EEprom,16000 Externes für Play die Anzahl der zulesenden Eeprom Werte (Damit Ende bekannt ist)

uint8_t Motor_Status = 0; // 1 = Start, 0= Stopp
uint8_t Start_Stop_alt =0; // Speichert den zuletzt gesetzten Wert der Start Stopp Taste
uint8_t PLAY_START_Out_State; // Status vom Ausgangssignal Anschluss "PLAY_START"
uint8_t Drehrichtung_alt = 0; // Speichert die letzte Drehrichtung

uint8_t letzer_Modus; // Wenn Arduino ausgeht, geht automatisch in den letzte Modus
uint8_t Current_Mode; // Hat den aktuelellen Modus drin: 0 = nichts, 1 = play, 2 = Manuell, 3 = Record,  4 = Trimmung
uint8_t Manual_Mode_Start; // Wird auf 1 gesetzt, wenn das Menü starten, damit der Motor immer beschleunigt wird

//EEprom Bytes decodieren vom Eintrag (für Play)
uint8_t Dir; // liest die Drehrichtung aus
uint8_t PLAY_START_Out_EEprom; // Status des externen Ausgangs "PLAY_Start"
uint16_t Poti; // Wert der Geschwindigkeit
uint16_t Zeit; // Zeit des Ereignisses in 100 Ms seit start


//////////////////////////////////// EEprom - Speicherung von Record ////////////////////////////////////




void setup() 
{
 Wire.begin();
  
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 OLED_Refresh(1);
 delay(2000); // Rublicator Logo 2s anzeigen

////////////////// Initialisierung der Pins //////////////////
 pinMode(Record_Taste, INPUT_PULLUP); 
 pinMode(Drehrichtung, INPUT_PULLUP); 
 pinMode(START_STOP, INPUT_PULLUP); 
 pinMode(Play_Taster, INPUT_PULLUP);
 pinMode(PLAY_START_In, INPUT);

 pinMode(Manuell_Taster, INPUT_PULLUP);
 pinMode(Trimmung_Taster, INPUT_PULLUP);
 
 pinMode(Potiometer, INPUT); // Für Geschwindigkeit
 pinMode(Poti2_Endschalter_Pin, INPUT); // Externes Pori2 geschwindigkeitsbereich
  
 pinMode(PLAY_START_Out, OUTPUT); // Ausgang für Daten Ausgabe

 pinMode(RGB_red, OUTPUT);
 pinMode(RGB_green, OUTPUT);
 pinMode(RGB_blue, OUTPUT); 

 pinMode(DIP_1, INPUT);
 pinMode(DIP_2, INPUT);
 pinMode(DIP_3, INPUT);
     
 pinMode(Start_Stop_LED, OUTPUT);
 pinMode(DIR_LED, OUTPUT);

 pinMode(Puls_Treiber, OUTPUT); // Ausgang für den Motor Treiber
 pinMode(Direction_Treiber, OUTPUT);
////////////////// Initialisierung der Pins ////////////////// 

 
 
 Max_Adresse = (EEPROM.read(995) & 255) << 8 | EEPROM.read(994); // Lese Wert der Maximalen Adresse vom letzten Record
 letzer_Modus = EEPROM.read(998); // letzter Modus auslesen
                                                                                           
 delay(10); // Nach EEprom Operation kurz Warten -> Manchmal entstehen sonsr Fehler
 DIP_123 = ((digitalRead(DIP_3) << 2) | DIP_123); // Beschleunigung ON / OFF
 DIP_123 = ((digitalRead(DIP_2) << 1) | DIP_123); // Keine Belegung
 DIP_123 = (digitalRead(DIP_1) | DIP_123); // Play loop ON OFF
 Beschleunigung_aktiv = digitalRead(DIP_3); // Becshleunigung (DIP3) aktivieren? 680 Ohm Widerstand R17

 
 

/////////////// Erkennung der angeschlossenen I2C Geräte ///////////////
 for(int i2c_scan = 0; i2c_scan < 127; i2c_scan++)
 {
  static uint8_t Scan_error = 0; // Wenn != 0 ist -> Fehler -> kein Gerät mit der Adresse
  Wire.beginTransmission(i2c_scan);
  Scan_error = Wire.endTransmission(); //error_scan hat die Asresse gespeichert

  if(Scan_error == 0) // Gerät gefunden
   {
    if(i2c_scan == 0x50) // kann später erweitert werden
     {
      Hardware_part_EEprom = 1; // Externes EEprom erkannt
     }
   }
 }
/////////////// Erkennung der angeschlossenen I2C Geräte ///////////////


if(Hardware_part_EEprom == 1) // 1 mal Blinken = Extension Eeprom erkannt
{
  RGB_LED(0,0,50);
  delay(1000);
  RGB_LED(0,0,0);
 }

// Ermittlung des Geschwindigkeitsbereiches durch Poti2 und Speed_Setting
V_Play = (Speed_Setting * Potiauswertung(10)); 


Serial.begin(9600); //Erst am Ende, sonst beeinflusst DIP3

GetEepromValues(Max_Adresse);
Max_play_time = Zeit/10; 
OLED_Refresh(0);

}







void loop() 
{


///////////////////////////////// Erkennung ob ein Modus ausgewählt wurde ///////////////////////////////// 

// Im Record-Mode
 if(digitalRead(Record_Taste) == LOW && (LastTimerValue[1] + MaxPressTime) <  millis())
  {
   Current_Mode = 3;
   OLED_Refresh(0);
   
   LastTimerValue[1] = millis();
   Record();
   Current_Mode = 0;
   OLED_Refresh(0);
  }


// Im Trim-Mode
 if(digitalRead(Trimmung_Taster) == LOW && (LastTimerValue[5] + MaxPressTime) <  millis())
  {
   Current_Mode = 4;
   OLED_Refresh(0);
   
   LastTimerValue[5] = millis();
   RGB_LED(50,5,0);
   Trimmung();
   RGB_LED(0,0,0);
   Current_Mode = 0;
   OLED_Refresh(0);
  }


// Im Play-Mode
 if((digitalRead(Play_Taster) == LOW && (LastTimerValue[4] + MaxPressTime) <  millis()) || letzer_Modus == 1)
  {
   Current_Mode = 1;
   OLED_Refresh(0);
   
   EEPROM.write(998,1); // Arduino Reset: soll er automtisch in den letzten Modus wechseln
   LastTimerValue[4] = millis();
 
   if(Max_Adresse <= 1) // Wenn nichts aufgenommen wurde:
    {
     int i;
     
     for(i = 0; i<=15; i++)
      {
       RGB_LED(0,50,0);
       delay(100);
       RGB_LED(0,0,0);
       delay(100);
       LastTimerValue[4] = millis();
      }
     
    }
   
   else
    {
     RGB_LED(0,50,0);
     Play();
     RGB_LED(0,0,0);
    }
    letzer_Modus = 0; // Damit nur beim Start der Modus vom EEprom übernommen wird
  
   Current_Mode = 0; 
   OLED_Refresh(0);
     
   EEPROM.write(998,0); 
  }


// Im Manual-Mode
 if((digitalRead(Manuell_Taster) == LOW && (LastTimerValue[6] + MaxPressTime) <  millis()) || letzer_Modus == 2)
  {
   Current_Mode = 2;
   Manual_Mode_Start = 1; // Damit, immer wenn man ins Menü springt, der Motor beschleunigt wird.
   OLED_Refresh(0);
   
   EEPROM.write(998,2); // Arduino Reset: soll er automtisch ins letzte Menu gehen
     
   LastTimerValue[6] = millis();
   RGB_LED(50,50,0);
   Normaler_Modus();
   RGB_LED(0,0,0);
   letzer_Modus = 0; // Damit nur beim Start der Modus vom EEprom übernommen wird
   
   EEPROM.write(998,0); // Geht aus dem Menu festhalten (bei RESET wichtig)
   Current_Mode = 0;
   Manual_Mode_Start = 0; 
   OLED_Refresh(0);
  }  


///////////////////////////////// Erkennung ob ein Modus ausgewählt wurde ///////////////////////////////// 



//Serial.println("loop"); // Rückgabe, dass Arduino läuft

}











////////////////////////////////////////////////////////// Bewegung aufnehmen //////////////////////////////////////////////////////////
void Record(void)
{ 
 
 EEPROM.write(999, 0); // Stellt Trimmung fallls noch an wieder aus
  
 Max_Adresse = 0; // Setzt die Anzahl der Eintäge au 0
 Start_Stop_alt = 0; // Am Anfang soll der Motor immer stehen
 Drehrichtung_alt = 0; // Dir reset
 
 Record_Start_Time = millis(); // Wird später von der Zeit abgezogen (Zeit auf 0 setzten)

 uint8_t Drehrichtung_alt_a = 0; // Für Beschleunigung benötigt
 uint8_t whilec = 0; // Wartet auf Externes Signal 
 uint8_t Neue_Eingabe = 0; // Prüft ob Dir,Start/Stop, oder Poti vereändert wurde
 uint16_t Potiauswertung_alt = 0; // Prüft ob Poti verändert wurde
 
 uint8_t REC_LED_Status;//Status der REC LED (wegen blinken)
 

// Hardware Beschleunigung:
 uint8_t Drehrichtung_Read = 0; // letzter Drehrichtungs Wert
 uint8_t START_STOP_Read;       // letzter Start/Stop Wert
 uint8_t Start_Stop_alt_a = 0;  // Für Beschleunifung nach Stopp
 
 uint16_t HB_Counter = 51;
 uint16_t Potiauswertung_Read; // letzter Poti Wert


 PLAY_START_Out_State = 0; // Ausgang am Anfang immer ausschalten.
 digitalWrite(PLAY_START_Out, PLAY_START_Out_State); // State Out am Anfang immer aus
 

 digitalWrite(Direction_Treiber, Drehrichtung_alt); // Damit nicht von Manuellen Modus beeinflusst wird
 digitalWrite(DIR_LED, Drehrichtung_alt);

 EEPROM.write(994, 0); // Reset der alten Adresse
 EEPROM.write(995, 0); // Reset der alten Adresse




///////////////////////////////// Warte auf Impuls vom externen Taster / Signal (später für die Kopplung mehrerer Boards nötig) /////////////////////////////////

 while((digitalRead(Record_Taste) == HIGH || (LastTimerValue[1] + MaxPressTime) >  millis()) && whilec == 0 && Trimmmodus_aktiv == 0) // Warte auf erstes Signal
     {
      Poti2_Endschalter = analogRead(Poti2_Endschalter_Pin); // 0-80 = Poti, >= 1000 = Endschalter
      OLED_Refresh(0);

      if(analogRead(PLAY_START_In) >= 900)// Maximal 1023, 900 um Störungen zu vermeiden
        {
         //Info: Durchlaufanzahl = 1;
      
         noTone(Puls_Treiber);
         whilec = 1; // Nur am Anfang einmal diese Funktion aufrufen
      
      
       } else
       {
        static unsigned long millis_old = millis();

        if((millis()- millis_old) > 1000) // LEDs blinken rot -> warte auf Startsignal
        { 
         RGB_LED(50,0,0);
         delay(100);
         RGB_LED(0,0,0);
         millis_old = millis();
        } 
      }
     }
 
    
 RGB_LED(50,0,0);
 whilec = 1;
 Record_Start_Time = millis(); // Wird später von der Zeit abgezogen
 LastTimerValue[1] = 0; //Damit falls durch 2 Druck der Record Taste nicht in 2 While Schleife geht, sondern beendet
    
///////////////////////////////// Warte auf Impuls vom externen Taster / Signal (später für die Kopplung mehrerer Boards nötig) /////////////////////////////////





 
 while(digitalRead(Record_Taste) == HIGH || (LastTimerValue[1] + MaxPressTime) >  millis()) // Haupt While Schleife, bei Record aktiv
   {
    
    if(LastTimerValue[9] < millis()) // LED im Sekunden Takt rot blinken lassen
     {
      RGB_LED((50*REC_LED_Status),0,0);
      REC_LED_Status = !REC_LED_Status;
      LastTimerValue[9] = millis() +1000;
     }



// ---Hardware Beschleunigung--- Das Lesen der Eingänge kostet viel Zeit und muss nicht bei jedem Durchlauf passieren (alle 50 mal) //
    if(HB_Counter > 300) // Sorgt dafür, dass nur bei jedem 20 Puls Werte erneuert werden, spart Zeit
     {
      HB_Counter = 0;
      Drehrichtung_Read = digitalRead(Drehrichtung);
      START_STOP_Read = digitalRead(START_STOP);
      
      Poti2_Endschalter = analogRead(Poti2_Endschalter_Pin); // Auswertung 0-750 = Poti, >= 900 = Endschalter
      OLED_Refresh(0); //Oled Refresh

      
      if(Hardware_part_EEprom == 0) // Suche passende Poti auflösung je nach EEprom, internes 7-Stufen, externes 30-Stufen
      {
       Potiauswertung_Read = Potiauswertung(0);
      } else
      {
       Potiauswertung_Read = Potiauswertung(2);
      }



    if(Drehrichtung_Read == 0 && (LastTimerValue[2] + MaxPressTime) < millis() )// 1. Drehrichtung
     {

      Drehrichtung_alt_a = 1; // aktiviert Beschleunigung, weil Dir geändert wurde
      Drehrichtung_alt = !Drehrichtung_alt;
      LastTimerValue[2] = millis();
      digitalWrite(DIR_LED, Drehrichtung_alt);
      Neue_Eingabe = 1;
      }
      


    if(START_STOP_Read == 0 && (LastTimerValue[3] + MaxPressTime) <  millis() )// 2. START_Stop Zustand
     {
      Start_Stop_alt_a = Start_Stop_alt; // Für beschleunigung
      Start_Stop_alt = !Start_Stop_alt;
      LastTimerValue[3] = millis();
      Neue_Eingabe = 1;
     }


    if(digitalRead(Trimmung_Taster) == LOW && (LastTimerValue[10] + MaxPressTime) <  millis() && Hardware_part_EEprom  == 1) // Trimm Taster hier für "Play_Start" Ausgang Aktivierung
      { 
       LastTimerValue[10] = millis();
       PLAY_START_Out_State = !(B00000001 & PLAY_START_Out_State);
       digitalWrite(PLAY_START_Out, PLAY_START_Out_State);
       Neue_Eingabe = 1;     
      }

    
    if(Potiauswertung_alt != Potiauswertung_Read ) // Prüft ob geschwindigkeit (Poti) verändert wurde
     {
      Potiauswertung_alt = Potiauswertung_Read;
      Neue_Eingabe = 1;
     } 
    }
    
    HB_Counter++; 
// ---Hardware Beschleunigung--- Das Lesen der Eingänge kostet viel Zeit und muss nicht bei jedem Durchlauf passieren (alle 50 mal) //
 
  

    if(Neue_Eingabe == 1) // Wenn ein Wert verändert wurde, dann neuer Eeprom Eintrag
     {
      Neue_Eingabe = 0;
      Max_Adresse += 1;
      WriteEepromValues(Max_Adresse);
     }



////////////////////////////// Beschleunigung des Motors ////////////////////////////////////

    if(Poti2_Endschalter <= 900) // Prüft, dass kein Endschalter berührt wird
     {
 

      if(Start_Stop_alt_a == 1 &&Start_Stop_alt == 1 && Drehrichtung_alt_a == 1 && Beschleunigung_aktiv == 0) // Nur Wenn Motor sich bewegt, damit bei Stopp Motor nicht unnötig hoch beschleunigt
      {

       Drehrichtung_alt_a = 0; // Deaktiviert Beschleunigung, damit beim nächsten Durchgang nicht wieder beschleunigt

       for(int i = sqrt (Potiauswertung_Read); (i*i) > 0; i--) // Motor Entschleunigen
         {
          tone(Puls_Treiber, (i*i));
          delay(Beschleunigung);
         }

       digitalWrite(Direction_Treiber, Drehrichtung_alt); // Neue Drehrichtung aktualisieren

        
       for(int i = 0; (i*i) <  Potiauswertung_Read; i++) // Motor beschleunigen
         {
          tone(Puls_Treiber, (i*i));
          delay(Beschleunigung);         
         }
       }

      digitalWrite(Direction_Treiber, Drehrichtung_alt); // Neue Drehrichtung aktualisieren, auch wenn Beschkeunigung aus ist




      if(Start_Stop_alt_a == 1 && Start_Stop_alt == 0 && Beschleunigung_aktiv == 0) // Vor Run muss der Motor, wenn er steht beschleunigt werden
        {
      
          for(int i = sqrt (Potiauswertung_Read); (i*i) > 0; i--) // Motor Entschleunigen
             {
              tone(Puls_Treiber, (i*i));
              delay(Beschleunigung);
             }

          Start_Stop_alt_a = 0; // deaktivieren
        }


  

      if(Start_Stop_alt_a == 0 && Start_Stop_alt == 1 && Beschleunigung_aktiv == 0) // Vor Start muss der Motor, wenn er steht, beschleunigt werden
        {
         Drehrichtung_alt_a = 0; // Deaktiviert Beschleunigung, um doppelte Beschleunigung bei Start &  Dir änderung zu vermeiden
         digitalWrite(Direction_Treiber, Drehrichtung_alt); // Drehrichtung aktualisieren

       
         for(int i = 0; (i*i) < Potiauswertung_Read; i++) // Motor Beschleunigen
            {
             tone(Puls_Treiber, (i*i));
             delay(Beschleunigung);
            }

        Start_Stop_alt_a = 1; // deaktivieren
    
        }




      if(Start_Stop_alt == 1) // Wenn Motor Aktiviert wurde: Run
        {
         tone(Puls_Treiber, Potiauswertung_Read); // Generiert Pulse in dem der Timer auf den Output gesetz wird
         digitalWrite(Start_Stop_LED, LOW);
        }
    
      else
       {
        noTone(Puls_Treiber);
        digitalWrite(Start_Stop_LED, HIGH);
        }


    }

    else
    {
     noTone(Puls_Treiber); 
     OLED_Refresh(0); 
    }


    if((Max_Adresse >= 495 && Hardware_part_EEprom == 0) || (Max_Adresse >= 15000 && Hardware_part_EEprom == 1) ) 
    // Damit nicht in Eeprom Register 990 reingeschrieben wird, wo andere wichtige Werte gespeichert sind, Speicher = voll
    //Externe EEprom: 64.000 kbyte / 4 (1 Datensatz) = 16000 Einträge (maximal in 1,5 Stunden Aufnahmezeit)
     {
      uint8_t i;
      
      for(i = 0; i<=40; i++)
       {
        RGB_LED((50*REC_LED_Status),0,0);
        delay(50);
        RGB_LED(0,0,0);;
        delay(50);
       }
       noTone(Puls_Treiber);
      return; // Beende Record()
    }
   }
 
////////////////////////////// Beschleunigung des Motors ////////////////////////////////////




 Max_Adresse += 1; // Damit auch der letzte Wert gespeichert wird 
 WriteEepromValues(Max_Adresse); 
  
 EEPROM.write(994, (Max_Adresse & B11111111)); // Speichert ersten 8 Bit der neuen Eintägeanzahl
 EEPROM.write(995, (Max_Adresse >> 8)); //Speichert 8-16 bit

 noTone(Puls_Treiber);
 RGB_LED(0,0,0);
 LastTimerValue[1] = millis();

 delay(15);
 GetEepromValues(Max_Adresse); // Refresh Display
 Max_play_time = (Zeit/10); // Durch 10, da in 100Ms angebenen -> Sekunden

 PLAY_START_Out_State = 0; // Am ende immer aus
    
 digitalWrite(PLAY_START_Out, PLAY_START_Out_State); // State Out am Anfang immer aus
 digitalWrite(DIR_LED, LOW);
 digitalWrite(Direction_Treiber, LOW);
 digitalWrite(Start_Stop_LED, LOW);
 delay(1000); // Kurze Pause, damit EEprom Zeit hat.
 return;
}
////////////////////////////////////////////////////////// Bewegung aufnehmen //////////////////////////////////////////////////////////








////////////////////////////////////////////////////////// Bewegung abspielen //////////////////////////////////////////////////////////
void Play(void)
{
 Trimonoff = EEPROM.read(999); // Wurde schoneinmal eine Trimmung vorgnommen?
  
 uint8_t HB_Counter = 0xFF; // = 256 Damit beim Start direkt die Daten gelesen werden (Hardware Beschleunigung)
 uint16_t Poti_alt = 0;
 uint16_t Durchlaufanzahl = 1;
 uint16_t aktuelleZeit; // 12bit = max 409.5 Sekunden
  
 uint8_t Dir_old = 0; // alte Drehrichtung abspeichern, 1 ,da Bei Record start LED immer aus, sprich dir = 0 ist
 uint8_t Ersterd = 0; // Wird nachher auf 1 gesetzt, damit der erste Dir Wert eingelesen wird und am Anfang die Richtung richtig ist

 uint8_t whilec = 0;

 PLAY_START_Out_State = 0; // Ausgang am Anfang immer aus
 digitalWrite(PLAY_START_Out, PLAY_START_Out_State); // State Out am Anfang immer aus





// Starten, warte auf Play Input oder nicht (DIP Einstellung)

 if((DIP_123 & B00000001) == 1) // Wenn Loop Modus aus ist -> warte auf Startsignal
   {
      
     
    while((digitalRead(Play_Taster) == HIGH || (LastTimerValue[4] + MaxPressTime) >  millis()) && whilec == 0 && Trimmmodus_aktiv == 0) // Warte auf erstes Signal
    {
     Poti2_Endschalter = analogRead(Poti2_Endschalter_Pin); // 0-750 = Poti, >= 900 = Endschalter
     OLED_Refresh(0);
      
     if(analogRead(PLAY_START_In) >= 900)// Maximal 1023, 900 um Störungen zu vermeiden
       {
        Durchlaufanzahl = 1;
        noTone(Puls_Treiber);
        whilec = 1;
      
       } else
       {
        static unsigned long millis_old = millis();

        if((millis()- millis_old) > 1000) // LED Blinken -> warte auf Startsignal
        {
         
        RGB_LED(0,30,0);
        delay(100);
        RGB_LED(0,0,0);
        millis_old = millis();
        }
        
     }
    }

    if(digitalRead(Play_Taster) == LOW) // Beende Modus
    {
      delay(1500);
     return;
    }
    
    whilec = 1; // Deaktivieren, nur wenn Play am Anfang ist auf Startsignal warten
    if(Trimmmodus_aktiv == 0)
      {
      RGB_LED(0,50,0); // Grüne LED an
      }
      
   
    
    }
// Starten, warte auf Play Input oder nicht (DIP Einstellung)





    
 Play_Start_Time = millis(); // Zeit auf 0 setzen
 delay(80); // Bei Kopplung mehrerer Board nötig, da Record Mode für die initalisierung 80Ms länger braucht

 
 while((digitalRead(Play_Taster) == HIGH || (LastTimerValue[4] + MaxPressTime) >  millis()) && Durchlaufanzahl <=  Max_Adresse)
   {
    
    // ---Hardware Beschleunigung--- Das Lesen der Eingänge kostet viel Zeit und muss nicht bei jedem Durchlauf passieren //
    if(HB_Counter > 100 ) // Sorgt dafür, dass nur bei jedem 20 Puls Werte erneuert werden, spart Zeit
     {
 
      GetEepromValues(Durchlaufanzahl);  // Liest dauernt EEprom aus. (werte refresh) 

      Poti2_Endschalter = analogRead(Poti2_Endschalter_Pin); // 0-750 = Poti, >= 900 = Endschalter
      OLED_Refresh(0);
      


      if(Zeit <= (millis() - Play_Start_Time) / 100) // Settings Aktualisieren, wenn Zeit von dem neuen Eintrag erreicht ist
        {
         
         // Wenn letzter Wert ist: Variante  = Ende;  Variante2 = Trimmodus aktiiert, dann wird die Drehrichtung ohne Beschleunigung weiter gegeben
         if((Durchlaufanzahl+1 >=  Max_Adresse && (Trimonoff == 1 || Trimmmodus_aktiv == 1))|| Ersterd == 0)  
           {

            Ersterd = 1; // Deaktivieren nach dem ersten Mal
            
            if(Dir == 1) // 1. Drehrichtung einstellen
              {
               digitalWrite(Direction_Treiber, 1);
               digitalWrite(DIR_LED ,HIGH);
               Dir_old = 0;
              }
   
            else
            {
             digitalWrite(Direction_Treiber, 0);
             digitalWrite(DIR_LED ,LOW);
             Dir_old = 1; 
            }

            
            PLAY_START_Out_State = PLAY_START_Out_EEprom;  
            digitalWrite(PLAY_START_Out, PLAY_START_Out_State);   
           }

     else
     {

      if(Poti2_Endschalter <= 900) // Prüft, dass keine Endschalter berührt werden
        {

          if(PLAY_START_Out_EEprom != PLAY_START_Out_State) // Ausgang Refresh
            {
             PLAY_START_Out_State = PLAY_START_Out_EEprom;
             digitalWrite(PLAY_START_Out, PLAY_START_Out_State);
             }



          if(Dir == 1 && Dir_old == 1) // 1. Drehrichtung wurde verändert, beschleuigen,   Poti > damit am Anfang nicht beschleunigt, wo Motr noch steht
            {
             digitalWrite(DIR_LED ,HIGH);

             if(Poti != 0  && Beschleunigung_aktiv == 0)
               {
                
                for(int i = sqrt (Poti); (i*i) > 0; i--) // Motor entschleunigt
                 {
                  tone(Puls_Treiber, (i*i));
                  delay(Beschleunigung);
                 }

                digitalWrite(Direction_Treiber, 1);
 
                for(int i = 0; (i*i) < Poti_alt; i++)
                  {
                   tone(Puls_Treiber, (i*i));
                   delay(Beschleunigung);
                  }
               } 

      
             else
             {
              digitalWrite(Direction_Treiber, 1);
              }

      
             Dir_old = 0; // letzte Richtung schreiben
    
          } 



          if(Dir == 0 && Dir_old == 0) // 1. Drehrichtung wurde verändert, beschleuigen
            {
             noTone(Puls_Treiber);
             digitalWrite(DIR_LED ,LOW);
         

             if(Poti != 0 && Beschleunigung_aktiv == 0)
               {

                for(int i = sqrt (Poti); (i*i) > 0; i--) // Motor entschleunigen
                 {
                  tone(Puls_Treiber, (i*i));
                  delay(Beschleunigung);
                 }

                digitalWrite(Direction_Treiber, 0); // Neue Drehrichtung 
        
          
                for(int i = 0; (i*i) < Poti_alt; i++)
                 {
                  tone(Puls_Treiber, (i*i));
                  delay(Beschleunigung);
                 }

               }

            else
            {
             digitalWrite(Direction_Treiber, 0);
             }

             Dir_old = 1; // letzte Drehrichtung schreiben
  
           }



          if(Poti_alt >= 1 && Poti == 0 && Beschleunigung_aktiv == 0) // Wenn von Bewegung in Stopp -> Entschleunigen
            {
              
              for(int i = sqrt (Poti_alt); (i*i) > 0; i--) // Motor entschleunigen
               {
                tone(Puls_Treiber, (i*i));
                delay(Beschleunigung);
               }
            }
  


          if(Poti_alt == 0 && Poti != 0 && Beschleunigung_aktiv == 0) // Wenn vom Stopp in Bewegung versetzt wird auch bschleunigem
            {
      
             for(int i = 0; (i*i) < Poti; i++) 
              {
               tone(Puls_Treiber, (i*i));
               delay(Beschleunigung);
              }
            
            }

         }
      
      else
      {
       noTone(Puls_Treiber);
       digitalWrite(Start_Stop_LED, HIGH);
       }   // Zeige Endschalter an!
    
     }



      Poti_alt = Poti;
      Durchlaufanzahl++;
    
      }
     }
    HB_Counter++;
  // ---Hardware Beschleunigung--- Das Lesen der Eingänge kostet viel Zeit und muss nicht bei jedem Durchlauf passieren //




    if(Trimonoff == 0)// wenn aus, letzten Wert nochmal lesen
      {

       if(Poti_alt != 0) // 3. Start / Stop Prüfen
         {
          
          if(Poti2_Endschalter >= 900)
           {
            noTone(Puls_Treiber);
            digitalWrite(Start_Stop_LED, HIGH);      
           }
       
          else
          {
           tone(Puls_Treiber, Poti_alt);
           digitalWrite(Start_Stop_LED, LOW);
           }
         }
     
       else
       {
        noTone(Puls_Treiber);
        digitalWrite(Start_Stop_LED, HIGH);
       }   
     }


    else
    { 

     if(Poti_alt != 0 && Durchlaufanzahl <  Max_Adresse && Poti2_Endschalter <= 900) // 3. Start / Stop Prüfen
       {
        tone(Puls_Treiber, Poti_alt);
        digitalWrite(Start_Stop_LED, LOW);
       }


     if(Poti_alt != 0 && Durchlaufanzahl >=  Max_Adresse && Poti2_Endschalter <= 900) // 3. Start / Stop Prüfen
       {
        tone(Puls_Treiber, 1 *200 );
        digitalWrite(Start_Stop_LED, LOW);
       }

    
     if(Poti_alt == 0 || Poti2_Endschalter >= 900)
      {
       noTone(Puls_Treiber);
       digitalWrite(Start_Stop_LED, HIGH);
      }

  
    }





    if(Durchlaufanzahl >  Max_Adresse && Trimmmodus_aktiv == 0)// loop -> Neustart, nur wenn nicht im Trimmodus
     {
      noTone(Puls_Treiber);
      Poti_alt = 0;
      PLAY_START_Out_State = 0; // Am Anfang immer aus
      digitalWrite(PLAY_START_Out, PLAY_START_Out_State); // State Out am Anfang immer aus

      
      if((DIP_123 & B00000001) == 0) // Wenn Loop Modus aktiviert ist
        {
         Durchlaufanzahl = 1;
         Play_Start_Time = millis();
         noTone(Puls_Treiber);
      
            
         for(uint8_t  i = 0; i<=4; i++)// Neustart optisch anzeigen
          {
           RGB_LED(0,0,0);
           delay(50);
           RGB_LED(0,50,0);
           delay(50);
           RGB_LED(0,0,0);
           delay(50);
           RGB_LED(0,50,0);
          }
          
        } else { // Wartet auf PLAY_START Signal bekommt
        
          whilec = 0;
         
          while(digitalRead(Play_Taster) == HIGH && whilec == 0  && Trimmmodus_aktiv == 0) // Warte auf Signal, oder dass Modus beendet wird
             {
      
              if(analogRead(PLAY_START_In) >= 900)// Maximal 1023, 900 um Störungen zu vermeiden
                {
                 Durchlaufanzahl = 1;
                 Play_Start_Time = millis();
                 noTone(Puls_Treiber);
                 
                 if(Trimmmodus_aktiv == 0)
                  {
                   RGB_LED(0,50,0); // Gruene LED ging immer aus
                  }

                 HB_Counter = 0xFF; // =256 Damit beim Start direkt die Daten gelesen werden
                 whilec = 1;
      
                }
                
              else
              {
               static unsigned long millis_old = millis();

               if((millis()- millis_old) > 1000)
                {
                 RGB_LED(0,30,0);
                 delay(100);
                 RGB_LED(0,0,0);
                 millis_old = millis();
                }
              }
             }
        }
      }
   }
 
 noTone(Puls_Treiber);
 RGB_LED(0,0,0);
 LastTimerValue[4] = millis();
 digitalWrite(PLAY_START_Out, 0); // Ausgang am Ende immer aus

 PLAY_START_Out_State = 0; // Am Ende immer aus
 digitalWrite(PLAY_START_Out, PLAY_START_Out_State); // State Out am Anfang immer aus
 
 digitalWrite(DIR_LED ,LOW); // Schalte alles aus
 digitalWrite(Direction_Treiber, LOW);
 digitalWrite(Start_Stop_LED, LOW);
 return;
}

////////////////////////////////////////////////////////// Bewegung abspielen //////////////////////////////////////////////////////////









////////////////////////////////////////////////////////// Manuelller Modus //////////////////////////////////////////////////////////
void Normaler_Modus(void)
{

 Start_Stop_alt = (EEPROM.read(997) & B00000001); // Initialisierungswert vom letzten Mal
 Drehrichtung_alt =(EEPROM.read(996) & B00000001); // Initialisierungswert vom letzten Mal
 digitalWrite(Direction_Treiber, Drehrichtung_alt);

 // Hardware Beschleunigung:
 uint16_t HB_Counter = 50;
 uint8_t Drehrichtung_Read;   // letzter Drehrichtungs Wert
 uint8_t START_STOP_Read;     // letzter Start/Stop Wert
 uint16_t Potiauswertung_Read; // letzter Poti Wert

 
 uint8_t Start_Stop_changed = 0; // Wenn Taste verändert -> 1
 uint8_t Drehrichtung_changed = 0; // Erkennt ob Drehrichtung verändert wurde
 
 
 while(digitalRead(Manuell_Taster) == HIGH || (LastTimerValue[6] + MaxPressTime) >  millis())
   {
    
   // ---Hardware Beschleunigung--- Das Lesen der Eingänge kostet viel Zeit und muss nicht bei jedem Durchlauf passieren //
    if(HB_Counter > 7) // Sorgt dafür, dass nur bei jedem 7. Puls Werte erneuert werden, spart Zeit
     {
      HB_Counter = 0;
      Drehrichtung_Read = digitalRead(Drehrichtung);
      START_STOP_Read = digitalRead(START_STOP);
      Potiauswertung_Read = Potiauswertung(1);
      OLED_Refresh(0);
     }
    HB_Counter++; 

    Poti2_Endschalter = analogRead(Poti2_Endschalter_Pin); // 0-750 = Poti, >= 900 = Endschalter
      
    if(Poti2_Endschalter <= 900) // Nur wenn Endschalter nicht gedrückt sind Motor start
     { 
        
      if(Drehrichtung_Read == 0 && (LastTimerValue[7] + MaxPressTime) < millis() )// 1. Drehrichtung Auswertung
       {
        Drehrichtung_alt = !Drehrichtung_alt;
        Drehrichtung_changed = 1;
        LastTimerValue[7] = millis();
        EEPROM.write (996, Drehrichtung_alt);// Damit beim Restart Drehrichtung erhalten bleibt
        Drehrichtung_Read = 1; // Deaktiviert, wegen HB Counter nur alle 7 mal aufgerufen wird
       }


      if(START_STOP_Read == 0 && (LastTimerValue[8] + MaxPressTime) <  millis() )// 2. START_Stopp Auswertung
       {
        Start_Stop_alt = !Start_Stop_alt;
        Start_Stop_changed = 1;
        LastTimerValue[8] = millis();
        EEPROM.write (997, Start_Stop_alt);// Damit beim Restart Start_Stop_alt erhalten bleibt.
        START_STOP_Read = 1;
       }


       if(((Drehrichtung_changed == 1 && Start_Stop_alt != 0) || (Start_Stop_changed == 1 && Start_Stop_alt == 0)) && Beschleunigung_aktiv == 0) // Erkennung ob Ent/Be-schleunigt werden muss
        {
        
          if(Start_Stop_changed == 1)
          {
           digitalWrite(Start_Stop_LED, HIGH);
           Start_Stop_changed = 0;
           Drehrichtung_changed = 0;
            
          }

          digitalWrite(DIR_LED, Drehrichtung_alt); 
           

          
       for(int i = sqrt (Potiauswertung_Read); (i*i) > 0; i--) // Motor entschleunigen
        {
         if(analogRead(Poti2_Endschalter_Pin) < 900)
         {
         tone(Puls_Treiber, (i*i));
         delay(Beschleunigung);
         }
          else { noTone(Puls_Treiber);
          Start_Stop_alt = 0;
          }
         
         }
        
         noTone(Puls_Treiber); 
        }
        

       digitalWrite(DIR_LED, Drehrichtung_alt); // Drehrichtung aktualisieren
       digitalWrite(Direction_Treiber, Drehrichtung_alt);
       
        // Wenn kein Stopp -> beschleunigen auf Vmax
       if(((Drehrichtung_changed == 1 || Start_Stop_changed == 1) && Start_Stop_alt != 0 && Beschleunigung_aktiv == 0) || (Manual_Mode_Start == 1 && Start_Stop_alt != 0)) 
         {
          digitalWrite(Start_Stop_LED, LOW);

          for(int i = 0; (i*i) < Potiauswertung_Read; i++) // Motor beschleunigen
           {
            if(analogRead(Poti2_Endschalter_Pin) < 900)
              {
               tone(Puls_Treiber, (i*i));
               delay(Beschleunigung);
              }  
              
          else
          {
           noTone(Puls_Treiber);
           digitalWrite(Start_Stop_LED, HIGH);
           Start_Stop_alt = 0;
          }
         }
         Manual_Mode_Start = 0; // Damit nur beim 1 Durchlauf Beschleunigug funktioniert.
        }
 
       Start_Stop_changed = 0; // Reset, warte auf nächste Veränderung
       Drehrichtung_changed = 0;  // Reset, warte auf nächste Veränderung


       if(Start_Stop_alt != 0) // Damit PotiWwert auch bei deaktivierter Beschleunigung übernommen wird
         {
          digitalWrite(Start_Stop_LED, LOW);
          tone(Puls_Treiber, Potiauswertung_Read);
         }
    
       else
       {
        digitalWrite(Start_Stop_LED, HIGH);
        noTone(Puls_Treiber);
       }

     }
     
     else
     {
      noTone(Puls_Treiber);
      Start_Stop_alt = 0;
      digitalWrite(Start_Stop_LED, HIGH);
     }     
  
  } // Ende While Schleife

 noTone(Puls_Treiber);
 LastTimerValue[6] = millis();
 return;
}

////////////////////////////////////////////////////////// Normaler Modus //////////////////////////////////////////////////////////











////////////////////////////////////////////////////////// Eeprom Werte bekommen //////////////////////////////////////////////////////////
void GetEepromValues(int adresse) //Ziel 16 bit lange Zahl aus 2 register zu lesen und analysieren
{



 if(Hardware_part_EEprom == 0)//wenn kein externes Eeprom -> internes nutzen (hat andere Codierung)
 {
  uint16_t valbyte1; //2 Byte welche den Datensatz beinhalten
  uint16_t valbyte2;

  valbyte1 = EEPROM.read(adresse * 2 - 1); // z.B. Adresse 6 = 11 & 12 byte im Eeprom
  valbyte2 = EEPROM.read(adresse * 2); // 12 byte im Eeprom
 
  Dir = (valbyte1 & B00010000) >> 4; //Den Wert von Direction herausfinden (Byte1 Bit 5)
  Poti = (valbyte1 & B11100000) >> 5; //Den Wert vom Poti (1-7) / Stopp (0) herausfinden Bit 6-8
  Zeit = (valbyte1 & B00001111) << 8 | valbyte2; // Zeit herausfinden, Byte2 & Byte1 Bit 1-4 

  Poti = (Poti * V_Play); // Umrechnung damit Poti Wert z.b. in eine brauchbare Frequenz z.B. 1000Hz umgerechnet wird

}



else // Sonst externes EEprom nutzen
{


  
 uint8_t valbyte1; // 1/4. Byte
 uint8_t valbyte2; // 2/4. Byte
 uint8_t valbyte3; // 3/4. Byte
 uint8_t valbyte4; // 4/4. Byte

 int Extern_eeadresse = ((adresse * 4) -3 ); //Adresse *4 ; -3; z.B. Adresse 2 bei 5,6,7,8 ist.

 Wire.beginTransmission(EEdeviceaddress); // Adresse i2c vom EEprom, Starte Kommunikation
 Wire.write((int)(Extern_eeadresse >> 8));      // 1 Byte nimmt Eeprom Registeradresse
 Wire.write((int)(Extern_eeadresse & 0xFF));    // 2 Byte nimmt Eeprom Registeradresse
 Wire.endTransmission();
 Wire.requestFrom(EEdeviceaddress, 4); // Erwartet 4 viele Werte zurück

 // Prüft ob die Kommunikation zum EEprom funktioniert und liest den 4 Byte Eintrag aus.
 if (Wire.available()) { valbyte1 = Wire.read(); Extern_Eepromaviable = 0; } else { Extern_Eepromaviable = 1;} 
 if (Wire.available()) { valbyte2 = Wire.read(); }
 if (Wire.available()) { valbyte3 = Wire.read(); }
 if (Wire.available()) { valbyte4 = Wire.read(); }
 
 Wire.endTransmission(); // Kommunikation muss beendet werden

 // Decodieren der 4 Byte in brauchbare Werte
 Dir =  (valbyte1 & B00000100) >> 2; //Den Wert von Direction herausfinden Byte 1 Bit3
 Poti = (valbyte1 & B11111000) >> 3; //Den Wert vom Poti  / Stopp (0) herausfinden, Byte2 Bit 4-8
 Zeit = (valbyte3 << 8) | valbyte2; // Zeit errechnen aus Byte3 und byte2
 PLAY_START_Out_EEprom = valbyte4; // Lese GPIO Status aus 0 = aus;  1 = an, nur 1 bit genutzt. 7 noch frei
 
 Poti = (Poti * V_Play * 0.2258); // 7/30 = 0.23, (weil Poti jetzt bis 30 hoch geht statt nur 7 bei dem Internen

 }

}


////////////////////////////////////////////////////////// Eeprom Werte bekommen //////////////////////////////////////////////////////////









////////////////////////////////////////////////////////// Eeprom Werte schreiben //////////////////////////////////////////////////////////
void WriteEepromValues(int adresse) 
{

 //Definiere 4 Bytes, Internes EEprom braucht nur Byte 1 & 2
 uint8_t valbyte1; // Internes + Externes Eeprom
 uint8_t valbyte2;// Internes + Externes Eeprom
 uint8_t valbyte3;// Externes Eeprom
 uint8_t valbyte4;// Externes Eeprom

 
 uint32_t aktuelleZeit; // Zeitdifferenz seit Record Start
 uint16_t Poti_StartStop; // Poti Wert oder 0 für Stopp

 
 if(Hardware_part_EEprom == 0)//wenn kein externes eeprom -> internes
 {
  
  aktuelleZeit = (millis() - Record_Start_Time) / 10; //(Speichert Zeit differenz)in 0,01 Sekunden Schritte

  if(aktuelleZeit % 10 >= 5)
    {
     aktuelleZeit+= 10;
    }
  
  aktuelleZeit = aktuelleZeit /10; // in 0,1 Sekunde Schritte



 if(Start_Stop_alt == 0)
  {
   Poti_StartStop = 0;
  }
  
 else
  {
   Poti_StartStop = Potiauswertung(3);
  }
 
 valbyte1 = (Poti_StartStop & B00000111) << 5 | (Drehrichtung_alt & B00000001) << 4 | (aktuelleZeit & 3840) >> 8; //3840 damit nur letzten 4 von 12 bits übernommen werden
 valbyte2 = aktuelleZeit; // Speichert restliche Zeit in Byte2, Nur die ersten 8 von 12 bits werden übernommen

 EEPROM.write((adresse* 2 - 1), valbyte1);
 EEPROM.write((adresse * 2), valbyte2);

 }




 else // Sonst externes Eeprom nutzen und andere Codierung verwenden
 {

  int Extern_eeadresse = ((adresse * 4) -3 ); //Nimmt Adresse aus oben Funktion *4 ; -3; z.B. Adresse 4 -> 13,14,15,16
 
  aktuelleZeit = (millis() - Record_Start_Time) / 10; //(Speichert Zeit differenz)in 0,1 Sekunden Schritte


  if(aktuelleZeit % 10 >= 5) // Rundet bei 0,1X X. auf ab 5. -> höhere Genauigkeit
   {
    aktuelleZeit+= 10;
   }
   
  aktuelleZeit = aktuelleZeit /10; // in 0,1 Sekunde auflösung umwandeln


  if(Start_Stop_alt == 0)
   {
    Poti_StartStop = 0;
   }
  
  else
  {
   Poti_StartStop = Potiauswertung(4);
  }

 
  valbyte1 = (Poti_StartStop & B00011111) << 3 | (Drehrichtung_alt & B00000001) << 2; // Bit 4,5,6,7,8 = Poti Wert; Bit 3 = Drehrichtung
  valbyte2 = aktuelleZeit; // Speichert restliche Zeit in valbyte3, Nur die ersten Acht bits werden übernommen
  valbyte3 = (aktuelleZeit >> 8); // Bit 8-16 der Zeit wird in valbyte3 gespeichert
  valbyte4 = (B00000001 & PLAY_START_Out_State); //Speichert den Zustand von PLAY_START_Out 1 Bit, 2-8 = noch frei
 

  Wire.beginTransmission(EEdeviceaddress); // Adresse vom Externen EEprom
  
  Wire.write((int)(Extern_eeadresse >> 8));      //1 Byte = Bit 8-16 -> Registeradresse
  Wire.write((int)(Extern_eeadresse & 0xFF));    // 2 Byte = Bit NR 1-8 -> Registeradresse
  
  Wire.write(valbyte1); // Page Write (Maximal 30 Bytes, braucen nur 4).
  Wire.write(valbyte2); // Schreibe einen neuen Eintag in die 4 Bytes
  Wire.write(valbyte3);
  Wire.write(valbyte4);
  
  Extern_Eepromaviable = Wire.endTransmission(); // Speichert, ob EEprom erreichbar: 0 = alles ok >0 -> Fehler

 }
}



////////////////////////////////////////////////////////// Eeprom Werte schreiben //////////////////////////////////////////////////////////










////////////////////////////////////////////////////////// Poti Wert auswertung //////////////////////////////////////////////////////////
int Potiauswertung(int Modus)  // Gibt den Poti Wert aus. Mindestends 1,  Es gibt jedoch unterschiedliche Modi
{
 uint16_t Potivalue ; // 0-1023 3bit = 7 Stufen, 0 = Stopp

 Potivalue = (1028 - analogRead(Potiometer)); //1028 statt 1023 damit der Wert niemals 0 wird

 if(Modus == 0) // Play/Record Modus, Internes Eeprom -> 7 Stufen lesen
 {

  if((Potivalue / 143) > 1)// 1000 : 7 = 143 (1024 wird fast nie erreicht)
   {
    return ((Potivalue / 143) * V_Play);  //Potiwert 1-7 * Geschwindigkeitsbereich
   } 
  
  else // Wenn der Wert 0 ist -> auf 1 setzen (Hardware Fehler)
  {
   return (1*V_Play);
  }
  
}





 if(Modus == 1) // Für Manueller Modus
  {
   static uint16_t Potiauswertung_old;
 
   if((Potiauswertung_old +15) < Potivalue || (Potiauswertung_old - 15) > Potivalue)// 15 = um Poti Toleranz auszublenden
    {
     Potiauswertung_old = Potivalue; // Wenn die Differenz groß genug ist -> abspeichern
    }
    
   return (Potiauswertung_old * ((float)(V_Play*7) /1023)); // Manueller Modus und Play() haben gleiche maximal Geschwindigkeit
}





if(Modus == 2) // Play/Record Modus, Externes Eeprom -> 30 Stufen lesen
{
  
 if((Potivalue / 33) > 1) // 1000 : 31 = 33 (1024 wird fast nie erreicht), 1024 : 32 = 32 -> darf aber max 31 sein, deshalbe durch 33!
  {
   return ((Potivalue / 33)* (V_Play * 0.2258)); //Poti = Poti * 451; // 31*451 = 14000 Vmax um angemessene Geschwindigkeit zu erreichen
  }                                          // Verrechnung zur Poti auflösung: 7/ 31 = 0.2258
   
 else // Mindestens muss es eine 1 sein;
 {
  return (V_Play * 0.2258);
 }
}



if(Modus == 3)// Play/Record Modus, Internes Eeprom -> 7 Stufen schreiben 
{

 if((Potivalue / 143) >= 1)// 1000 : 7 = 143 (1024 wird fast nie erreicht
  {
   return ((Potivalue / 143));  
  } 
 
 else // Mindestens muss es eine 1 sein, damit Motor überhaubt läuft;
 {
  return (1);
 }
 
}


if(Modus == 4) // Play/Record Modus, Externes Eeprom -> 30 Stufen schreiben
{
  
 if((Potivalue / 33) >= 1) // 1000 : 31 = 33 (1024 wird fast nie erreicht)
  {
   return ((Potivalue / 33));  
  }  
 
 else // Mindestens muss es eine 1 sein;
 {
  return (1);
 }
 
}





if(Modus == 10) // Für Poti2 Auswertung
{
 uint16_t Poti2_Endschalter_old; // alter Wert

 Poti2_Endschalter_old = EEPROM.read(993) * 3; // Max 0- 255, für Toleranz, da Poti +/- 1 Schwankt
 Poti2_Endschalter = analogRead(Poti2_Endschalter_Pin); // 0-750 = Poti, >= 900 = Endschalter

 if( Poti2_Endschalter < 70) // 70/750 = 1,  da sonst z.B. 20/750 = 0 wäre -> keine Geschwindigkeit, daher min 1!
 {
  Poti2_Endschalter = 70; 
 }

 // Nur Wenn Poti2 um 3 Einheiten verstellt ist neuen Wert nehmen (um Poti2 Tolernz zu ignorieren)
 if((Poti2_Endschalter_old+15 < Poti2_Endschalter || Poti2_Endschalter_old > Poti2_Endschalter+15)  && Poti2_Endschalter < 750 ) 
  {
   EEPROM.write(993, (Poti2_Endschalter / 3) ); // 8 bit 750 / 3 = max 250
   Serial.println(Poti2_Endschalter / 70);
   return (Poti2_Endschalter / 70); // 0 - 750  /7   = 10 Stufen
  }

 else // Wenn unverändert, alten Wert nehmen
 {
  if(Poti2_Endschalter < 750 ) // Könnte sein, dass Endschalter gedrückt sind
   {
    return (Poti2_Endschalter / 70); // 0 - 750  /7   = 10 Stufen
   }

  else // Sonst Fehler
  {
   Serial.println(1);
   return 1; // langsame Geschwindigkeit
   }

 }

}

}
////////////////////////////////////////////////////////// Poti Wert auswertung //////////////////////////////////////////////////////////









////////////////////////////////////////////////////////// Poti Wert auswertung //////////////////////////////////////////////////////////





int RGB_LED(int red, int green, int blue) // Für die 4 RGB LEDS Max 100 Empfohlen, sonst zu hell
{
 analogWrite(RGB_red, (red*0.1*brightness_red));
 analogWrite(RGB_blue, (blue*0.1*brightness_blue));
 analogWrite(RGB_green, (green*0.1*brightness_green));
}






////////////////////////////////////////////////////////// Trimmung - Einstellung //////////////////////////////////////////////////////////
int Trimmung(void)// Soll kein o ausgeben, macht andere Funktion
{

 Trimonoff = EEPROM.read(999); // Wurde schoneinmal getrimmt? Dann letzte Trimmung löschen
 
 //Wenn schon getrimmt wurde, alte Trimmung überschreiben. Max_Adresse um 1 reduzieren
 if(Trimonoff == 1) // nur trimmen wenn noch nie getrimmt, sonst später reseten für neutrimm !!!
   {
    Max_Adresse = Max_Adresse-1; // 1 abziehen, um letzten Eintag vom Trimmen zu löschen

    // 1 von Max_Sdresse abziehen, den letzten Trimmwert löschen
    EEPROM.write(994, (Max_Adresse & B11111111)); // Speichert ersten 8 Bit
    EEPROM.write(995, (Max_Adresse >> 8)); //Speichert 8-16 bit

    Trimonoff = 0;
    EEPROM.write(999, 0);
   }


 uint16_t korrektur_Dregrichtung_0 = 0; // wie oft nach recht geklickt
 uint16_t korrektur_Dregrichtung_1 = 0; // wie oft nach links geklickt
 uint16_t wirkliche_Korrektur = 0; // Differenz der beiden oberen Korrekturen

 uint8_t letzendlichekorrektur_drehr = 0; // In welcher Richtung letztenendlich korregiert werden soll
 uint8_t Drehrichtungtrimm ;// eingestellte Richtung währed Trimmung, aus Play übernommen 
 
 uint16_t MaxPressTime_trimm = 500; // Presszeit max bei Trimmunktion des Tasters
 unsigned long Zeitverstrichen_taster[10] = {0}; // Schutz, dass Taster ruck nicht doppelt gewerted wird
 
 GetEepromValues(Max_Adresse); // Erhalte: Zeit; Poti; Dir;
 
 Trimmmodus_aktiv = 1; // Trimmodus aktiv Play ohne Loop
  
 uint8_t c;
 
 for(c = 0; c < 8; c++)
   {
    RGB_LED(0,0,0);
    delay(100);
    RGB_LED(50,5,0);
    delay(100);
   }
   
 Play();// Spiele aufgenommene Einträge ab

 for(c = 0; c < 8; c++) // Abspielen ist fertig
   {
    RGB_LED(0,0,0);
    delay(100);
    RGB_LED(50,5,0);
    delay(100);
   }


 Trimmmodus_aktiv = 0; // Trimmodus aktiv Play ohne Loop
 Drehrichtungtrimm = Dir; // Dammit Trimmung in derpassenden Drehrichtung startet
 digitalWrite(Direction_Treiber, Drehrichtungtrimm); //übernehme letzte Drehrichtung von Play
 digitalWrite(DIR_LED ,Drehrichtungtrimm); // Drehrictung an LED anzeigen


 while(digitalRead(Trimmung_Taster) == HIGH || (LastTimerValue[4] + MaxPressTime) >  millis()) //Solange Trimm Taster nicht gedückt -> im Trimm Modus bleiben
 {

   // Drehrichtung Taster Erkennung
  if(digitalRead(Drehrichtung) == LOW && (Zeitverstrichen_taster[1] + MaxPressTime_trimm) <  millis() ) // Wenn Sprung taste gedückt wurde -> In einem Datenpaket festhalten
   {
    Zeitverstrichen_taster[1] = millis();
    Drehrichtungtrimm = !Drehrichtungtrimm; //später LEDS passend leuchten
    digitalWrite(Direction_Treiber, Drehrichtungtrimm);
    digitalWrite(DIR_LED ,Drehrichtungtrimm); // An LED anzeigen
   }


  // 2: Je nach Richtung passendes Menü aufrufen

  static uint32_t counter;

  if(digitalRead(START_STOP) == HIGH && counter > 10)
   {
    counter = 0;
    digitalWrite(Start_Stop_LED, !digitalRead(Start_Stop_LED));
   }

  counter++;


  if((digitalRead(START_STOP) == LOW && (Zeitverstrichen_taster[2] + MaxPressTime_trimm) <  millis()) &&  Drehrichtungtrimm == 0) // Wenn Sprung taste gedückt wurde -> In einem Datenpaket festhalten
   {
    Zeitverstrichen_taster[2] = millis();
    tone(Puls_Treiber, 1 *200); // 1 als Poti wert, Achtung hier 200 statt 2000
    delay(100); // bestimmt die Step größe, nachher verrechnen
    noTone(Puls_Treiber);
    korrektur_Dregrichtung_0 ++;
   }


  if((digitalRead(START_STOP) == LOW && (Zeitverstrichen_taster[3] + MaxPressTime_trimm) <  millis()) &&  Drehrichtungtrimm == 1) // Wenn Sprung taste gedückt wurde -> In einem Datenpaket festhalten
   {
    Zeitverstrichen_taster[3] = millis();
    tone(Puls_Treiber, 1 * 200);
    delay(100); // bestimmt die Step größe, nachher verrechnen muss 100 sein oder grßer da 0,1 Sekunde
    noTone(Puls_Treiber);
    korrektur_Dregrichtung_1 ++; // halte den Korrekturfaktor fest
  }

 } //Eingabe beendet, Eingabe verrechnen



  // Rechne Differez (links und rechts Sprünge) aus, Berechne tatsäschliche Korrektur
  if(korrektur_Dregrichtung_1 >= korrektur_Dregrichtung_0)
   {
    wirkliche_Korrektur = (korrektur_Dregrichtung_1 - korrektur_Dregrichtung_0);
    letzendlichekorrektur_drehr = 1;
   }
  else
  {
   wirkliche_Korrektur = (korrektur_Dregrichtung_0 - korrektur_Dregrichtung_1);
   letzendlichekorrektur_drehr = 0;
  }

// Ist nur eine Test Software um die Einträge auslesen zu können
/*
  uint32_t counter =1;
  while(counter <= Max_Adresse+1)
  {
   GetEepromValues(counter);
   counter++;
// Test oh Werte ijd Eeprom  gespeichert werden


  //Serial.print("Aktuelle Adressen Anzahl:  ");
//Serial.println(counter);

 // Serial.print("Dir:  ");
//Serial.println(Dir);

//Serial.print("Poti:  ");
//Serial.println(Poti);

//Serial.print("Zeit:  "); // in 4002 = 400,2 Sekunden
//Serial.println(Zeit);
//Serial.println("----------------------------------------- ");

}
  */


  GetEepromValues(Max_Adresse); // holt sich sicherhetshalber nocheinmal die echte aktuelle Zeit aus dem letzten Eintrag

  if(Hardware_part_EEprom == 0)//wenn kein externes eeprom -> internes nutzen
   {
    uint16_t valbyte1x = (5& B00000111) << 5 | (letzendlichekorrektur_drehr & B00000001) << 4 | ((Zeit) & 3840) >> 8; //3840 damit nur letzten 4 bits übernommen werden
    uint16_t valbyte2x = (Zeit); // Speichert restliche Zeit in Byte2, Nur die ersten Acht bits werden übernommen
 
    EEPROM.write((Max_Adresse)* 2 - 1, valbyte1x);
    EEPROM.write((Max_Adresse) * 2, valbyte2x);

    Max_Adresse = Max_Adresse+1;

    valbyte1x = (0& B00000111) << 5 | (letzendlichekorrektur_drehr & B00000001) << 4 | ((wirkliche_Korrektur+Zeit) & 3840) >> 8; //3840 damit nur letzten 4 bits übernommen werden
    valbyte2x = (wirkliche_Korrektur+Zeit); // Speichert restliche Zeit in Byte2, Nur die ersten Acht bits werden übernommen
 
    EEPROM.write(((Max_Adresse)* 2 - 1), valbyte1x);
    EEPROM.write(((Max_Adresse) * 2), valbyte2x);

  }

  else // sonst externes Eeprom nutzen
  {
    
   int Extern_eeadresse = ((Max_Adresse * 4) -3 ); // Rechnet Max adresse um
   
   uint8_t valbyte1 = (5 & B00011111) << 3 | (letzendlichekorrektur_drehr & B00000001) << 2; // | oder -> verknüpft alles
   uint8_t valbyte2 = Zeit; // Speichert restliche Zeit in Byte2, Zeit aus Eeprom read
   uint8_t valbyte3 = (Zeit & 65280) >> 8; // 65280 = 1111111100000000 damit nur Bit 8-16 genutzt wird


   Wire.beginTransmission(EEdeviceaddress); // Adresse vom Externen EEprom
  
   Wire.write((int)(Extern_eeadresse >> 8));      //1 Byte = Bit 8-16 
   Wire.write((int)(Extern_eeadresse & 0xFF));    // 2 Byte = Bit NR 1-8 (beides Adresse)
  
   Wire.write(valbyte1); // Page Write , Maximal 30 Bytes! (braucen nur 4)
   Wire.write(valbyte2);
   Wire.write(valbyte3);
   Wire.endTransmission();

   Max_Adresse = Max_Adresse+1;
  
   Extern_eeadresse = ((Max_Adresse * 4) -3 ); // Rechnet Max adresse in neue um


   valbyte1 = (0 & B00011111) << 3 | (letzendlichekorrektur_drehr & B00000001) << 2; // | oder -> verknüoft alles
   valbyte2 = (wirkliche_Korrektur+Zeit); // Speichert restliche Zeit in Byte2, Zeit aus Eeprom read
   valbyte3 = ((wirkliche_Korrektur+Zeit) & 65280) >> 8; // 65280 = 1111111100000000 damit nur Bit 8-16 genutzt wird
   //uint8_t valbyte4 = 0ä; //Später stm32 Outputs ...
 
   delay(15); // Wichtig!,  nach einer vorherigen Sendung >10 Ms warten, sontst nimmt Eeprom keine Werte an!!

   Wire.beginTransmission(EEdeviceaddress); // Adresse vom externen EEprom
  
   Wire.write((int)(Extern_eeadresse >> 8));      //1 Byte = Bit 8-16 
   Wire.write((int)(Extern_eeadresse & 0xFF));    // 2 Byte = Bit NR 1-8 (beides Adresse)
  
   Wire.write(valbyte1); // Page Write , Maximal 30 Bytes! (braucen nur 4)
   Wire.write(valbyte2);
   Wire.write(valbyte3);
   // Wire.write(valbyte4);
   Wire.endTransmission();
  
  }

  //Speicherung der neuen Max_adresse im internen EEprom

  EEPROM.write(994, (Max_Adresse & B11111111)); // Speichert ersten 8 Bit
  EEPROM.write(995, (Max_Adresse >> 8)); //Speichert 8-16 bit
  EEPROM.write(999, 1); // Stellt Trimmung ein
  
  digitalWrite(Start_Stop_LED, 0); //LEDS ausschalten
  digitalWrite(DIR_LED , 0);
  LastTimerValue[5] = millis();
}


////////////////////////////////////////////////////////// Trimmung - Einstellung //////////////////////////////////////////////////////////









////////////////////////////////////////////////////////// OLED Display Refresh  //////////////////////////////////////////////////////////

int OLED_Refresh(int Mode) 
{
 // Display soll nur refresh durchführen, wenn Wert verändert wurde -> Refresh dauert nämlich lange, Speichrt jeweils ide letzten Werte
 uint8_t Value_changed =0; 
 static uint8_t Firstrun;
 
 static uint8_t Current_Mode_o; 
 static uint16_t Poti2_Endschalter_o; // muss 0 / ens erkennen
 static uint8_t PLAY_START_Out_State_o;
 static uint8_t Extern_Eepromaviable_o;
 
 display.setRotation(2);
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(WHITE);

 if(Mode == 1) // Initalisierung
 {
  display.drawBitmap(32, 0 ,logo, 64, 64, WHITE);
  display.display();
  delay(2000);
 }
 

 if((LastTimerValue[10] + 1500) <  millis()) // Für Manuellen Modus, damit trotzdem EEprom Status anzeigt
  {
   Wire.requestFrom(EEdeviceaddress, 1);// Erwartet 4 viele Werte

   if (Wire.available() )
    {
     Extern_Eepromaviable = 0;
    }
    else
    {
     Extern_Eepromaviable = 1;
    }

    LastTimerValue[10] = millis();
  }
    


 // Prüfen, ob sich ein Wert verändert hat -> Refresh
 if(Current_Mode != Current_Mode_o)
 { Value_changed = 1;
   Current_Mode_o = Current_Mode; }
  
 if(Poti2_Endschalter >= 900 && Poti2_Endschalter_o <= 900)
  { Value_changed = 1;
    Poti2_Endschalter_o = Poti2_Endschalter; }
 if(Poti2_Endschalter <= 900 && Poti2_Endschalter_o >= 900)
  { Value_changed = 1;
    Poti2_Endschalter_o = Poti2_Endschalter; }
  
  
 if(PLAY_START_Out_State != PLAY_START_Out_State_o)
   { Value_changed = 1;
     PLAY_START_Out_State_o = PLAY_START_Out_State; }

 if(Extern_Eepromaviable != Extern_Eepromaviable_o)
   { Value_changed = 1;
     Extern_Eepromaviable_o = Extern_Eepromaviable; }




 if(Mode == 0 && (Value_changed == 1 || Firstrun == 0)) // OlED Refresh
 {
  Firstrun = 1; // Nur beim ersten mal, damit Nch Icon Date angezeigt werden
  display.drawBitmap(80, 9 ,Motor, 50, 30, WHITE);
  display.drawRect( 120, 42,  8,  5, WHITE);


  if(Extern_Eepromaviable == 0) // Zeige an, EEprom erkannt
   {
    display.fillRect( 120, 42,  8,  5, WHITE);
   }
 
  if(Extern_Eepromaviable >= 1) // Zeige an, EEprom Fehler Wenn Wert >= 1 ist
   {
    display.fillRect( 121, 43,  6,  3, BLACK);
   }

 

  display.setCursor(0,0);
  display.print("Mode: ");
 
  if(Current_Mode == 0)
  {
   display.print("Sleep");
  }

  if(Current_Mode == 1)
  {
   display.print("Play");
  }

  if(Current_Mode == 2)
  {
   display.print("Manual");
  }

  if(Current_Mode == 3)
  {
   display.print("Record");
  }

  if(Current_Mode == 4)
  {
   display.print("Trim");
  }
  


  display.setCursor(0,12);
  display.print("Limit S: ");
  if(Poti2_Endschalter >= 900)
  {
   display.print(1);
   } else {
    display.print(0);
   }
   
  display.setCursor(0,22);
  display.print("V-Range: "); // Geschwindigkeitsstufe
  display.print(V_Play / Speed_Setting);


  display.setCursor(0,32);
  display.print("Acceler: "); // Geschwindigkeitsstufe
  if(Beschleunigung_aktiv == 0)
  {
   display.print(Beschleunigung);
   } else {
   display.print("OFF");
   }


  display.setCursor(80,0);
  display.print(Max_play_time); // Dauer der letzten Aufnahme , ist falsch muss time verwenden
  display.setCursor(103,0);
  display.print(" Sek");

 
  display.setCursor(0,41);
  display.print("Pin-Out: "); // Gibt den Ausgang an vom Screw Terminal

  if(Hardware_part_EEprom == 1)
   {
    display.print(PLAY_START_Out_State);
    }
  else {
   display.print("---");
   }

  display.setCursor(107,41);
  display.print("S:"); // S = Speicher verfügbar ?

  display.setCursor(0,55); 
  display.print("Rublicator Innovation"); // Geschwindigkeitsstufe
  display.display(); 
 } 
}



////////////////////////////////////////////////////////// OLED Display Refresh  //////////////////////////////////////////////////////////






/* (C)Copyright by Rublicator Innovation Inhaber Ruben Rodermann
 *  Rublicator Schrittmotorsteuerung mit Record Funktion V1
 *  Version: 1.0 (Q2/2021)
 *    
 *    
 *  Rechtlicher Hinweis: 
 *  Die Software darf ausschließlich für den privaten Gebrauch verwendet werden. 
 *  Eine Weiterverbreitung ist in jeglicher Art verboten. Die komerzielle Nutzung 
 *  sowie Verbreitung der Software ist verboten. Dies gilt auch, wenn die Software 
 *  nur verändert wurde. Alle Rechte liegen ausschließlich bei dem Urheber. 
 *  
 *  Hinweise:
 *  - Es sollte nicht zu oft Serial.print benutzt werden, sonst können
 *    nicht erwünschte Störungen auftreten.
 *  - PLAY_Start Ausgang in Record nicht De/Aktivieren, wenn
 *    man parallel eine andere Eingabe macht (z.B. Poti Geschwindigkeit verstellen)
 *    sonst Teilweise Fehlsignale
 *  - Funktion OLED_Refresh() sollte nicht veändert werden.
 */ 
