Pr�klady ke zkousce z UNIXu
===========================

P�semka obsahuje dva pr�klady, po jednom z c�st� (A) a (B).

Obecn� pokyny
-------------

Nezapomente se na sv� resen� podepsat a napsat c�sla pr�kladu.

Alespon u 1 vol�n� naznacte, jak byste standardn�m zpusobem osetrili pr�padnou
chybu. Ve zbytku programu muzete predpokl�dat, ze vsechny funkce skonc�
spr�vne, a nezab�vat se osetrov�n�m chyb.

Nezapomente, ze presmerov�n�, roury a zpracov�n� expanzn�ch znaku prov�d�
shell (tj. m� to delat v�s program, kter�m simulujete shell). Pouz�vejte
spr�vnou variantu sluzby exec (pouzit� PATH, zpusob zad�n� argumentu). Piste
program tak, aby nez�lezelo na tom jestli (a jak�) dostane pri sv�m spusten�
deskriptory otevren�ch souboru (napr. nemus� dostat otevren� deskriptory 0,
1, 2). Vsechna jm�na souboru vznikl� z expanzn�ch znaku se pred�vaj� na
pr�kazov� r�dce najednou jednomu programu jako samostatn� argumenty (program
se nespoust� opakovane pro jednotliv� soubory). Pri implementaci presmerov�n�
('pr�kaz soubor', 'pr�kaz <soubor') nepouz�vejte roury. Snazte se omezit pocet
pouz�van�ch procesu a rour na nezbytn� minimum.

Pokud potrebujete synchronizovat procesy, vyhnete se aktivn�mu cek�n�, m�sto
toho pouz�vejte funkce, kter� zablokuj� proces, dokud nenastane ocek�van�
ud�lost. Snazte se blokovat procesy pouze tehdy, kdy je to skutecne nutn�.

Pouz�vejte syst�mov� vol�n� (napr. open, read, write, pipe), ne knihovn�
funkce (napr. fopen,fread, fwrite, fprintf, popen).

Pokud nev�te, co prov�d� pr�kaz shellu, kter� m�te simulovat, tak se radeji
zeptejte (neznalost shellu nem� vliv na zn�mku) a nevym�slejte si, co by to
mohlo delat.

Obecn� pokyny
-------------

Nezapomente se na sv� resen� podepsat a napsat c�sla pr�kladu.

Alespon u 1 vol�n� naznacte, jak byste standardn�m zpusobem osetrili pr�padnou
chybu. Ve zbytku programu muzete predpokl�dat, ze vsechny funkce skonc�
spr�vne, a nezab�vat se osetrov�n�m chyb.

Nezapomente, ze presmerov�n�, roury a zpracov�n� expanzn�ch znaku prov�d�
shell (tj. m� to delat v�s program, kter�m simulujete shell). Pouz�vejte
spr�vnou variantu sluzby exec (pouzit� PATH, zpusob zad�n� argumentu). Piste
program tak, aby nez�lezelo na tom jestli (a jak�) dostane pri sv�m spusten�
deskriptory otevren�ch souboru (napr. nemus� dostat otevren� deskriptory 0,
1, 2). Vsechna jm�na souboru vznikl� z expanzn�ch znaku se pred�vaj� na
pr�kazov� r�dce najednou jednomu programu jako samostatn� argumenty (program
se nespoust� opakovane pro jednotliv� soubory). Pri implementaci presmerov�n�
('pr�kaz soubor', 'pr�kaz <soubor') nepouz�vejte roury. Snazte se omezit pocet
pouz�van�ch procesu a rour na nezbytn� minimum.

Pokud potrebujete synchronizovat procesy, vyhnete se aktivn�mu cek�n�, m�sto
toho pouz�vejte funkce, kter� zablokuj� proces, dokud nenastane ocek�van�
ud�lost. Snazte se blokovat procesy pouze tehdy, kdy je to skutecne nutn�.

