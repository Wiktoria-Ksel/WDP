---

## Wprowadzenie

Liczbą kolosalną nazwiemy reprezentację nieujemnej liczby całkowitej za
pomocą listy cyfr, które również są liczbami kolosalnymi. Reprezentacja ta,
opisana w inny, ale równoważny sposób, była rozważana przez Donalda Knutha.

Wartością liczby kolosalnej jest suma potęg dwójki o wykładnikach będących
wartościami cyfr tej liczby.

Powiemy, że liczba kolosalna jest znormalizowana, jeśli jej cyfry są
znormalizowane, i są one uporządkowane (ściśle) malejąco według wartości.
Każda nieujemna liczba całkowita ma dokładnie jedną reprezentację w postaci
znormalizowanej liczby kolosalnej.

Tekstowym zapisem liczby kolosalnej jest słowo języka z poniższą gramatyką
w rozszerzonej notacji BNF:

```text
<kolosalna> ::= { "1" <cyfra> } "0"
<cyfra> ::= <kolosalna>
```

Można udowodnić, że jest to język słów powstałych przez dopisanie symbolu
`0` na koniec wyrażenia nawiasowego, w którym `1` pełni rolę nawiasu
otwierającego, a `0` to nawias zamykający.

Tekstowy zapis liczby kolosalnej można przekształcić na niepozycyjny
zapis binarny. W tym celu:

- symbole `0`, `1`, zamieniamy na bity `0`, `1`;

- na końcu dopisujemy tyle bitów `0`, ile potrzeba, by długość ciągu była
  podzielna przez osiem;

- ciąg bitów dzielimy na porcje po osiem i umieszczamy je w kolejnych
  bajtach;

- w danym bajcie bity zapisujemy, zaczynając od pozycji najbardziej
  znaczących.

Wszystkie liczby kolosalne, których zapisem są poniższe słowa:

```text
101010101010101010100
110010110011001010100
1100101110001010100
1100101010101110000
1100110010101110000
11100010101110000
10101110001110000
11100011100011000
1101100011000
1110010011000
```

mają wartość dziesięć. Ostatnia z nich jest znormalizowana.

Inne przykłady znormalizowanych liczb kolosalnych są poniżej:

- `0` to `0`
- `1` to `100`
- `2` to `11000`
- `3` to `1100100`
- `4` to `1110000`
- `5` to `111000100`
- `6` to `11100011000`
- `7` to `1110001100100`
- `8` to `111001000`
- `9` to `11100100100`
- `10` to `1110010011000`
- `11` to `111001001100100`
- `12` to `111001001110000`
- `13` to `11100100111000100`
- `14` to `1110010011100011000`
- `15` to `111001001110001100100`
- `16` to `111100000`
- `17` to `11110000100`
- `18` to `1111000011000`
- `19` to `111100001100100`
- `20` to `111100001110000`
- `50` to `11110001001111000011000`
- `64` to `1111000110000`
- `100` to `11110001100011110001001110000`
- `127` to `111100011000111100010011110000111001001110001100100`
- `128` to `111100011001000`
- `144` to `11110001100100111100000`
- `199` to `111100011001001111000110001110001100100`
- `256` to `11110010000`
- `1000` to `1111001001001111001000111100011001001111000110001111000100111001000`
- `1009` to `111100100100111100100011110001100100111100011000111100010011110000100`
- `1024` to `111100100110000`
- `10000` to `111100100111000100111100100110001111001001001111001000111100000`
- `65536` to `11111000000`
- `200791` to `11111000010011111000001111001001110000111100011000111100001110001100100`
- `2^65536` to `1111110000000`
- `2^65537` to `111111000001000`
- `2^(2^65536)` to `111111100000000`
- `2^(2^(2^65536))` to `11111111000000000`
- `5+2^(2^(2^65536))` to `1111111100000000111000100`

Pozycyjny zapis binarny trzech ostatnich wymienionych wartości miałby
więcej bitów, niż jest atomów na Ziemi. Niepozycyjny zapis binarny
liczb kolosalnych ma, odpowiednio, 2, 3 i 4 bajty.

## Polecenie

Zaimplementuj kalkulator umożliwiający wykonywanie obliczeń na liczbach
kolosalnych.

Kalkulator ma pamięć, która jest stosem. Na początku stos jest pusty.

Program czyta z wejścia polecenia i wykonuje je. Kończy pracę, gdy
polecenia się skończą.

## Postać danych

Dane to ciąg wierszy. W każdym wierszu jest jedno polecenie.

Program rozpoznaje polecenia i wykonuje odpowiednie akcje:

- tekstowy zapis liczby kolosalnej, niekoniecznie znormalizowanej:

  włóż na stos wczytaną liczbę;

- kropka `'.'`:

  zdejmij liczbę ze stosu i wypisz ją na wyjście;

- dwukropek `':'`:

  zduplikuj liczbę, czyli zdejmij ją ze stosu i włóż ją na stos
  dwukrotnie;

- daszek `'^'`:

  zdejmij liczbę ze stosu i włóż na stos potęgę `2`, w której ta
  liczba jest wykładnikiem;

- plus `'+'`:

  zdejmij ze stosu dwie liczby i włóż na stos ich sumę;

- razy `'*'`:

  zdejmij ze stosu dwie liczby i włóż na stos ich iloczyn.

