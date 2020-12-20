
function [outputMatrice] = forwardKinematics(from,to)
syms theta1 theta2 theta3 theta4 theta5 theta6 L1 L2 D1 X Y theta

%%Defintion of DH parameters
DH = [    pi/2,         0,               172.1,                theta1;
             0,    219.79,                   0,     	theta2+(pi/2);
             0,    268.98,                   0,                theta3];
%%Transformation matrix from frame 6 to Wrist    
T3_W=[  1,  0,  0,  267.98;
        0,  1, 0,  0;
        0,  0,  1, 0;
        0,  0,  0,  1];
if to == 'W'
    outputMatrice = DH_toMatrice(DH,from,3)*T3_W; %Returns transformation matrix from specified Joint to wrist
else
    outputMatrice = DH_toMatrice(DH,from,to); %Returns transformation matrix from specified joint to specified joint
end
end


