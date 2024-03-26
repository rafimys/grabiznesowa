# grabiznesowa
Projekt polega na napisaniu bardzo prostej gry ekonomicznej (symulacji przedsiębiorstwa), rozgrywanej w konsoli. Gracz prowadzi swoją firmę, a celem gry jest osiągnięcie określonej wartości spółki. Firma produkuje produkt, który magazynuje i sprzedaje. Może ona zatrudniać różne typy pracowników, a także brać kredyty. Gra odbywa się systemem turowym: co miesiąc gracz decyduje ilu i jakich pracowników zatrudnić oraz czy wziąć kredyt i zatwierdza koniec miesiąca. Na podstawie typu i liczby zatrudnionych pracowników liczona jest informacja o liczbie sprzedanych produktów. Następnie zwracana jest informacja o stanie finansowym spółki w następnym miesiącu. Jeżeli wartość spółki (pomniejszona o zadłużenie) przekracza określoną wartość, gra kończy się zwycięstwem. Jeżeli bilans konta spadnie poniżej zera, firma bankrutuje i gra kończy się przegraną. Jeżeli żaden z tych warunków nie nastąpi, gra toczy się dalej (kolejna tura).

Szczegóły gry
Typy pracowników
Firma może zatrudniać następujące typy pracowników

Inżynier(ka) - zwiększa wartość produktu
Magazynier(ka) - zwiększa pojemność magazynu, która narzuca górny limit liczby produktów, które mogą zostać sprzedane w danym miesiącu
Marketer(ka) - zwiększa liczbę sprzedanych co miesiąc produktów (generuje popyt)
Robotni(k/czka) - produkuje produkty (generuje podaż)
Każdy pracownik ma imię oraz ustalone wynagrodzenie, które musi zostać wypłacone na koniec miesiąca. Imię jest ustalane w trakcie zatrudniania pracownika (możesz użyć dostarczonego przez prowadzącego generatora imion losowych). Wynagrodzenie jest stałe dla wszystkich pracowników danego typu (np. wszyscy inżynierowie zarabiają X).

Każdy typ pracownika posiada zdefiniowaną stałą wydajności, ustalaną w jednym miejscu w kodzie (zapewne jako stałe pole statyczne odpowiednich klas). Stałe wydajności oznaczmy (w kolejności zawodów wymienionej wyżej): CI, CMag, CMkt, CR.

Dodatkowo, każdy z typów pracowników posiada dodatkową indywidualną cechę:

Inż. - nazwa skończonego wydziału
Mag. - czy może obsługiwać wózek widłowy (tak lub nie)
Mkt. - liczba obserwujących na mediach społecznościowych (liczba całkowita)
Rob. - rozmiar buta (załóżmy, że jest to liczba zmiennoprzecinkowa)
Gra powinna dać możliwość wyświetlenia listy zatrudnionych pracowników wraz z ich cechami (kolejność może być dowolna).

Pojemność magazynu
Pojemność magazynu równa jest iloczynowi liczby magazynierów i stałej CMag.

Cena produktu
Cena produktu równa jest iloczynowi liczby inżynierów i stałej CI.

Popyt
Popyt na produkty równy jest iloczynowi liczby marketerów i stałej CMkt.

Sprzedaż produktów
Sprzedaż odbywa się wg. następującego schematu:

Teoretycznie możliwa iczba wyprodukowanych w danym miesiącu produktów równa jest iloczynowi liczby robotników i stałej CR.
Liczba faktycznie wyprodukowanych w danym miesiącu produktów równa jest mniejszej z wartości: pojemność magazynu, teoretycznie możliwa liczba wyprodukowanych produktów.
Liczba sprzedanych w danym miesiącu produktów równa jest mniejszej z wartości: popyt, liczba faktycznie wyprodukowanych produktów.
Przychód firmy równy jest iloczynowi liczby sprzedanych produktów i ceny produktu.
Do powyższego schematu może (ale nie musi) zostać wprowadzony czynnik losowy. Wykonujący projekt może także (ale nie musi) zaimplementować magazyn w taki sposób, że niesprzedane w danym miesiącu produkty pozostają na stanie w miesiącu kolejnym.

Wartość spółki
Wartość spółki definiujemy jako średni przychód firmy z ostatnich N miesięcy, gdzie N to stała zdefiniowana w programie.

Kredyty
Gracz może w każdej turze zaciągnąć kredyt, który musi później spłacić. Biorąc kredyt gracz ustala jego kwotę oraz czas spłaty. Odsetki ustalane są wg. zasady: im dłuższy czas spłaty, tym wyższe odsetki (szczegóły pozostawiamy wykonującemu projekt). Czas spłaty powinien mieć górny limit (nie można zaciągnąć kredytu na dłużej niż X). Dodatkowo, całkowite zadłużenie nie może przekroczyć wartości M razy wartość spółki, gdzie M to stała zdefiniowana w programie.

Dochód
W każdym miesiącu stan konta gracza zwiększany (lub zmniejszany) jest o kwotę dochodu, liczoną wg. wzoru:

dochód = przychód - wynagrodzenie pracowników - raty zaciągniętych pożyczek

Stan początkowy
Na początku gry firma gracza posiada po jednym pracowniku każdego rodzaju oraz stałą (ustaloną w programie) kwotę na koncie.

Przebieg gry
Gra odbywa się w całości w konsoli. Na początku powinien zostać wyświetlony komunikat o możliwych akcjach gracza oracz początkowym stanie firmy. Następnie gracz może wpisać z klawiatury komendę, na przykład:

lp - wylistuj pracowników (imiona i wynagrodzenia)
zinz - zatrudnij inż.
zmag - zatrudnij mag.
zmkt - zatrudnij mark.
zrob - zatrudnij rob.
kred - weź kredyt (w następnym kroku podaj kwotę i czas spłaty)
kt - zakończ turę i wyświetl stan firmy na początku następnego miesiąca
