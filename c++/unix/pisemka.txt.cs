Príklady ke zkousce z UNIXu
===========================

Písemka obsahuje dva príklady, po jednom z cástí (A) a (B).

Obecné pokyny
-------------

Nezapomente se na své resení podepsat a napsat císla príkladu.

Alespon u 1 volání naznacte, jak byste standardním zpusobem osetrili prípadnou
chybu. Ve zbytku programu muzete predpokládat, ze vsechny funkce skoncí
správne, a nezabývat se osetrováním chyb.

Nezapomente, ze presmerování, roury a zpracování expanzních znaku provádí
shell (tj. má to delat vás program, kterým simulujete shell). Pouzívejte
správnou variantu sluzby exec (pouzití PATH, zpusob zadání argumentu). Piste
program tak, aby nezálezelo na tom jestli (a jaké) dostane pri svém spustení
deskriptory otevrených souboru (napr. nemusí dostat otevrené deskriptory 0,
1, 2). Vsechna jména souboru vzniklá z expanzních znaku se predávají na
príkazové rádce najednou jednomu programu jako samostatné argumenty (program
se nespoustí opakovane pro jednotlivé soubory). Pri implementaci presmerování
('príkaz soubor', 'príkaz <soubor') nepouzívejte roury. Snazte se omezit pocet
pouzívaných procesu a rour na nezbytné minimum.

Pokud potrebujete synchronizovat procesy, vyhnete se aktivnímu cekání, místo
toho pouzívejte funkce, které zablokují proces, dokud nenastane ocekávaná
událost. Snazte se blokovat procesy pouze tehdy, kdy je to skutecne nutné.

Pouzívejte systémová volání (napr. open, read, write, pipe), ne knihovní
funkce (napr. fopen,fread, fwrite, fprintf, popen).

Pokud nevíte, co provádí príkaz shellu, který máte simulovat, tak se radeji
zeptejte (neznalost shellu nemá vliv na známku) a nevymýslejte si, co by to
mohlo delat.

Obecné pokyny
-------------

Nezapomente se na své resení podepsat a napsat císla príkladu.

Alespon u 1 volání naznacte, jak byste standardním zpusobem osetrili prípadnou
chybu. Ve zbytku programu muzete predpokládat, ze vsechny funkce skoncí
správne, a nezabývat se osetrováním chyb.

Nezapomente, ze presmerování, roury a zpracování expanzních znaku provádí
shell (tj. má to delat vás program, kterým simulujete shell). Pouzívejte
správnou variantu sluzby exec (pouzití PATH, zpusob zadání argumentu). Piste
program tak, aby nezálezelo na tom jestli (a jaké) dostane pri svém spustení
deskriptory otevrených souboru (napr. nemusí dostat otevrené deskriptory 0,
1, 2). Vsechna jména souboru vzniklá z expanzních znaku se predávají na
príkazové rádce najednou jednomu programu jako samostatné argumenty (program
se nespoustí opakovane pro jednotlivé soubory). Pri implementaci presmerování
('príkaz soubor', 'príkaz <soubor') nepouzívejte roury. Snazte se omezit pocet
pouzívaných procesu a rour na nezbytné minimum.

Pokud potrebujete synchronizovat procesy, vyhnete se aktivnímu cekání, místo
toho pouzívejte funkce, které zablokují proces, dokud nenastane ocekávaná
událost. Snazte se blokovat procesy pouze tehdy, kdy je to skutecne nutné.

Pouzívejte systémová volání (napr. open, read, write, pipe), ne knihovní
funkce (napr. fopen,fread, fwrite, fprintf, popen).

Pokud nevíte, co provádí príkaz shellu, který máte simulovat, tak se radeji
zeptejte (neznalost shellu nemá vliv na známku) a nevymýslejte si, co by to
mohlo delat.

A) Procesy, roury
-----------------

- spoustení procesu
- presmerování < > >>
- presmerování <& >& >>&
- roury
- pouzití argv
- pouzití env. var.
- zmena env. var.
- cekání na exit code
- ctení obsahu adresáre

VZOROVÝ PRÍKLAD
Napiste program v jazyce C, který simuluje cinnost shellu pri provádení
príkazu

find $HOME -name '*.c' 2>/dev/null | less

1.
Napiste program, který simuluje cinnost shellu pri interpretaci skriptu

