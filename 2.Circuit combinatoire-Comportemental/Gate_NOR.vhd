library IEEE;
use IEEE.std_logic_1164.all;

entity Gate_NOR is
    port(
        a   : in std_logic_vector (1 downto 0);
        s   : out std_logic);
end Gate_NOR;

architecture behavior of Gate_NOR is

    begin

        process(a)
            begin
                case(a) is
                    when "00"=> s<='1';
                    when "01"=> s<='0';
                    when "10"=> s<='0';
                    when "11"=> s<='0';
                end case;
        end process;

end behavior;