#!/usr/bin/perl
use feature 'say';

my @soubor1 = ('cislo1 abcdefefe', 'cislo2 bgafsdafa', 'cislo3 fdfdfdfd', 'cislo4 ohooooo', 'cislo5 tralalalal');
my @soubor2 = ('cislo1', 'cislo3', 'cislo5');

my @filteredSoubor = ();
for my $item(@soubor2) {
    say "Looking for item $item";
    my @partialResult = grep(m/$item/, @soubor1);

    say "Vysledek operace grep: @partialResult \n";
    
    # kukni sem: http://perlmeme.org/tutorials/arrays.html
    @filteredSoubor = (@filteredSoubor, @partialResult); 
}

say 'RESULT:';
say join("\n", @filteredSoubor);
