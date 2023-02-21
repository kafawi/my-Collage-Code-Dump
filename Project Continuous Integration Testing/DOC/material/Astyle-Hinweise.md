#Anleitung zur Nutzung des Stylecheckers astyle

Achtung: Die reguläre Version von Astyle bietet keine Möglichkeit
nützliche Informationen zu vorgenommenen Änderungen zurückzugeben.

Lösung: Der Fork unter https://github.com/steinwurf/astyle erlaubt
mit der neuen Option --print-changes die Ausgabe einer Liste 
vorzunehmender Änderungen

Installation:
In .../astyle-master/
- python waf configure --cxx_mkspec=cxx_default
- python waf build
ausführen

Kompilertes Programm:
Das Excecutable findet sich nun in .../astyle-master/build/cxx_default/

Beispiel mit  Erzeugung eines Reports in astyleReport.txt:
astyle --style=gnu --dry-run --verbose --print-changes original.cpp 1> astyleReport.txt

Beispiel mit in neues File geschriebenen Änderungen:
astyle --style=gnu  < original.cpp >  bearbeitet.cpp

Optionen:
--style				der gewünschte Coding Style
--dry-run			Probe ohne geschriebene Änderungen
--print-changes			Konsolenausgabe der Änderungen
--verbose			detaillierte Ausgabe

Liste der Vordefinierten Coding Styles
http://astyle.sourceforge.net/astyle.html#_Quick_Start
