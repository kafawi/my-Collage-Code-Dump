# Aufganverteilung KW 16 - 19 
KW16
* HAL lauffähig machen
* Serielle Schnittstelle
  - Byte senden
  - Checksumme == zurücksenden und auf Gleichheit zuprüfen

Wrapper schreiben

????????
Kallitbrierungsduurchlaufs Konzept

Pulsemessages? 
* ausprobieren
* erfahrungen sammeln

KW17 - KW19
* Basics Logger
 
Wenn HAL & Serial laufen: 
* Automaten Sequenzdiagramme

Wenn Automaten Sequenzdiagramme vorhanden sind:
* Konsistente Architektur und Design prüfen
- Rollenspiel/Durchgehen der Diagrammme

Genaude Dokumentation, für Hard/ Software, was passiert wenn ein Werkstück aufs Laufband gelegt wird
* Sequenzdiagramme
* Tabelle

Logger/Reader
* Logging Fotmat festlegen, damit es erkennbar für den reader ist.
* Logging in alle vorhandenen Datein einpflegen und Fortführen





Konzept für die Weiterleitung der Sensorsignale zu verarbeitenden Komponenten

Geeignetes Pattern/Design für die Verarbeitung der Sensordaten ausgewählt

Modellierung der Anlagensteuerung beider Förderbänder mit Zustandsautomaten
oder Petri-Netzen mit Ausnahmebehandlung

Schnittstelle für gesamte Aktorik dokumentiert

Realisation der Sensorik basierend auf ISRs und Pulse-Messages

Test der Sensorik-HAL

| Name | NAME | Datum | Fertig |
| ------ | ------ | ------ | ------|
| Kalle | HAL | prio |
| Alex |  Serielle Schnittstelle | |
| Alex | Dokumenatation überprüfen | |
| Kalle | Wrapper | prio |
| Lennart | Sequenzdiagramme /Automaten per Hand |   |
| Kalle  | Codeingstyle  | ???? |
| Nils | Zeitentabelle anlegen | Do 20.04.17 | rdy |
| Alex/Lennat/Nils | Pulse Message spielen | 20.04.17 | rdy |
| Alex/Lennat/Nils | Automat in C++ testen | 20.04.17 | rdy |
| Nils |Logger zum laufen bringen|Di 25.04.17 ||