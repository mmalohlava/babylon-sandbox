%
% Parametry pokusu
%

% Pocet hodu:
numberOfThrows = 100;
% Pocet kostek:
numberOfDice  = 4;

% Vygeneruji si soubor nahodnych hodu
diceThrows = randi(6, numberOfDice, numberOfThrows);

% Zobrazim soubor hodu kostkami
diceThrows

% Spocitam histogram hodnot [1,2,3,4,5,6] v kazdem hodu
% a pak si podminkou omezim vsechny sloupce, ve kterych 
% se nachazi cislo 3 a vice (tj. to znaci, ze v danem hodu padlo jedno cislo bud
% 3krat nebo 4krat). 
% Ve vysledku dostanu vektor nul a jednicek. Jednicka znaci
% uspesny hod, nula znaci opak.
successfulDiceThrows = any(histc(diceThrows, (1:6)) >= 3)

% Spoctu kumulativni soucet ve vektoru, tj [1,0,1] => [1,1,2]. 
% Tj. dostanu pocet prozatimnich uspechu v danem hodu.
successfulDiceThrowsSum = cumsum(successfulDiceThrows)

% Jeste si poznacim pocet vsech uspesnych pripadu:
totalNumberOfSuccess = max(successfulDiceThrowsSum);
totalProbability = totalNumberOfSuccess / numberOfThrows;

% Spoctu relativni pravdepodobnosti v kazdem kroku:
resultingProbability = successfulDiceThrowsSum ./ (1:numberOfThrows)

% Zobrazim graf pravdepodobnosti.
plot(resultingProbability, '--rs', 'MarkerFaceColor', 'g', 'MarkerSize', 4);
title('Relativni pravdepodobnost pri hodu 4 kostkami');
xlabel('pocet hodu');
ylabel('relativni pravdepodobnost');
line([0 numberOfThrows], [totalProbability totalProbability]);



