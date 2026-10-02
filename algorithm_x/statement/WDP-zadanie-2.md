---

## Wprowadzenie

Rozwiązaniem problemu
[
dokładnego pokrycia
](https://en.wikipedia.org/wiki/Exact_cover),
dla rodziny $P$ podzbiorów dziedziny $S$, jest taki zbiór $Q \subseteq P$,
że każdy element dziedziny $S$ należy do dokładnie jednego elementu $Q$.

Problem dokładnego pokrycia jest
[
NP-zupełny
](https://en.wikipedia.org/wiki/NP-completeness).
Nie jest znany deterministyczny algorytm rozwiązujący go w czasie
wielomianowym. Algorytm o koszcie wykładniczym, stosujący *metodę prób
i błędów*, jest przez Donalda Knutha nazywany
[
Algorytmem X
](https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X).

Wiele problemów, np. łamigłówki, można sprowadzić do problemu dokładnego
pokrycia. Pomimo wykładniczej złożoności, efektywność rozwiązania
problemu za pomocą Algorytmu X może być dla użytkownika akceptowalna.

## Polecenie

Napisz program czytający ciąg wierszy $F, W_1, \dots, W_n$, w którym $F$
to *filtr*, a $W_1, \dots, W_n$ jest reprezentacją pojedynczej instancji
problemu dokładnego pokrycia.

Wszystkie czytane wiersze są tej samej długości $d$. Wiersz $F$ składa się
ze znaków minus `-` i plus `+`. Każdy wiersz $W_1, \dots, W_n$ jest ciągiem
dowolnych znaków, z których co najmniej jeden jest różny od podkreślenia
`_`.

W rozważanej instancji dziedziną jest $S = \{ 1, \dots, d \}$.
Wiersze $W_1$ do $W_n$ reprezentują rodzinę $P$ podzbiorów $S$ w ten
sposób, że $W_j$ reprezentuje $j$-ty zbiór $P_j$ w tej rodzinie.
Element $k \in S$ należy do zbioru $P_j$ wtedy i tylko wtedy, gdy $k$-ty
znak wiersza $W_j$ jest różny od znaku podkreślenia.

Wynikiem programu jest ciąg wierszy reprezentujących wszystkie możliwe
rozwiązania instancji $W_1, \dots, W_n$, przekształconych następnie za
pomocą filtru $F$ przez usunięcie znaków z pozycji, na których w filtrze
jest `-`.

Rozwiązaniem instancji $W_1, \dots, W_n$ jest zbiór
$T \subseteq \{1, \dots, n \}$. Zbiór ten jest reprezentowany przez tekst
$R$ długości $d$, który nie zawiera znaku podkreślenia `_` i spełnia
warunek:

$$
\forall_{1 \leq i \leq d} \exists_{j \in T}((W_j)_i = R_i \land \forall_{k \in T \setminus \{j\}} (W_k)_i = \_)
$$

Rozwiązania budujemy ze znaków wierszy $W_1, \dots, W_n$, zgodnie z ich
kolejnością. W danym rozwiązaniu, w kolejności od początku, wybieramy
metodą prób i błędów znaki niekolidujące z wyborami dokonanymi wcześniej.

Kolejność rozważania wierszy danych oraz ich kolumn może mieć wpływ
na kolejność wierszy wynikowych, ale nie będzie miała wpływu na to, jakie
wiersze program wypisze.

## Przykłady

Do treści zadania dołączone są pliki `.in` z przykładowymi danymi i pliki
`.out.sorted` z wynikami wzorcowymi.

- Dla danych
  [
  przyklad1.in
  ](https://moodle.mimuw.edu.pl/pluginfile.php/372280/mod_folder/content/0/przyklad1.in?forcedownload=1)
  poprawny wynik, po posortowaniu wierszy, to
  [
  przyklad1.out.sorted
  ](https://moodle.mimuw.edu.pl/pluginfile.php/372280/mod_folder/content/0/przyklad1.out.sorted?forcedownload=1).

- Dla danych
  [
  przyklad2.in
  ](https://moodle.mimuw.edu.pl/pluginfile.php/372280/mod_folder/content/0/przyklad2.in?forcedownload=1)
  poprawny wynik, po posortowaniu wierszy, to
  [
  przyklad2.out.sorted
  ](https://moodle.mimuw.edu.pl/pluginfile.php/372280/mod_folder/content/0/przyklad2.out.sorted?forcedownload=1).

- Dla danych
  [
  przyklad3.in
  ](https://moodle.mimuw.edu.pl/pluginfile.php/372280/mod_folder/content/0/przyklad3.in?forcedownload=1)
  poprawny wynik, po posortowaniu wierszy, to
  [
  przyklad3.out.sorted
  ](https://moodle.mimuw.edu.pl/pluginfile.php/372280/mod_folder/content/0/przyklad3.out.sorted?forcedownload=1).

## Walidacja i testy

- Rozwiązania podlegają walidacji, wstępnie badającej zgodność ze
  specyfikacją.

  Walidacja sprawdza działanie programu na przykładach dołączonych do
  treści zadania.

  Pomyślne przejście walidacji jest warunkiem dopuszczenia programu do
  testów poprawności. Program, który walidacji nie przejdzie, dostaje
  zerową ocenę poprawności.

- Walidacja i testy są prowadzone na komputerze `students`.

- Programy są kompilowane poleceniem:

  ```bash
  gcc @opcje nazwa.c -o nazwa
  ```

  gdzie `nazwa.c` to nazwa pliku z kodem źródłowym, a plik `opcje` ma
  zawartość:

  ```text
  -std=c23
  -pedantic
  -Wall
  -Wextra
  -Wformat-security
  -Wduplicated-cond
  -Wfloat-equal
  -Wshadow
  -Wconversion
  -Wjump-misses-init
  -Wlogical-not-parentheses
  -Wnull-dereference
  -Wvla
  -Werror
  -fstack-protector-strong
  -fsanitize=undefined
  -fno-sanitize-recover
  -g
  -fno-omit-frame-pointer
  -O1
  ```

  Opcje `-std=c23`, `-pedantic` wskazują, że kompilator ma dbać
  o zgodność kodu z aktualnym standardem języka C.

  Dzięki opcjom `-Wall`, `-Wextra` kompilator zgłosi zauważone usterki.

  Opcje `-Wformat-security`, `-Wduplicated-cond`, `-Wfloat-equal`,
  `-Wshadow`, `-Wconversion`, `-Wjump-misses-init`,
  `-Wlogical-not-parentheses`, `-Wnull-dereference` umożliwiają
  wykrywanie dodatkowych usterek.

  Opcja `-Wvla` sprawia, że użycie tablic zmiennej długości jest uznawane
  za usterkę.

  Opcja `-Werror` wskazuje, że kompilator ma uznać usterki za błędy.

  Dzięki opcji `-fstack-protector-strong`, podczas wykonania programu
  zostaną wykryte niektóre błędne odwołania do pamięci na stosie.

  Opcje `-fsanitize=undefined`, `-fno-sanitize-recover` umożliwiają
  wykrywanie operacji, które mają efekt nieokreślony.

  Opcje `-g`, `-fno-omit-frame-pointer` poprawiają jakość komunikatów
  o błędach wykonania.

  Opcja `-O1` włącza optymalizacje, co zwiększa prawdopodobieństwo
  ujawnienia się błędów.

  Wymagane są wszystkie wymienione opcje kompilatora. Nie będą do nich
  dodawane żadne inne.

  Zwracamy uwagę, że poszczególne wersje kompilatora `gcc` mogą się
  różnić sposobem obsługi tych samych opcji. Przed wysłaniem rozwiązania
  warto więc skompilować je i przetestować na `students` w sposób
  opisany powyżej.

- Podczas walidacji i testów, program `nazwa` jest uruchamiany pod
  kontrolą programu Valgrind poleceniem:

  ```bash
  valgrind --leak-check=full -q --error-exitcode=1 ./nazwa
  ```

  Jeśli Valgrind wykryje błąd, to nawet gdyby wynik był prawidłowy,
  uznajemy, że program testu nie przeszedł.

  Opcja `-q` powoduje, że jedynymi informacjami, wypisywanymi przez
  program Valgrind, są komunikaty o błędach.

  Opcja `--leak-check=full` wskazuje Valgrindowi, że powinien, między
  innymi, szukać wycieków pamięci.

  Opcja `--error-exitcode=1` określa kod wyjścia programu w przypadku,
  gdy Valgrind wykryje błąd.

- Przyjmujemy, że niezerowy wynik funkcji `main()` informuje o błędzie
  wykonania programu.

- Poprawność wyniku sprawdzamy, przekierowując na wejście programu
  zawartość pliku `.in` i porównując, za pomocą programu `diff`, rezultat,
  po jego posortowaniu programem `sort`, z plikiem `.out.sorted`, np.:

  ```bash
  < przyklad.in ./nazwa | sort | diff - przyklad.out.sorted
  ```

  Ocena poprawności wyniku jest binarna. Wynik uznajemy za poprawny,
  jeżeli program `diff` nie wskaże żadnej różnicy względem wyniku
  wzorcowego.

## Uwagi i wskazówki

- Jako rozwiązanie należy wysłać plik tekstowy `.c` z kodem źródłowym
  w języku C.

- Wolno założyć, że dane są poprawne.

- Wolno założyć, że każdy wiersz danych, w tym ostatni, kończy się
  reprezentacją końca wiersza `'\n'`.

  Należy zadbać, by warunek ten spełniał także wynik programu.

- Wolno założyć, że na wejściu programu jest nie więcej niż 200
  wierszy.

- Wolno założyć, że długość wiersza na wejściu programu nie przekracza
  300\.

- Naturalnym sposobem implementacji metody prób i błędów jest rekursja.

- Donald Knuth opisuje implementację Algorytmu X za pomocą dość złożonej
  struktury danych, opartej na liście dwukierunkowej, z zastosowaniem
  techniki
  [
  tańczących wskaźników
  ](https://en.wikipedia.org/wiki/Dancing_Links).

  Nie oczekujemy takiej implementacji. Ograniczenie na rozmiar danych
  wejściowych pozwala na użycie, jako struktury danych, zwykłej tablicy.
  Za takie rozwiązanie będzie można dostać ocenę maksymalną.

  Oczywiście nie zabraniamy używania pamięci dynamicznej. Nie będzie
  za to kary, ale też nie zostanie to w żaden sposób nagrodzone.

- Algorytm X ma złożoność wykładniczą. Nawet na małych danych może
  działać bardzo długo. Dane do testów zostaną jednak dobrane tak, by
  prosta implementacja tego algorytmu, bez żadnych usprawnień, bez
  problemu zmieściła się w limicie czasu obowiązującym podczas walidacji
  i testów.
