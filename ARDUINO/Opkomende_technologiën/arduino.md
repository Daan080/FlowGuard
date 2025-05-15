# Arduino Flowguard
## Introductie
Volgens cijfers van het RIZIV is meer dan een derde van de langdurige arbeidsongeschiktheid in België gelinkt aan psychische stoornissen, met depressie en burn-out als koplopers. Een belangrijke oorzaak hiervan is de aanhoudende werkdruk, stress en het gebrek aan pauzes — zeker bij mensen die aan een bureau werken in een kantooromgeving. Dit project is ontstaan als antwoord op die problematiek.

## Doel:
De Flowguard helpt kantoormedewerkers door:
Regelmatig pauzes aan te moedigen,
Visueel de werkstatus te tonen aan collega’s,
Een gevoel van controle en voldoening te geven over het werkritme.
Deze synthese beschrijft het ontwerp van het Arduino-circuit en de bijbehorende code die dit product functioneel maken.
## materiaal
- Arduino (Uno/Nano):
  De kern van het systeem. Een stabiel en flexibel platform dat eenvoudig te programmeren is en veel ondersteuning heeft voor extra componenten. Hierdoor kon snel
  een werkend prototype worden opgebouwd.

- RGB LCD-scherm (met I2C):
  Toont duidelijk de resterende tijd op een intuïtieve manier (HH:MM:SS).
  De achtergrondkleur verandert afhankelijk van de status (groen of rood), wat zorgt voor een directe visuele koppeling tussen status en tijd.

- Rotary Encoder (met drukknop):
  Laat toe om op een natuurlijke manier tijd in te stellen en de timer te starten/stoppen.
  De encoder biedt fysieke controle zonder dat er een schermmenu of complexe interactie nodig is, wat laagdrempelig is voor elke gebruiker.

- LED Arcade drukknoppen:
  Bieden een eenvoudige en directe manier om de werkstatus manueel aan te passen en hebben een goede sensiviteit en omvang, .

- Adafruit NeoPixel RGB-ledring:
  Visuele feedback op afstand: toont of de gebruiker beschikbaar is of in focus is zonder geluid of onderbrekingen.
  De ledkleur is altijd synchroon met de status van de lcd-backlight, wat consistentie biedt.

## Onderdelen
### Groen/Rood lamp
Probleemaanpak:
In kantoren is het vaak onduidelijk of iemand geconcentreerd aan het werk is of openstaat voor onderbrekingen. Hierdoor ontstaan onnodige verstoringen die stress kunnen verhogen.

Oplossing via hardware en code:
Met twee fysieke knoppen (groen en rood) kan de gebruiker zelf de werkstatus aangeven.
Bij een druk op de groene knop:
De lcd-backlight en de RGB-ledring kleuren groen.
Dit geeft aan: "Ik ben beschikbaar" of "Ik werk in een normaal tempo".
Bij een druk op de rode knop:
De backlight en ledring kleuren rood.
Dit signaleert: "Niet storen" of "Ik ben gefocust bezig".
Dit visueel systeem bevordert respect voor elkaars werkflow en voorkomt overbodige stressvolle onderbrekingen.

### Timer
Probleemaanpak:
Veel werknemers nemen te weinig pauzes, wat leidt tot mentale vermoeidheid. Pauzes zijn essentieel voor concentratie en stressverlaging, maar worden vaak vergeten of uitgesteld.
Oplossing via hardware en code:
Een ingebouwde timerfunctie met encoder helpt bij het plannen van korte werkblokken en pauzes:
Via de rotary encoder kan de gebruiker eenvoudig een werk- of pauzeperiode instellen. De code zorgt voor slimme tijdsaanpassingen met stappen die afhangen van de ingestelde tijd (vb. stappen van 30 seconden voor korte pauzes).
De druk op de encoder start of stopt de timer.
Tijdens het aftellen is de RGB-ledring actief, wat een duidelijk signaal geeft dat de gebruiker aan een taak bezig is.

Wanneer de timer afloopt:
De lcd-tijd begint te knipperen.
De backlight wordt extra fel (helder groen of rood) om de gebruiker visueel te attenderen.
De ledring schakelt uit — dit benadrukt dat de ingestelde tijd voorbij is en nodigt uit tot pauze.
Door het gebruik van eenvoudige fysieke interactie (draaien, drukken) en duidelijke lichtsignalen, wordt de gebruiker subtiel begeleid in een gezonder werkritme.