Pouz�vejte syst�mov� vol�n� (napr. open, read, write, pipe), ne knihovn�
funkce (napr. fopen,fread, fwrite, fprintf, popen).

Pokud nev�te, co prov�d� pr�kaz shellu, kter� m�te simulovat, tak se radeji
zeptejte (neznalost shellu nem� vliv na zn�mku) a nevym�slejte si, co by to
mohlo delat.

A) Procesy, roury
-----------------

- spousten� procesu
- presmerov�n� < > >>
- presmerov�n� <& >& >>&
- roury
- pouzit� argv
- pouzit� env. var.
- zmena env. var.
- cek�n� na exit code
- cten� obsahu adres�re

VZOROV� PR�KLAD
Napiste program v jazyce C, kter� simuluje cinnost shellu pri prov�den�
pr�kazu

find $HOME -name '*.c' 2>/dev/null | less

1.
Napiste program, kter� simuluje cinnost shellu pri interpretaci skriptu

/bin/kill -TERM `ps "$1"`
echo $?

Pro cten� v�stupu vnoren�ho pr�kazu pouzijte rouru. Predpokl�dejte, ze vnoren�
pr�kaz vyp�se pouze jeden r�dek, kter� muze obsahovat v�ce slov (oddelen�ch
mezerami). Kazd� slovo se pred�v� pr�kazu kill jako samostatn� parametr.

2.
Napiste program, kter� simuluje cinnost shellu pri prov�den� pr�kazu

ls -lR / 2>&1 | "$PAGER"

3.
Napiste program, kter� simuluje cinnost shellu pri interpretaci skriptu

find "$1" "$2" 2>errfile | xargs rm "$RMARG"

4.
Napiste program, kter� simuluje cinnost shellu pri interpretaci skriptu

for F in "$@"; do /usr/bin/grep '^#' "$F"; done 2>/dev/null | less

5.
Napiste program, kter� simuluje cinnost shellu pri interpretaci r�dku

find / -type d -print 2>&1 | xargs cat >>outfile

6.
Napiste program, kter� simuluje cinnost shellu pri interpretaci skriptu

if grep "$REGEXP" "$1" >nalezeno 2>errfile; then echo NALEZENO;
else echo NENALEZENO; fi

Pouzijte extern� pr�kaz (program) echo.

7.
Napiste program, kter� simuluje cinnost shellu pri interpretaci skriptu

I=1
while [ "$I" -le "$1" ]; do echo "$I"; I=$[$I+1]; done >cisla

Pouzijte programy test a echo, pricten� jednicky muzete implementovat jako
vnitrn� pr�kaz.

8.
Napiste program, kter� simuluje cinnost shellu pri interpretaci pr�kazov�ho
r�dku

grep slovo * 2>errfile; echo $?

9.
Napiste program, kter� simuluje zjednodusenou podobu pr�kazu ls. Program
dostane jako parametr jm�no adres�re a vyp�se jm�na a velikosti vsech souboru
v nem. V�stup bude setr�den pomoc� programu sort. Pro pred�n� dat programu
sort pouzijte rouru.

10.
Napiste program, kter� simuluje cinnost shellu pri interpretaci skriptu

GS_OPTIONS=-dSAFER
export GS_OPTIONS
ghost "$1" | lpr

11.
Napiste program, kter� simuluje zjednodusenou podobu pr�kazu ls. Program
dostane jako parametr jm�no adres�re a vyp�se jm�na vsech souboru v nem. Pro
symbolick� linky nav�c vyp�se i c�l linku. V�stup bude setr�den pomoc�
programu sort. Pro pred�n� dat programu sort pouzijte rouru.

