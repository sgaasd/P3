%%Defintion of DH parameters

theta1 = deg2rad(0);
theta2 = deg2rad(90);
theta3 = deg2rad(0);


%TDH(alpha,a,d,theta)


DH = [       0,         0,               52.8,                theta1;
             pi/2,    0,                   0,                   theta2;
             0,    219.88,                   0,                theta3];
%%Transformation matrix from frame 6 to Wrist    
T3_W=[  1,  0,  0,  223.68;
        0,  1, 0,  0;
        0,  0,  1, 0;
        0,  0,  0,  1];
    
outputMatrice = DH_toMatrice(DH,1,3)*T3_W; %Returns transformation matrix from specified Joint to wrist

x = outputMatrice(1,4)
y = outputMatrice(2,4)
z = outputMatrice(3,4)