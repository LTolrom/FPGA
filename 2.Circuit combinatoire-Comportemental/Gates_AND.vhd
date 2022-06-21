library IEEE;
use IEEE.std_logic_1164.all;

entity Gate_AND is
    port(
        a   : in std_logic_vector (1 downto 0);
        s   : out std_logic);
end Gate_AND;

architecture behavior of Gate_AND is

    begin
    process(a)
        begin
            if a= ("00" OR "01" OR "10") then
                s <= '0';
            elsif a="11" then
                s <='1';
            end if;
    end process;

end behavior;

    