/bin/kill -TERM `ps "$1"`
echo $?

Pro ctení výstupu vnoreného príkazu pouzijte rouru. Predpokládejte, ze vnorený
príkaz vypíse pouze jeden rádek, který muze obsahovat více slov (oddelených
mezerami). Kazdé slovo se predává príkazu kill jako samostatný parametr.

2.
Napiste program, který simuluje cinnost shellu pri provádení príkazu

ls -lR / 2>&1 | "$PAGER"

3.
Napiste program, který simuluje cinnost shellu pri interpretaci skriptu

find "$1" "$2" 2>errfile | xargs rm "$RMARG"

4.
Napiste program, který simuluje cinnost shellu pri interpretaci skriptu

for F in "$@"; do /usr/bin/grep '^#' "$F"; done 2>/dev/null | less

5.
Napiste program, který simuluje cinnost shellu pri interpretaci rádku

find / -type d -print 2>&1 | xargs cat >>outfile

6.
Napiste program, který simuluje cinnost shellu pri interpretaci skriptu

if grep "$REGEXP" "$1" >nalezeno 2>errfile; then echo NALEZENO;
else echo NENALEZENO; fi

Pouzijte externí príkaz (program) echo.

7.
Napiste program, který simuluje cinnost shellu pri interpretaci skriptu

I=1
while [ "$I" -le "$1" ]; do echo "$I"; I=$[$I+1]; done >cisla

Pouzijte programy test a echo, prictení jednicky muzete implementovat jako
vnitrní príkaz.

8.
Napiste program, který simuluje cinnost shellu pri interpretaci príkazového
rádku

grep slovo * 2>errfile; echo $?

9.
Napiste program, který simuluje zjednodusenou podobu príkazu ls. Program
dostane jako parametr jméno adresáre a vypíse jména a velikosti vsech souboru
v nem. Výstup bude setríden pomocí programu sort. Pro predání dat programu
sort pouzijte rouru.

10.
Napiste program, který simuluje cinnost shellu pri interpretaci skriptu

GS_OPTIONS=-dSAFER
export GS_OPTIONS
ghost "$1" | lpr

11.
Napiste program, který simuluje zjednodusenou podobu príkazu ls. Program
dostane jako parametr jméno adresáre a vypíse jména vsech souboru v nem. Pro
symbolické linky navíc vypíse i cíl linku. Výstup bude setríden pomocí
programu sort. Pro predání dat programu sort pouzijte rouru.

12.
Napiste program pwd, který vypíse cestu od korene k aktuálnímu adresári.
Nepouzívejte existující príkaz pwd, funkci getcwd(), nebo jejich ekvivalenty.
Nápoveda: jméno odkazu na adresár v jeho rodicovském adresári zjistíte
porovnáním císel zarízení a i-uzlu aktuálního adresáre a vsech polozek
rodicovského adresáre. Polozka ".." korenového adresáre odkazuje na sebe.

13.
Napiste program access, který pro jména souboru zadaná jako parametry vypíse
(na standardní výstup), vase práva k nim (císt, psát, nebo spustit). Pro
soubory, které neexistují nebo se nedají zjistit práva, vypíse na chybový
výstup hlásení obsahující jméno souboru a prícinu chyby. Nepouzívejte funkci
access(), príkaz test -f/-r/-w/-x, nebo jejich ekvivalenty.

B) Synchronizace, IPC, síte
---------------------------

VZOROVÝ PRÍKLAD
Implementujte operace P a V pro UNIXové semafory pomocí podmínkových
promenných. Skupina operací nad skupinou semaforu, vybraných z pole semaforu,
je atomická, tj. provedou se bud vsechny operace nebo ani jedna (pokud nelze
provést vsechny). Pokud nekterou operaci nelze provést, vlákno se zablokuje a
ceká, dokud nemuze provést vsechny operace.

1.
Pomocí System V IPC semaforu a sdílené pameti implementujte fronty zpráv.
Predpokládejte, ze vsechny zprávy ve fronte mají stejnou délku. Zprávy se z
fronty vybírají postupne, v poradí, ve kterém byly poslány do fronty.
Do fronty muze posílat i z ní prijímat zprávy libovolný pocet procesu.
Implementujte operace
init(nmesg,sz) - inicializace fronty, nmesg je pocet zpráv, které mohou být
soucasne ve fronte, sz je délka zprávy
send(msg) - posle zprávu do fronty, pokud uz ve fronte je nmesg zpráv, ceká,
az se uvolní místo
recv(msg) - precte první zprávu z fronty, kdyz je fronta prázdná, ceká, az
prijde zpráva