12.
Napiste program pwd, kter� vyp�se cestu od korene k aktu�ln�mu adres�ri.
Nepouz�vejte existuj�c� pr�kaz pwd, funkci getcwd(), nebo jejich ekvivalenty.
N�poveda: jm�no odkazu na adres�r v jeho rodicovsk�m adres�ri zjist�te
porovn�n�m c�sel zar�zen� a i-uzlu aktu�ln�ho adres�re a vsech polozek
rodicovsk�ho adres�re. Polozka ".." korenov�ho adres�re odkazuje na sebe.

13.
Napiste program access, kter� pro jm�na souboru zadan� jako parametry vyp�se
(na standardn� v�stup), vase pr�va k nim (c�st, ps�t, nebo spustit). Pro
soubory, kter� neexistuj� nebo se nedaj� zjistit pr�va, vyp�se na chybov�
v�stup hl�sen� obsahuj�c� jm�no souboru a pr�cinu chyby. Nepouz�vejte funkci
access(), pr�kaz test -f/-r/-w/-x, nebo jejich ekvivalenty.

B) Synchronizace, IPC, s�te
---------------------------

VZOROV� PR�KLAD
Implementujte operace P a V pro UNIXov� semafory pomoc� podm�nkov�ch
promenn�ch. Skupina operac� nad skupinou semaforu, vybran�ch z pole semaforu,
je atomick�, tj. provedou se bud vsechny operace nebo ani jedna (pokud nelze
prov�st vsechny). Pokud nekterou operaci nelze prov�st, vl�kno se zablokuje a
cek�, dokud nemuze prov�st vsechny operace.

1.
Pomoc� System V IPC semaforu a sd�len� pameti implementujte fronty zpr�v.
Predpokl�dejte, ze vsechny zpr�vy ve fronte maj� stejnou d�lku. Zpr�vy se z
fronty vyb�raj� postupne, v porad�, ve kter�m byly posl�ny do fronty.
Do fronty muze pos�lat i z n� prij�mat zpr�vy libovoln� pocet procesu.
Implementujte operace
init(nmesg,sz) - inicializace fronty, nmesg je pocet zpr�v, kter� mohou b�t
soucasne ve fronte, sz je d�lka zpr�vy
send(msg) - posle zpr�vu do fronty, pokud uz ve fronte je nmesg zpr�v, cek�,
az se uvoln� m�sto
recv(msg) - precte prvn� zpr�vu z fronty, kdyz je fronta pr�zdn�, cek�, az
prijde zpr�va

2.
Napiste kostru TCP serveru, kter� um� obsluhovat v�ce pozadavku soucasne.
Pro kazd�ho klienta se spoust� nov� proces nebo vl�kno. Napiste obe varianty.
Predpokl�dejte, ze je definovan� funkce protokol, kter� zajist�
komunikaci s klientem, po n�vratu z n� je treba ukoncit spojen� s klientem.

3.
Dva procesy (zapisovatel a cten�r) pouz�vaj� ke komunikaci sd�lenou pamet.
Zapisovatel vygeneruje data a uloz� je do pameti, cten�r si je vyzvedne a
zpracuje. Do sd�len� pameti se vejde jen jeden blok dat, takze zapisovatel
mus� pred zaps�n�m dals�ch dat cekat, nez cten�r zpracuje predchoz� data.
Cten�r mus� naopak cekat na zapisovatele, az vytvor� nov� data. Implementujte
synchronizaci mezi zapisovatelem a cten�rem pomoc� sign�lu.

4.
Napiste UDP server, kter� pouz�v� pouze 1 proces (1 vl�kno) a
poskytuje 2 sluzby na 2 portech. Podle toho, na kter� port prijde pozadavek
klienta, se pro jeho zpracov�n� vol� funkce zpracuj1 nebo zpracuj2.
Funkce zpracuj1 prov�d� echo, tj. vr�t� data klientovi. Funkce zpracuj2 cte
a poc�t� datagramy tak dlouho, dokud poch�z� od stejn�ho klienta. Kdyz prijde
datagram od jin�ho klienta, posle puvodn�mu klientovi zjisten� pocet datagramu
a zacne poc�tat datagramy od nuly pro nov�ho klienta.

