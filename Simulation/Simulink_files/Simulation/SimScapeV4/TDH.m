%Function for calculating the DH matrice
function [T] = TDH(alpha,a,d,theta)

    T=  [(cos(theta))              (-sin(theta))                 0                  a;
         (sin(theta))*(cos(alpha))   (cos(theta))*(cos(alpha))  (-sin(alpha)) (-sin(alpha))*d;
         (sin(theta))*(sin(alpha))   (cos(theta))*(sin(alpha))   (cos(alpha))  (cos(alpha))*d;
         0 0 0 1];
end
    
%Function for rounding values to avoid pi being infinity
function [rounded] = r(number)
    if isnumeric(number)
        rounded = round(number,10);
    else
        rounded = number;
    end
end