2.
Napiste kostru TCP serveru, který umí obsluhovat více pozadavku soucasne.
Pro kazdého klienta se spoustí nový proces nebo vlákno. Napiste obe varianty.
Predpokládejte, ze je definovaná funkce protokol, která zajistí
komunikaci s klientem, po návratu z ní je treba ukoncit spojení s klientem.

3.
Dva procesy (zapisovatel a ctenár) pouzívají ke komunikaci sdílenou pamet.
Zapisovatel vygeneruje data a ulozí je do pameti, ctenár si je vyzvedne a
zpracuje. Do sdílené pameti se vejde jen jeden blok dat, takze zapisovatel
musí pred zapsáním dalsích dat cekat, nez ctenár zpracuje predchozí data.
Ctenár musí naopak cekat na zapisovatele, az vytvorí nová data. Implementujte
synchronizaci mezi zapisovatelem a ctenárem pomocí signálu.

4.
Napiste UDP server, který pouzívá pouze 1 proces (1 vlákno) a
poskytuje 2 sluzby na 2 portech. Podle toho, na který port prijde pozadavek
klienta, se pro jeho zpracování volá funkce zpracuj1 nebo zpracuj2.
Funkce zpracuj1 provádí echo, tj. vrátí data klientovi. Funkce zpracuj2 cte
a pocítá datagramy tak dlouho, dokud pochází od stejného klienta. Kdyz prijde
datagram od jiného klienta, posle puvodnímu klientovi zjistený pocet datagramu
a zacne pocítat datagramy od nuly pro nového klienta.

5.
Implementujte semafory s vyuzitím separátního rídícího procesu, který zajistuje
semaforové operace (stací implementovat init(N) - inicializace na hodnotu N,
p(N) - podmínené snízení hodnoty o N a v(N) - zvýsení hodnoty o N a uvolnení
cekajících procesu). Procesy, které chtejí pouzívat semafory, komunikují s
rídícím procesem pomocí front zpráv.

6.
Problém obedvajících filozofu: kolem kulatého stolu sedí N filozofu a vzdy
mezi dvema filozofy je jedna vidlicka (celkem tedy N vidlicek). Aby se filozof
mohl najíst, potrebuje obe vidlicky, které má u sebe. Nejprve vezme obe
vidlicky, pak se nají a nakonec vidlicky vrátí na stul. Cílem úlohy je
zajistit, aby se kazdý filozof, kdyz dostane hlad, mohl za konecný cas pustit
do jídla. Je tedy treba zabránit deadlocku, napr.: vsichni filozofové chtejí
jíst soucasne, kazdý z nich vezme vidlicku vlevo, ale pak uz zádný nemá
vidlicku vpravo a vsichni cekají.

Vyreste problém obedvajících filozofu za pomoci UNIXových semaforu. Kazdý 
filozof je predstavován samostatným procesem. Neblokujte zádný proces
zbytecne.

7.
Problém obedvajících filozofu: kolem kulatého stolu sedí N filozofu a vzdy
mezi dvema filozofy je jedna vidlicka (celkem tedy N vidlicek). Aby se filozof
mohl najíst, potrebuje obe vidlicky, které má u sebe. Nejprve vezme obe
vidlicky, pak se nají a nakonec vidlicky vrátí na stul. Cílem úlohy je
zajistit, aby se kazdý filozof, kdyz dostane hlad, mohl za konecný cas pustit
do jídla. Je tedy treba zabránit deadlocku, napr.: vsichni filozofové chtejí
jíst soucasne, kazdý z nich vezme vidlicku vlevo, ale pak uz zádný nemá
vidlicku vpravo a vsichni cekají.

Vyreste problém obedvajících filozofu s pouzitím podmínkových promenných.
Kazdý filozof je simulován samostatným vláknem. Neblokujte zádné vlákno
zbytecne.

8.
Nekolik procesu pouzívá sdílenou pamet tak, ze si v ní alokují bloky stejné
délky. Kazdý blok smí být alokován pouze jedním procesem. Napiste funkci
shalloc(), která alokuje volný blok pameti. Pokud jsou vsechny bloky obsazené,
volající proces pocká, az se nejaký blok uvolní. Napiste také dealokacní 
funkci shfree(). Pouzijte sdílenou pamet a semafory.