5.
Implementujte semafory s vyuzit�m separ�tn�ho r�d�c�ho procesu, kter� zajistuje
semaforov� operace (stac� implementovat init(N) - inicializace na hodnotu N,
p(N) - podm�nen� sn�zen� hodnoty o N a v(N) - zv�sen� hodnoty o N a uvolnen�
cekaj�c�ch procesu). Procesy, kter� chtej� pouz�vat semafory, komunikuj� s
r�d�c�m procesem pomoc� front zpr�v.

6.
Probl�m obedvaj�c�ch filozofu: kolem kulat�ho stolu sed� N filozofu a vzdy
mezi dvema filozofy je jedna vidlicka (celkem tedy N vidlicek). Aby se filozof
mohl naj�st, potrebuje obe vidlicky, kter� m� u sebe. Nejprve vezme obe
vidlicky, pak se naj� a nakonec vidlicky vr�t� na stul. C�lem �lohy je
zajistit, aby se kazd� filozof, kdyz dostane hlad, mohl za konecn� cas pustit
do j�dla. Je tedy treba zabr�nit deadlocku, napr.: vsichni filozofov� chtej�
j�st soucasne, kazd� z nich vezme vidlicku vlevo, ale pak uz z�dn� nem�
vidlicku vpravo a vsichni cekaj�.

Vyreste probl�m obedvaj�c�ch filozofu za pomoci UNIXov�ch semaforu. Kazd� 
filozof je predstavov�n samostatn�m procesem. Neblokujte z�dn� proces
zbytecne.

7.
Probl�m obedvaj�c�ch filozofu: kolem kulat�ho stolu sed� N filozofu a vzdy
mezi dvema filozofy je jedna vidlicka (celkem tedy N vidlicek). Aby se filozof
mohl naj�st, potrebuje obe vidlicky, kter� m� u sebe. Nejprve vezme obe
vidlicky, pak se naj� a nakonec vidlicky vr�t� na stul. C�lem �lohy je
zajistit, aby se kazd� filozof, kdyz dostane hlad, mohl za konecn� cas pustit
do j�dla. Je tedy treba zabr�nit deadlocku, napr.: vsichni filozofov� chtej�
j�st soucasne, kazd� z nich vezme vidlicku vlevo, ale pak uz z�dn� nem�
vidlicku vpravo a vsichni cekaj�.

Vyreste probl�m obedvaj�c�ch filozofu s pouzit�m podm�nkov�ch promenn�ch.
Kazd� filozof je simulov�n samostatn�m vl�knem. Neblokujte z�dn� vl�kno
zbytecne.

8.
Nekolik procesu pouz�v� sd�lenou pamet tak, ze si v n� alokuj� bloky stejn�
d�lky. Kazd� blok sm� b�t alokov�n pouze jedn�m procesem. Napiste funkci
shalloc(), kter� alokuje voln� blok pameti. Pokud jsou vsechny bloky obsazen�,
volaj�c� proces pock�, az se nejak� blok uvoln�. Napiste tak� dealokacn� 
funkci shfree(). Pouzijte sd�lenou pamet a semafory.

9.
Nekolik vl�ken pouz�v� c�st spolecn� pameti (ukazatel na ni je v glob�ln�
promenn� mem) tak, ze si v n� alokuj� bloky stejn�
d�lky. Kazd� blok sm� b�t alokov�n pouze jedn�m vl�knem. Napiste funkci
shalloc(), kter� alokuje voln� blok pameti. Pokud jsou vsechny bloky obsazen�,
volaj�c� vl�kno pock�, az se nejak� blok uvoln�. Napiste tak� dealokacn� 
funkci shfree(). Pouzijte podm�nkov� promenn�.

