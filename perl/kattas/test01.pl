#!/usr/bin/perl
use feature 'say';

# vytvorim referenci na hash (reference = ukazovatko)
my $hash = { "en" => "london", "cr" => "prague" };

# pridam polozku
$hash->{ "es" } = "spain";

# vypisu polozky
say $hash->{"en"};
say $hash->{"es"};

my @allLines = ();
while (my $line = <>) {
   push(@allLines, $line); 
}

say "Number of lines: ".scalar(@allLines);

my $count = 1;
foreach my $l(@allLines) {
    say "$count: $l";
    $count++;
}



