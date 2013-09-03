function result = hornerscheme( polynom, x0 )
% Divide the given polynom by (x-x0) with help of horner scheme and return polynom
% equation.
%
%   The function takes two parameters: the first parameter 'polynom' is a
%   vector of polynom arguments. The second parameter represents a value for
%   the divider (x-x0).
%   
%   The method returns formatted string containing polynom equation. E.g.,
%   the call:
%       hornerscheme([2 -6 2 -1], 3);
%   returns
%       2x^3-6x^2+2x-1 = (2x^2+2)*(x-3)+5
%

    % compute horner scheme for given values
    [result, rest] = computeHornerScheme(polynom, x0);
    
    % format output
    lhs = polyout(polynom);
    rhs = [ '(' polyout(result) ')*(' polyout([1 -x0]) ')' ];
    if (rest ~= 0)
        if (rest > 0) 
            rhs = [ rhs '+' num2str(rest) ]; 
        else
            rhs = [ rhs num2str(rest) ];
        end
    end
    
    result = [lhs ' = ' rhs ];
end

function [ result, rest ] = computeHornerScheme( polynom, x0 )
% The method compute horner scheme for given polynom and value.
%   The argument 'polynom' is a vector of polynom arguments. The argument
%   x0 represents a value, where the polynom should be evaluated.
%   The 'result' represents a quotient of 'polynom'/(x-x0) and 'rest' represents
%   a remainder.

    % length of the polynom
    polynomLength = length(polynom);

    % compute horner scheme
    b(1) = polynom(1);
    for i = 2:polynomLength                                                                                                                                                                                                                                                                                                                                                                         
        c(i) = x0*b(i-1);                                                                                                                                                                                                                                                                                                                                                                         
        b(i) = polynom(i)+c(i);                                                                                                                                                                                                                                                                                                                                                                       
    end                                                                                                                                                                                                                                                                                                                                                                                         

    % save the results
    rest = b(polynomLength);                                                                                                                                                                                                                                                                                                                                                                           
    result = b(1:polynomLength-1);   
end

function s = polyout(polynom) 
    s = polyout2(polynom, 'x');
end

function s = polyout2(polynom, var)
% Convert given polynom to textual representation
%
%   The argument 'polynom' contains a vector of polynom arguments, var
%   represent polynom variable. The method returns string containing a
%   textual representation of the polynom.
%   E.g., the call 
%       polyout2([1 2 3],'x')
%   returns
%       x^2+2x+3
%
    n = length(polynom);
    exp = n - 1;
    s = '';
    for i = 1:n
        if (polynom(i) ~= 0) 
            if (i ~= 1) 
                if (polynom(i) > 0)
                    s = [s '+'];
                end
            end
            if (polynom(i) ~= 1) 
                s = [s num2str(polynom(i))];
            end
            if (exp ~= 0)
                if (exp == 1)
                    s = [s var];
                else
                    s = [s var '^' num2str(exp)];            
                end
            end            
        end
        exp = exp - 1;
    end
end
