%Choisir le bon port serie
Serial_port = 'COM3';
BaudRate = 9600;

%Initialiser la communication serie (ajuster le BaudRate au besoin)
s = serial(Serial_port, 'BaudRate', BaudRate);

%Vecteur du signal discretise
%On creer 6 points également espace temporellement
digital_signal = zeros(6,1);
amplitude = 127;
DC_offset = 127;
for n = 0:5
    digital_signal(n+1) = amplitude*sin(2*pi*n / 6) + DC_offset;
end

%On veut envoyer ce vecteur a toutes les 4ms
while true
    for i=1:6
        fwrite(s, digital_signal(i,1), 'uint8');
        pause(0.04); %attendre 4ms
        
        %faire un peu de menage (transmit et receive buffer)
        flushinput(s);
        flushoutput(s);
    end
    %recommencer
end


