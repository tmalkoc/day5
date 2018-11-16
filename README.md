### final exercise

Napravite command line aplikaciju koja slaže linearnu sekvencu od jednostavnih matematičkih blokova.

Svaki blok ima točno jedan ulaz (double), jedan izlaz (double) i eventualne dodatne parametre.

Napravite (barem) nekoliko blokova:
- identity - vraća ulaz
- addition - vraća ulaz uvećan za konstantu
- multiplication - vraća ulaz umnožen sa konstantom
- power - vraća ulaz potenciran na konstantu
- limit - vraća min konstantu ako je ulaz manji od nje, max konstantu ako je ulaz veći od nje, inače ulaz
- condition - vraća -1, 0, 1 ovisno o usporedbi sa konstantom

Za svaki blok i za sekvencu napišite unit testove (zaseban projekt).

Korisnik može iz glavnog menija
a) kreirati sekvencu
- dodati blok na kraj sekvence (dodatne parametre unosi odmah, ne mogu se naknadno mijenjati)
- obrisati blok iz sekvence
- pomaći postojeći blok iz sekvence na početak
- vidjeti trenutnu sekvencu

b) evaluirati vrijednosti
- unijeti jednu vrijednost nad kojom će se izvršiti svi blokovi i ispisati konačni rezultat
- unijeti naziv tekstualne datoteke sa nizom vrijednosti - izvršit će se svi blokovi nad svim vrijednostima i snimiti izlazni file sa rezultatima

Sekvenca se sprema u file i automatski učitava pri sljedećem pokretanju programa.
