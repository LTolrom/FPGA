library IEEE;
use IEEE.std_logic_1164.all;

entity Gate_OR is
    port(
        a   : in std_logic_vector (1 downto 0);
        s   : out std_logic);
end Gate_OR;

architecture behavior of Gate_OR is

    begin
        process(a)
            begin
                if a ="00" then
                    S<='0';
                else
                    s<='1';
            end if;
        end process;

end behavior;