Oprócz znaków wymienionych powyżej, na wejściu nie ma żadnych innych.

Zakładamy, że zawsze, gdy program będzie zdejmował wartość ze stosu,
stos będzie niepusty.

Nie zakładamy, że po wykonaniu ostatniego polecenia stos będzie pusty.

## Postać wyniku

Wynikiem programu jest ciąg wierszy, po jednym dla każdego wykonanego
polecenia kropka `'.'`. W wierszu jest tekstowa reprezentacja
znormalizowanej liczby kolosalnej.

## Przykłady

Do treści zadania dołączone są pliki `.in` z przykładowymi danymi i pliki
`.out` z wynikami wzorcowymi.

- Dla danych
  [
  przyklad1.in
  ](https://moodle.mimuw.edu.pl/pluginfile.php/374551/mod_folder/content/0/przyklad1.in?forcedownload=1)
  poprawny wynik to
  [
  przyklad1.out
  ](https://moodle.mimuw.edu.pl/pluginfile.php/374551/mod_folder/content/0/przyklad1.out?forcedownload=1).

- Dla danych
  [
  przyklad2.in
  ](https://moodle.mimuw.edu.pl/pluginfile.php/374551/mod_folder/content/0/przyklad2.in?forcedownload=1)
  poprawny wynik to
  [
  przyklad2.out
  ](https://moodle.mimuw.edu.pl/pluginfile.php/374551/mod_folder/content/0/przyklad2.out?forcedownload=1).

- Dla danych
  [
  przyklad3.in
  ](https://moodle.mimuw.edu.pl/pluginfile.php/374551/mod_folder/content/0/przyklad3.in?forcedownload=1)
  poprawny wynik to
  [
  przyklad3.out
  ](https://moodle.mimuw.edu.pl/pluginfile.php/374551/mod_folder/content/0/przyklad3.out?forcedownload=1).

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
  zawartość pliku `.in` i porównując rezultat, za pomocą programu `diff`,
  z plikiem `.out`, np.:

  ```bash
  < przyklad.in ./nazwa | diff - przyklad.out
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

- Rozwiązanie zadania wymaga zastosowania rekursji i pamięci dynamicznej.

- Program nie powinien nakładać żadnych ograniczeń na rozmiar danych
  i wyniku. Wolno tylko założyć, że zmieszczą się one na stercie
  (w pamięci dynamicznej).

- Nie trzeba się obawiać przepełnienia stosu podczas wykonania poprawnego
  algorytmu rekurencyjnego.

- Oczekujemy rozwiązania o koszcie wielomianowym względem rozmiaru
  danych.

- By znormalizować liczbę kolosalną trzeba posortować jej cyfry
  i zsumować cyfry powtarzające się.

- Znormalizowane liczby kolosalne porównujemy cyfra po cyfrze, zaczynając
  od cyfr największych.

- Obliczenie sumy znormalizowanych liczb kolosalnych wymaga scalenia
  list ich cyfr. W przypadku, gdy ta sama cyfra występuje w obu
  dodawanych liczbach, realizujemy przeniesienie.

  Do scalenia list cyfr potrzebujemy porównania liczb.

- Iloczyn dwóch liczb kolosalnych można wyznaczyć, korzystając ze wzoru:

  $$
  \left( \sum_{i=0}^m 2^{a_i} \right) \left( \sum_{j=0}^n 2^{b_j} \right) = \sum_{i=0}^m \sum_{j=0}^n 2^{a_i+b_j}
  $$

  Będzie do tego potrzebne dodawanie.

- Tekstowy zapis liczby kolosalnej, niekoniecznie znormalizowanej, można
  przekształcić na wyrażenie arytmetyczne. W tym celu należy kolejno:

  - zastąpić każdy znak `'1'` znakiem `'('`;

  - zastąpić każdy znak `'0'` znakiem `')'`;

  - między każdą parą znaków `'('` i `')'` wstawić znak `'0'`;

  - między każdą parą znaków `')'` i `'('` wstawić znak `'+'`;

  - przed każdym znakiem `'('` wstawić `"2^"`;

  - zamiast ostatniego znaku `')'` wstawić `"-0"`.

  Przekształcenie to można zrealizować za pomocą programu `sed`, który
  zastępuje wzorce w tekście, wykonując polecenie:

  ```text
  sed 's:1:(:g; s:0:):g; s:():(0):g; s:)(:)+(:g; s:(:2^(:g; s:)$:-0:g'
  ```

  Wartość wyrażenia można obliczyć, i wypisać w postaci dziesiętnej,
  korzystając z kalkulatora wyrażeń arytmetycznych `bc`.

  Np. polecenie:

  ```bash
  echo 11110001001111000011000 | sed 's:1:(:g; s:0:):g; s:():(0):g; s:)(:)+(:g; s:(:2^(:g; s:)$:-0:g' | bc
  ```

  wypisze:

  ```text
  50
  ```

  Program `bc` używa pozycyjnej reprezentacji liczb. Próba użycia go do
  przekształcenia na postać dziesiętną dużej liczby kolosalnej, np.
  `111111100000000`, zakończy się błędem.

  W rozwiązaniu zadania nie wolno korzystać z programów `sed` i `bc`,
  ale mogą one pomóc w testowaniu.
