# Arduino Flowguard
## Introductie
Volgens cijfers van het RIZIV is meer dan een derde van de langdurige arbeidsongeschiktheid in België gelinkt aan psychische stoornissen, met depressie en burn-out als koplopers. Een belangrijke oorzaak hiervan is de aanhoudende werkdruk, stress en het gebrek aan pauzes — zeker bij mensen die aan een bureau werken in een kantooromgeving. Dit project is ontstaan als antwoord op die problematiek.

## Doel:
De Flowguard helpt kantoormedewerkers door:
Regelmatig pauzes aan te moedigen,
Visueel de werkstatus te tonen aan collega’s,
Een gevoel van controle en voldoening te geven over het werkritme.
Deze synthese beschrijft het ontwerp van het Arduino-circuit en de bijbehorende code die dit product functioneel maken.

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
