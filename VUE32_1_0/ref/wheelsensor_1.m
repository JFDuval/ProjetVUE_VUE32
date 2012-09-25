%Wheel sensor

close all;
clear all;
clc;

format short eng

maxvalue = 65535;
tx = 0:1:maxvalue;
t = [tx tx tx tx];
plot(t)

timestamp(1) = 0;
timestamp(2) = timestamp(1) + 900;

cnt = 1;
for i = 0:10:length(t)-1000
    
    timestamp(1) = i;
    timestamp(2) = timestamp(1) - 900;

if(timestamp(2) > timestamp(1))
    period = timestamp(2) - timestamp(1);
elseif (timestamp(2) == timestamp(1))
    period = 0;
else
    period = timestamp(2) + (maxvalue - timestamp(1));
end

log_period(cnt) = period;
cnt = cnt + 1;
end
figure()
plot(log_period)