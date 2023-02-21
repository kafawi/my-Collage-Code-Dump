#Architektur

Es wird eine 3-Layer-Architektur verwendet, bestehend aus:
- HID (Human Interface Device)
- MCL (Master Control Layer)
- HAL (Hardware Abstraction Layer)

#### Grenze MCL zu HAL
Der MCL definiert ein Interface und Enums, welches mit definierten Kommandos die Ansteuerung der Aktorik vorgibt. Dieses wird von der HAL implementiert. Die Events von der Sensorik werden von der HAL mit Push Push-Massages an den MCL übermittelt.

#### Grenze MCL zu HID
Von der HID werden Puls-Mesages an die MCL gesendet.