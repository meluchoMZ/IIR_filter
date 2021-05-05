%% Testbench creator for a hardware IIR filter
%% Hardware-Software codesign, Computer engineering
%% Author: Miguel Blanco Godón

clear; close all;
% as first testbench is a piece of music
[x, fs] = audioread('./mozart.wav');

% first version of the filter must use 16 bit signed integers
xint_16 = int16(10000*x);

f = fopen('./source_0.dat', 'w');
fprintf(f, '%d ', xint_16);
fclose(f);

% second version of the filter must use 32 floating point numbers
f = fopen('./source_1.dat', 'w');
fprintf(f, '%f ', x(1:100));
fclose(f);
