# Projekt Continuous Integration für Embedded Systems
Kurzprotokoll 2017-10-02
Protokollführer: Thomas Lehmann

Teilnehmer:
Thomas Lehmann,
Torge Hinrichs, 
Lennart Hartmann, 
Malte Schuler, 
Karl-Fabian Witte

## Notizen 

  - Der GitLab Server läuft, kann derzeit aber noch nicht per SSH angesprochen werden. Der Server ist nicht von außen sichtbar, nur von intern oder per VPN.
  - Erster Prototyp soll mit Artistc Style gebaut werden.
  - Für Protokolle soll jeweils ein eigener Ordner angelegt werden.
  - Ein Beispiel für die Pipeline in GitLab ist installiert. Gesteuert wird die Pipeline über gitlab-ci.yml. Das Script gilt für das gesamte Projekt.
  	
## Erster Sprint 

### User Story 

Als Kunde möchte ich meinen Code aus einem Repository durch einen Drittanbieter auf Format/Code-Style überprüfen lassen und einen Report erhalten.

### Entscheidungen 
-	Erste Schritte mit dem Artistic Style Checker
-	Alle Checks, ... müssen in einem Docker-Container laufen
-	Python 3.x (>3.3) soll nach Möglichkeit als Script-Sprache verwendet werden
-	Standard-Reports ohne weitere Aufarbeitung
-	Im ersten Durchgang werden kundenspezifische Einstellungen in den einzelnen Paketen direkt bearbeitet. Später werden die Daten zusammengeführt und ggf. ein Front-End erstellt.
-	Probleme sollten direkt ins Issue-Tracking eingetragen werden.

### Fragen 

-	Wie bekommt der Kunde den Report?
-	Wie bekommen wir deren Code? Wie kommt der Code in die Pipeline?

### Dokumentation 

-	Benutzung (durch Kunde)
-	Variablen/Einstellungen von bestimmten Tools
-	Im Wiki das grobe Bild der Abläufe (mit Verweis auf die Skripte) ablegen.

Ende: 11:30

Nächstes Treffen: 09.10.17, 8:15, Raum 7.81
