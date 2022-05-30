# WSMZR9parhuzamos

[Link a beadandóhoz](https://github.com/GMarcell1/WSMZR9parhuzamos/tree/main/WSMZR9_beadand%C3%B3)


## Optimális prefixszámítás

A program kiszámítja az optimális prefixet.
Akkor oldódik meg a feladat, ha a tömb mérete 2 valamelyik hatványa vagy hozzá közeli szám.

Amit elméleten vettünk optimális prefix számítás, azalapján oldottam meg a feladatot. Nem használtam Y segédtömböt, helyette az eredeti tömbbe helyettesítettem be.

Első két for ciklusba kiszámolom az Y segédtömböt, utána a következő for ciklusba kiszámolom a Z segédtömböt, valamint az utolsó for ciklusban megfelelően kijön a prefix számítás.


## Tömb

A program létrehoz egy tömböt. Megkeresi az összes prímszámot nem párhuzamosan.
A tömböt annyi részre osztja ahány szálunk van és úgy hasonlítja össze őket párhuzamosan, hogy prímszámok-e.
A végén összeadja a taskban tárolt prímszám előfordulásokat.


## Java

Létrehoztam egy osztályt amely implementál egy runnable interface-t.
Az fog lefutni párhuzamosan ami a run metódusban van.
Elsőször egy osztályt kell példányosítani utána egy thread osztályt, aminek a konstruktának a paramétere az előző osztály.

Start-tal elkezdjük, a join-nal pedig bevárják egymást és csak utána folytatódhatnak a további kódok.
