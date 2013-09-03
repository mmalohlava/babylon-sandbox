% Input a is the polynomial coefficient vector, x the value to be evaluated at.
% The output y is the evaluated polynomial and b the divided coefficient vector.
a = [1,2,3]
x = 4

b(1) = a(1);
for i = 2:length(a)
    c(i) = x*b(i-1)
    b(i) = a(i)+c(i);
end

y = b(length(a));
b = b(1:length(b)-1);

polyout(a)
polyout([1, -x])

polyout(y)
polyout(b)
%

