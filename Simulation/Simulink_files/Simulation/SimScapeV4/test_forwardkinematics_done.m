
syms theta1 theta2 theta3
%TDH(alpha,a,d,theta)


DH = [       0,         0,               0.0528,                theta1;
             -pi/2,    0,                   0,                   theta2;
             0,    0.21988,                   0,                theta3];
%%Transformation matrix from frame 6 to Wrist    
T3_W=[  1,  0,  0,  0.22368;
        0,  1, 0,  0;
        0,  0,  1, 0;
        0,  0,  0,  1];
    
outputMatrice = DH_toMatrice(DH,1,3)*T3_W; %Returns transformation matrix from specified Joint to wrist

x = simplify(expand(outputMatrice(1,4)))
y = simplify(expand(outputMatrice(2,4)))
z = simplify(expand(outputMatrice(3,4)))
