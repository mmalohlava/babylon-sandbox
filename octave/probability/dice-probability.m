function result = generateThrows( numberOfThrows, numberOfDices)

    result = round(rand(numberOfDices, numberOfThrows)*5 + 1);
    % result = randi(6, numberOfThrows, numberOfDices);
end

numberOfThrows = 1000;
numberOfDices  = 4;

diceThrows = generateThrows(numberOfThrows, numberOfDices);

% TODO co je presne priznivy pripad
% Simulovane hody kostkou
diceThrows

% Spocitam histogram hodnot [1,2,3,4,5,6] v kazdem hodu
% a pak si podminkou omezim vsechny sloupce, ve kterych 
% se nachazi cislo 3 a vice (tj. to znaci, ze v danem hodu padlo jedno cislo bud
% 3krat nebo 4krat). Ve vysledku dostanu vektor nul a jednicek. Jednicka znaci
% uspesny hod, nula znaci opak.
successfulDiceThrows = any(histc(diceThrows, [1:6]) >= 3)

% Spoctu kumulativni soucet ve vektoru, tj [1,0,1] => [1,1,2]. 
% Tj. dostanu pocet prozatimnich uspechu v danem hodu.
successfulDiceThrowsSum = cumsum(successfulDiceThrows)
% jeste si poznacim pocet uspechu
totalNumberOfSuccess = max(successfulDiceThrowsSum)

% spoctu relativni pravdepodobnosti v kazdem kroku
resultingProbability = successfulDiceThrowsSum ./ [1:numberOfThrows]
plot(resultingProbability, ";pravdepodobnost;");
xlabel("pocet hodu");
ylabel("relativni pravdepodobnost");
legend(mat2str(totalNumberOfSuccess / numberOfThrows))



