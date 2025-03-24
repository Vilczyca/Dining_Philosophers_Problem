# Problem jedzących filozofów

## Opis problemu
Problem jedzących filozofów jest jednym z zagadnień, pozwalających zwizualizować zagadnienie synchronizacji w systemach operacyjnych. Zadanie polega na symulacji sytuacji, w której kilka filozofów siedzi wokół okrągłego stołu i musi dogadać się, kto weźmie widelec. Filozofowie naprzemiennie myślą i jedzą, ale potrzebują dwóch widelców (lub pałeczek, w zależności od wersji), aby nałożyć jedzenie na swój talerz i spokojnie zjeść obiad. Filozofowie muszą współdzielić widelce, co może prowadzić do problemów takich jak:
- **zakleszczenie** (deadlock) - sytuacja, w której co najmniej dwa procesy się wzajemnie blokują, ponieważ każdy korzysta z zasobu, który jest potrzebny temu drugiemu (np. w wersji z dwoma myślicielami filozof A czeka na widelec wykorzystywany przez B, a filozof B czeka na widelec używany przez A).
-  **głodowanie** (starvation) - sytuacja, w której proces nie ma dostępu do zasobów, ponieważ są one stale wykorzystywane przez procesy o wyższym priorytecie. Niektórzy filozofowie mogą "głodować", jeśli nie będą w stanie uzyskać obu widelców, podczas gdy inni będą jedli.

# Wątki i ich reprezentacja
Każdy filozof działa na osobnym wątku, wykonując funkcję `doWork`, w której na zmianę myśli i próbuje jeść. Filozofowie próbują zabrać oba widelce, stosując różne strategie synchronizacji.

# Sekcje krytyczne i ich rozwiązanie
Sekcja krytyczna występuje, gdy filozofowie próbują jednocześnie zabrać te same widelce. Aby uniknąć współdzielenia widelca przez dwa wątki w tym samym czasie, stosowane są mechanizmy synchronizacji. Dodatkowo, każdy widelec jest reprezentowany przez `mutex`, który zapewnia wyłączny dostęp do widelca. Filozofowie muszą zablokować oba widelce przed jedzeniem i zwolnić je po zakończeniu posiłku.

## Strategie synchrinozacji:
- **Podstawowe blokowanie:** Filozofowie próbują zabrać widelce jeden po drugim. Może to prowadzić do zakleszczenia, jeśli wszyscy filozofowie jednocześnie wezmą lewy widelec i będą czekać na prawy.
- **Asymetryczne blokowanie:** Filozofowie o parzystym numerze ID biorą prawy widelec przed lewym, a filozofowie o nieparzystym numerze ID biorą lewy widelec przed prawym, co zmniejsza ryzyko zakleszczenia.
- **Wzorzec kelnera:** Filozofowie blokują oba widelce jednocześnie za pomocą lock i lock_guard, co zapewnia brak zakleszczenia, ale wymaga dłuższego oczekiwania na oba widelce.

## Instrukcja uruchamiania projektu

### Wymagania
- Kompilator C++
- Standard C++ 11 lub wyższy

### Jak uruchomić:

Sugerowanym sposobem uruchomienia programu jest użycie IDE mające zintegrowany kompilator C++, takich jak:
- Visual Studio
- CLion
- Code::Blocks

Jednakże, projekt ten można również ręcznie skompilować. Należy się jednak upewnić, że środowisko dla kompilatora jest poprawnie skonfigurowane.

1. Klonowanie repozytorium
   ```bash
   git clone https://github.com/Vilczyca/Dining_Philosophers_Problem.git
   cd Dining_Philosophers_Problem
   ```
2. Kompilacja projektu
   ```bash
   g++ -std=c++11 -o main main.cpp
   ```
3. Uruchomienie programu
   ```bash
   ./main [philosophers_number]
   ```
Zgodnie z założeniami projektu, program otrzymuje jako argument liczbę filozofów biorących udział w uczcie. Domyślnie, liczba filozofów wynosi 5, zgodnie z klasycznym sformuowaniem problemu.


