function [data_out] = get_data_lab1(board)
%this function collects data from the serial port and returns it to the
%main-loop.
%The input is the serial port we are trying to reach.
number_of_bytes_to_read = 100;
while(board.BytesAvailable <= number_of_bytes_to_read)
end
v = fread(board, number_of_bytes_to_read);%reading the board
    if(all(v(1:4:end) == 1) && all(v(4:4:end) == 254))
        data_out = 256*double(v(3:4:end))+double(v(2:4:end));%returns a double
    else
        disp('Error format Paquet')
        data_out = 0;
        %read until tag equal to 1
        while(1)
            trash = fread(board,1);
            if (trash==254)
                break
            end
        end
    end
end
       