9.
Nekolik vláken pouzívá cást spolecné pameti (ukazatel na ni je v globální
promenné mem) tak, ze si v ní alokují bloky stejné
délky. Kazdý blok smí být alokován pouze jedním vláknem. Napiste funkci
shalloc(), která alokuje volný blok pameti. Pokud jsou vsechny bloky obsazené,
volající vlákno pocká, az se nejaký blok uvolní. Napiste také dealokacní 
funkci shfree(). Pouzijte podmínkové promenné.

10.
Napiste kostru TCP serveru, který bude provádet paralelní obsluhu príchozích
spojení v rámci jednoho procesu (a bez pouzití vláken). Vyuzijte toho, ze
select() a poll() skoncí, pokud je mezi deskriptory testovanými pro ctení
deskriptor soketu, na kterém ceká zádost o spojení (a je tedy mozné na nej
volat accept(), které ihned uspeje). Server ceká na data od klientu, pokud
zjistí, ze nekterý klient poslal data, volá funkci rhandle(fd), kde fd je
deskriptor soketu pouzívaného pro komunikaci s tímto klientem. Jestlize
rhandle(fd) vrátí nenulu, znamená to pozadavek na zápis, který se obslouzí
tak, ze az server zjistí moznost zapsat data na fd, zavolá whandle(fd). Pokud
whandle(fd) vrátí nulu, není treba ho uz dále volat, kdyz vrátí nenulu, nebyla
zapsána vsechna data a musí se znovu volat whandle(fd) az bude fd pripraveno
pro zápis.

11.
Napiste jednoduchou TCP proxy, tj. program, který zprostredkovává TCP spojení.
Program má tri parametry lport, rhost a rport. Porty mohou být zadány bud
císlem, nebo jménem sluzby. Na portu lport ceká na príchozí spojení. Po
navázání spojení s klientem naváze spojení se serverem na adrese rhost a portu
rport. Následne predává vsechna data od klienta serveru a data od serveru
klientovi, vzdy okamzite, jakmile je dostane. Pokud server nebo klient ukoncí
spojení, proxy zavre i druhé spojení. Jednotliví klienti jsou obsluhováni
sekvencne, tj. dalsí klient je akceptován az po odpojení predchozího klienta.

12.
Napiste zjednodusenou variantu programu inetd, která bude pracovat pouze v
rezimu TCP/nowait. Predpokládejte, ze v poli conf máte zpracovaný konfiguracní
soubor (tj. nemusíte psát parser konfigurace). Konfigurace obsahuje záznam pro
kazdý obsluhovaný server. V záznamu je císlo portu, jméno a argumenty
programu, který se má spustit jako server. Program inetd ceká na príchod TCP
spojení na vsech portech zadaných v konfiguraci a po navázání spojení spustí
príslusný server, predá mu na deskriptorech 0, 1 a 2 odkaz na navázané spojení
a okamzite zacne cekat na dalsí spojení. Nezapomente na úklid zombií po
ukoncených procesech serveru. Nápoveda: Volání select() a poll() skoncí,
pokud je mezi deskriptory testovanými pro ctení deskriptor soketu, na kterém
ceká zádost o spojení (a je tedy mozné na nej volat accept(), které ihned
uspeje).

13.
Napiste zjednodusenou variantu programu inetd, která bude pracovat pouze v
rezimu UDP/wait. Predpokládejte, ze v poli conf máte zpracovaný konfiguracní
soubor (tj. nemusíte psát parser konfigurace). Konfigurace obsahuje záznam pro
kazdý obsluhovaný server. V záznamu je císlo portu, jméno a argumenty
programu, který se má spustit jako server. Program inetd ceká na príchod
datagramu. kdyz detekuje datagram na nekterém portu, spustí príslusný server.
Pozor: inetd nesmí datagram precíst. Dokud server neskoncí, inetd nemonitoruje
jeho port, ale dál obsluhuje ostatní porty, pro které práve nebezí zádný
server. Po skoncení serveru inetd obnoví monitoring jeho portu. Nápoveda:
pci ukoncení synovského procesu dostane rodic signál SIGCHLD (který je
standardne ignorován).
