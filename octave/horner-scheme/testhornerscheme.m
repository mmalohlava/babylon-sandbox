%
% Tests for horner scheme implementation
%

%
% Divide the polynom 2x^3-6x^2+2x-1 by (x-3)
%
a = [2 -6 2 -1];
x = 3;
hornerscheme(a, x)

%
% Divide the polynom x^3-6x^2+11x-6 by (x-2)
%
a = [1 -6 11 -6];
x = 2;
hornerscheme(a, x)

%
% Divide the polynom 4x^4-6x^3+3x-5 by (x-0.5)
%
a = [4 -6 0 3 -5];
x = 0.5;
hornerscheme(a, x)
