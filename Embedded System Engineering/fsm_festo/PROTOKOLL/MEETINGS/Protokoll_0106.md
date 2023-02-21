## Meeting Protikoll 1.06.2017
-----------------------------------
Zeit: 8:20 - 9:00
Teilnehmer: Alex, Eddy, Lennart, Kalle, Nils
##Status 
Kalle: Channel fertig gewrapt, getestet, dokumentiert 
Alex,Nils: Pulse Messeanging - Demaskieren fehlt
Eddy: Puk - Job übergeben, Provisiorium fertig
Lennart: FSMs für Eingang, Profilmessung, Metalldetektion/Gatesteuerung, Ausgang, Behandlung geschrieben,
		 Provisorische Klassen für alle notwendige Peripherie geschrieben, UML-Design und -Automaten erstellt.
##Beschluss Arbeitsablauf
- Trello checken -> git pull -> bearbeiten -> neue Pakete auf trello.
- Benachrichtigung nur an Personen, die am Paket arbeiten

##Beschluss Architektur/Design
- AmpelTiming wird von MCL vorgegeben => WarningLightController hat Thread
- Ablaufsteuerung der Profilmessung gehört zur MCL
- regulärer Betrieb wird durch parallele Automaten gehandhabt
- Ausnahmezustände werden durch parallele Automaten gehandhabt
- InputMultiplexer hält die für Auswahl des anzusprechenden Automaten nötigen Informationen

##Einweisungen
- Thread
- Timer
