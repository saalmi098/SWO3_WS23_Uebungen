# SWO3 - BB - WS 2023/24 Kurztest 1

**Prüfer:** G1: Winkler, MSc; G2: Purgin, MSc

**Datum:** Samstag 21.10.2023, **Dauer:** 15 Min, **erlaubte Unterlagen:** Online-Referenzen: [www.cplusplus.com](www.cplusplus.com), [www.cppreference.com](www.cppreference.com)

**Name:**



**Gruppe:**


**Punkte:** ___ von 6

## Aufgabe: Interleave (1 + 3 + 2 Punkte)


**Hinweis:** Die Angabe von `#includes` ist nicht notwendig.

Schreiben Sie eine Funktion, die zwei Zeichenketten zusammenfügt und dabei zwischen den Zeichenketten hin und her wechselt. Das Ergebnis soll in einer neu allokierten Zeichenkette mit genau der richtigen Länge platziert werden. Die beiden Zeichenketten müssen gleich lang sein. Stellen Sie das mit einem `assert` in der Funktion sicher.

```c
char* interleave(const char *a, const char *b);
// Beispiel
interleave("abcd", "1234")  // -> "a1b2c3d4"
interleave("abc",  ",,,")   // -> "a,b,c,"
```

**a.** In der Funktion muss der Speicher mit `malloc` allokiert werden. Welche beiden Punkte sind zu beachten, wenn Sie `malloc` verwenden?

Lösung a:

```c

```

**b.** Implementieren Sie die Funktion mit der oben beschriebenen Schnittstelle. Achten Sie dabei besonders auf das korrekte Reservieren von neuem Speicher in der richtigen Größe und denken Sie auch an das Terminationszeichen (`'\0'`) am Ende aller Zeichenketten. Für die Implementierung der Funktion dürfen Sie nur die Funktion `strlen()` aus der Standardbibliothek verwenden.

Lösung b:

```c

```

**c.** Schreiben Sie ein vollständiges Hauptprogramm, das die Funktion testet und eine sinnvolle Ausgabe erzeugt, in der die Funktionsweise nachvollzogen werden kann. Achten Sie dabei auch auf eine saubere Speicherverwaltung. Für die Implementierung der `main()`-Funktion können beliebige weitere Funktionen aus der Standardbibliothek verwendet werden.

Lösung c:

```c


```
