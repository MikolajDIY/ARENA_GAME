
<div align="center">
  <img src="img/for_Readme_file/TheArena.jpg" width="600" alt="Tytuł Gry">
</div>

The Arena Game jest to turowa gra 2D z elementami RPG, napisana w języku C++ z wykorzystaniem biblioteki graficznej SFML. Gracz mierzy się z kolejnymi falami przeciwników, ulepszając swój ekwipunek pomiędzy starciami.

## Widok gry
### Menu główne
<div align="center">
  <img src="img/for_Readme_file/Menu.png" width="600" alt="Menu">
</div>

### Walka
<div align="center">
  <img src="img/for_Readme_file/Game.png" width="600" alt="Game">
</div>

### Sklep
<div align="center">
  <img src="img/for_Readme_file/Shop.png" width="600" alt="Shop">
</div>

## Użyte technologie
* **Język główny:** C++
* **Biblioteka graficzna:** SFML 2.6.2
* **Kompilator:** MinGW GCC x86 13.1.0
* **Środowisko:** Code::Blocks 25.3
* **System operacyjny:** Windows 11

## Kluczowe funkcjonalności
* **System walki turowej** z różnymi typami ataków (Basic, Reckless, Risky, Combo).
* **Dynamiczne skalowanie trudności** i system fal przeciwników.
* **Sklep** pozwalający na zakup lepszego pancerza i broni za zdobyte złoto.
* **Solidna architektura** oparta na maszynie stanów i polimorfizmie.
* **Zapis i odczyt** stanu gry z pliku.
* **Komunikaty** potwierdzające wykonanie kluczowych operacji.

## Instrukcja kompilacji i uruchomienia
Aby poprawnie skompilować i uruchomić grę, postępuj zgodnie z poniższymi krokami:

1. **Środowisko:** Zainstaluj najnowszą wersję środowiska IDE **Code::Blocks**.
2. **Repozytorium:** Pobierz repozytorium projektu i wypakuj je w wybranym miejscu docelowym.
3. **Struktura katalogów:** Otwórz główny folder projektu (`ARENA_GAME`) i utwórz w nim nowy podkatalog o nazwie `ext`.
4. **Instalacja SFML:** Pobierz bibliotekę graficzną **SFML w wersji 2.6.2** i wypakuj jej zawartość do utworzonego wcześniej folderu `ext`.
5. **Kompilator (Ważne!):** Biblioteka SFML 2.6.2 może nie współpracować poprawnie z najnowszymi dystrybucjami kompilatora MinGW. Do poprawnej kompilacji zalecana jest instalacja i użycie sprawdzonej wersji: **MinGW GCC 13.1.0**.

## Autorzy
**Zespół:** Mikołaj Ratajczak, Zuzanna Ratajczak, Filip Sakowicz

**Kontekst:** Projekt zrealizowany w ramach zaliczenia laboratorium z przedmiotu **Programowanie Strukturalne i Obiektowe** realizowanego na **Politechnice Poznańskiej**.