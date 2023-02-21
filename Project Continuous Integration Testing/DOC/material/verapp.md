# Style-Checker: vera++
Hausaufgabe aus dem Kurzprotokoll 2017-09-25
Autor: Karl-Fabian Witte

## Aufgabe
Style-Checker mit Consolensteurung, der Report generiert (HTML, XML,...)

Vera++ parset die Programmobjecte in Collections und übergibt diese einem
Script, damit dieses eine Meldung ausgibt oder den Code transformiert.
Die Scripte können/sollten selbst geschreiben werden, jedoch
sind auch Standart Skripte, wie Zeilenende (carrier-return) vorkommen,
schon bereitgestellt. Die nicht modifizierenden Scripte, können als 
Stylerule oder Rule verwendet werden.
Die weiteren Information werden nun aufgeführt:
### Weitere Sprachen + Versionen außer C/C++
nein
### Formate (Styles)
Anhand von sogenannten Profile individuell bestimmbar. Die Profile 
sind eine Collection von Rule- und Transformationscripten.

### Güte der Outputs
Outputs wegen der Individuell gesetzten Rules relativ gut. 
Meldung kann selber formatiert werden.
Reporte werden in xml, vc (Visual Studio) oder in 
 gcc-like Format ausgegeben
(Eventuell zu viel eigenverantwortung)
### Black/Whitelisten/manueller Eingriff
Erfordert viel Zeit.

Fileebene: Da jedes File einzelt angegeben werden muss, totale Kontrolle
StyleEbene: Totale Kontrolle über die sogenannten Rules (Styles) bzw 
einem Profile.
Zeilebene: -
### Recursiv (Dateien einsammeln)
Nein, dies müsste über das Python-/shellscript ermöglicht werden,
welches vera später redundant aufrufen würde. 
(S: https://bitbucket.org/verateam/vera/issues/44) 
### Lizenzmodell
Boost Software License
(Sie wird in der STL convertiert -> also fast wie MIT)
(Außnahme vera.ctest (Apache License v2.0)

### Inbetriebnahmeaufwand
Installation: fummelig, 
da nicht in den Mirrorrepros der Distros aufgelistet,
Clonen und compilen. -> da opensource.
Selbst schreiben der Skripte erfordert mehr Aufwand.
-> jedoch sind die Scripte relativ kleingehalten.
Pro Rule ein script. Es ist auch Python möglich (sonst Tcl und Lua)
Die Wiki ist eine super docu und hilfe, und der quelloffene 
ourcecode macht das schreiben eines scriptes einfach.
https://bitbucket.org/verateam/vera/wiki

### Support in der community
relativ klein, jedoch aktiv. 
Issues werden im Wochen bis Monatabstand gemeldet,
https://bitbucket.org/verateam/vera/overview

### Aktiv gepflegt
Das coreteam besteht aus drei Personen.
Diese pflegen das Projekt aktiv, jedoch bedingt durch die größe langsam.

### Quellcode offen
ja, da Bedingung der Lizense

### Host-Betriebsystem
durch die Quelloffenheit, wir das Programm auf dem Betriebsystem übersetzt,
relativ Hostunabhängig.

### Hybide (Stylechecker+Analyser)
Nein.

### False Positive
Keine gefunden. Issue-List wurde nicht durchgeblättert.
(Beim Stylechecker sehe ich keine Fälle, jedoch kann man 
mich da gerne berichtigen)

### Umformatieren automatisch möglich/integriert
Nein, jedoch via Skript machbar. 
Lieber Astyle (MIT Lizenz) o.Ä. verwenden.

## Sonstiges/Anmerkung
Die Option mit Vera wäre für die Anpassung eine gute Lösung, 
jedoch müssten viele Skripte geschrieben werden und dies ist 
Zeitaufwendig. Zudem sind wenige komforfunktionen, wie automatisches 
Transformieren des Codes oder rekursiver Aufruf der zu prüfenden 
Code nicht implementiert.
Der gcc-like Output sagt aber zu und könnte so direkt in den 
Endreport unseres Analysetools übernommen werden.

## Anwendung
Der Favorit soll ausprobiert werden. Abstimmen über Slack, 
welcher Style-Checker auf was untersucht wird, 
damit wir breite Ergebnisse bekommen.

Beipiel: Aufeinanderfolgende Leezeilen werden nicht erlaubt.

in der Komandozeile -> stdOut (-o -)
```
tux@linuxBox$ vera++ file_under_check.c -rule L005  -o -
file_under_check.cpp:5:too many consecutive empty lines
```

Beispiel: Profilefile (Coding Style)
```
# this file defines the set of scripts (rules) 
# good vertical space 

set rules {
    L005
}
```
```
tux@linuxBox$ vera++ file_under_check.c --profile good_v_space  -o -
file_under_check.cpp:5:too many consecutive empty lines
```

[manpage](https://www.manpages.org/vera)
