# Flappy-Bird-Krakow-Edition
Instrukcja Kompilacji i Uruchomienia
Wymagania:

Kompilator wspierający standard C++17.

Zainstalowana biblioteka SFML 2.5+.

Głównym zadaniem gracza jest sterowanie smogiem w taki sposób, aby przetrwać jak najdłużej, omijając przeszkody i realizując cele ekonomiczne (zbieranie surowców).

Podstawowe mechaniki:
Sterowanie: Gracz kontroluje wysokość lotu smoga poprzez kliknięcia myszą (LPM). Każde kliknięcie nadaje ptakowi pęd w górę, przeciwdziałając sile grawitacji, która stale ciągnie go w dół.

Unikanie kolizji: Gra kończy się natychmiast, gdy smog dotknie rury (przeszkody) lub uderzy w ziemię.

Zdobywanie punktów: Punkty do ogólnego wyniku (Score) przyznawane są za skuteczne przelecenie przez środek każdej pary rur.

System surowców i poziomów:

Gra posiada unikalny system zbierania surowców, który definiuje postęp gracza:
Poziom 1 (Surówka):
Podczas lotu na ekranie pojawiają się ikony Surówki.
Gracz musi wlecieć w ikonę, aby ją zebrać.
Cel: Zebranie 15 sztuk Surówki odblokowuje dostęp do drugiego poziomu gry.
Poziom 2 (Stal):
Po odblokowaniu w menu, gracz może wybrać poziom 2, gdzie otoczenie zmienia się.
Zamiast Surówki, gracz zbiera Stal.


