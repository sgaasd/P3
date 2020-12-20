function [outputMatrice] = DH_toMatrice(inputMatrice,from,to)
%DH_toMatrice: Function for calculating transformation matrice from DH
%parameters
%   Detailed explanation goes here
outputMatrice = eye(4,4);
    for i=from:to
    T=TDH(inputMatrice(i,1),inputMatrice(i,2),inputMatrice(i,3),inputMatrice(i,4));
    outputMatrice = outputMatrice*T;
    end
end
