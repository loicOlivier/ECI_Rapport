serialportlist("available") % Trouver le port connecté au arduino
arduino = serialport("COM7",115200) % Utiliser le port trouvé + Bon Baudrate

data_qt = 500                    % Nombre de données à lire (500ms)

while(1)
flush(arduino)
raw_buffer = read(device, data_qt, "uint8")

%Se construire un nouveau buffer avec les vrais valeurs (sur 10 bits)
for i = 1 : length(data_buffer)
    data_buffer = []
    if (raw_buffer[i] == 0x01)
        
        data1 = raw_buffer(i+1]  % LSB
        data2 = raw_buffer[i+2]  % MSB
        data2 = bitshift(data2, 2)
        data2 = bitand(data2, 0b1100000000)
        data = data1 + data2
        data_buffer = [data_buffer data]
        % Envoyer les paquets de données au plot
        i = i + 4

    else 
        i = i + 1
    end
    
end

end