10.
Napiste kostru TCP serveru, kter� bude prov�det paraleln� obsluhu pr�choz�ch
spojen� v r�mci jednoho procesu (a bez pouzit� vl�ken). Vyuzijte toho, ze
select() a poll() skonc�, pokud je mezi deskriptory testovan�mi pro cten�
deskriptor soketu, na kter�m cek� z�dost o spojen� (a je tedy mozn� na nej
volat accept(), kter� ihned uspeje). Server cek� na data od klientu, pokud
zjist�, ze nekter� klient poslal data, vol� funkci rhandle(fd), kde fd je
deskriptor soketu pouz�van�ho pro komunikaci s t�mto klientem. Jestlize
rhandle(fd) vr�t� nenulu, znamen� to pozadavek na z�pis, kter� se obslouz�
tak, ze az server zjist� moznost zapsat data na fd, zavol� whandle(fd). Pokud
whandle(fd) vr�t� nulu, nen� treba ho uz d�le volat, kdyz vr�t� nenulu, nebyla
zaps�na vsechna data a mus� se znovu volat whandle(fd) az bude fd pripraveno
pro z�pis.

11.
Napiste jednoduchou TCP proxy, tj. program, kter� zprostredkov�v� TCP spojen�.
Program m� tri parametry lport, rhost a rport. Porty mohou b�t zad�ny bud
c�slem, nebo jm�nem sluzby. Na portu lport cek� na pr�choz� spojen�. Po
nav�z�n� spojen� s klientem nav�ze spojen� se serverem na adrese rhost a portu
rport. N�sledne pred�v� vsechna data od klienta serveru a data od serveru
klientovi, vzdy okamzite, jakmile je dostane. Pokud server nebo klient ukonc�
spojen�, proxy zavre i druh� spojen�. Jednotliv� klienti jsou obsluhov�ni
sekvencne, tj. dals� klient je akceptov�n az po odpojen� predchoz�ho klienta.

12.
Napiste zjednodusenou variantu programu inetd, kter� bude pracovat pouze v
rezimu TCP/nowait. Predpokl�dejte, ze v poli conf m�te zpracovan� konfiguracn�
soubor (tj. nemus�te ps�t parser konfigurace). Konfigurace obsahuje z�znam pro
kazd� obsluhovan� server. V z�znamu je c�slo portu, jm�no a argumenty
programu, kter� se m� spustit jako server. Program inetd cek� na pr�chod TCP
spojen� na vsech portech zadan�ch v konfiguraci a po nav�z�n� spojen� spust�
pr�slusn� server, pred� mu na deskriptorech 0, 1 a 2 odkaz na nav�zan� spojen�
a okamzite zacne cekat na dals� spojen�. Nezapomente na �klid zombi� po
ukoncen�ch procesech serveru. N�poveda: Vol�n� select() a poll() skonc�,
pokud je mezi deskriptory testovan�mi pro cten� deskriptor soketu, na kter�m
cek� z�dost o spojen� (a je tedy mozn� na nej volat accept(), kter� ihned
uspeje).

13.
Napiste zjednodusenou variantu programu inetd, kter� bude pracovat pouze v
rezimu UDP/wait. Predpokl�dejte, ze v poli conf m�te zpracovan� konfiguracn�
soubor (tj. nemus�te ps�t parser konfigurace). Konfigurace obsahuje z�znam pro
kazd� obsluhovan� server. V z�znamu je c�slo portu, jm�no a argumenty
programu, kter� se m� spustit jako server. Program inetd cek� na pr�chod
datagramu. kdyz detekuje datagram na nekter�m portu, spust� pr�slusn� server.
Pozor: inetd nesm� datagram prec�st. Dokud server neskonc�, inetd nemonitoruje
jeho port, ale d�l obsluhuje ostatn� porty, pro kter� pr�ve nebez� z�dn�
server. Po skoncen� serveru inetd obnov� monitoring jeho portu. N�poveda:
pci ukoncen� synovsk�ho procesu dostane rodic sign�l SIGCHLD (kter� je
standardne ignorov�n).
