%% Nettoye le port et reset les variables Matlab 
instr = instrfind;
if isempty(instr) == 0
    fclose(instr);
    delete(instr);
    clear instr;
end
clear
close all
clc


%% Établie connection série 

com_port = 'COM7'; % CHANGER LE PORT COM!
baud_rate = 115200;
databits = 8;
input_buffer = 8192;

    try
        s = serial(com_port, 'Baudrate', baud_rate, 'DataBits', databits, 'InputBufferSize', input_buffer);
        fopen(s);
        disp('The port is now opened');
    catch M
        disp('Error opening the com port');
        fclose(s);
        delete(s);
        clear all;
        return;
    end 
        
%% Graphique temps réel
figure
title('real time plot');
graphCanal1 = animatedline('MaximumNumPoints', 5000, 'Color', 'r');
xlabel('sample')
ylabel('val')
legend('Signal')


%% Main  Loop
inc = 0.0;
size_of_window = 500;
y1=0;
y2=5;

lower_lim_xaxis = 0;
cycle_counter = 0;
upper_lim_xaxis = size_of_window;


while(1)
    %Appelle la fonction get_data
    data_out = get_data_lab1(s);
    % Converti les valeurs d'une plage de 0-1023 à 0-5V
    volt = data_out*(5/(1023));

    %Affichage des données
    inc = inc(end)+(1:length(volt));
    addpoints(graphCanal1, inc, volt);
    drawnow
    
    if (inc(end)>=upper_lim_xaxis)
        lower_lim_xaxis = upper_lim_xaxis;
        upper_lim_xaxis = upper_lim_xaxis+size_of_window;
        axis([lower_lim_xaxis upper_lim_xaxis y1 y2])
    end    
    
end
        
        


        
        
        