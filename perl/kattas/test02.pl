#!/usr/bin/perl
use feature 'say';

#
# 1. moznost je nacist soubor po radcich
#
open (IN, "<$ARGV[0]") or die "error reading $ARGV[0] for reading";

my @contentFile = <IN>;

say "Obsah cteny po radcich:";
say @contentFile;

print "Ocislovany obsah:\n";
my $count = 1;
foreach my $line(@contentFile) {
    print "$count: $line";
    $count++;
}
close IN;

#
# 2. moznost (ELEGANTNI) je to nacist rovnou pres @contentFile = <IN>;
#
print "\nObsah po paragrafech od konce:\n";
# v promenne je ulozen seperator radku. normalen je to enter, ktery se znaci \n, ale muzes ho predefinovat a pak cist soubor treba po paragrafech (bloky textu oddelenych volnou radkou)
$/='';
open (IN, "<$ARGV[0]") or die "error reading $ARGV[0] for reading";
# nactu vstup pospatku
@contentFile = reverse <IN>;
$count = 1;
foreach my $line(@contentFile) {
    print "$count. paragraf:\n$line";
    $count++;
}
close IN;
