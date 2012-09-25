%Wheel sensor
%Spikes removal

close all;
clear all;
clc;

format short eng

data = [500 530 499 300 499 540 500 500];
moy = mean(data)

for i = 1:1:8
    if((data(i) > (1.3*moy)) || (data(i) < (0.7*moy)))
        data(i) = moy;
    end
end

moy2 = mean(data)
