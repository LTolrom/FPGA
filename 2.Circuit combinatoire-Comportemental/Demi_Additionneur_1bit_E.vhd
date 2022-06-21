library IEEE;
use IEEE.std_logic_1164.all;

entity DemiA_1b2 is
    port(
        a   : in std_logic_vector (1 downto 0);
        r   : out std_logic;
        s   : out std_logic);
end DemiA_1b2;

architecture behavior of DemiA_1b2 is

    begin
        process(a)
            begin
                case (a) is
                    when "00"=> s<='0';
                                r<='0';
                    when "01"=> s<='1';
                                r<='0';
                    when "10"=> s<='1';
                                r<='0';
                    when "11"=> s<='0';
                                r<='1';
                end case;
        end process;

end behavior;