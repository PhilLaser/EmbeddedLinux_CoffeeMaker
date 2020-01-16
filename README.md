# EmbeddedLinux_CoffeeMaker
## Beschreibung
Diese Anwendung dient zur Steuerung einer Kaffeemaschine. Über die Webapp kann die Kaffeemaschine direkt oder auch zeitverzögert angesteuert werden.
Unsere Projektziele waren die folgenden:
-	Eine Kaffeemaschine modifizieren, um sie an ein Raspberry Pi anschliessen zu können. 
-	Eine Anwendung schreiben, um die Funktionen der Kaffeemaschine auslösen zu können.
-	Optional: Webinterface zur Fernbedienung erstellen.

Diese konnten wir erfolgerich umsetzen.

## Install

app.py uses Flask, so make sure you pip install it. 

Compile relay.c like 'gcc -o relay relay.c -Wall'

Connect both relays to D3 and D4. D3 is for espresso and D4 for lungo.
