library IEEE;
use IEEE.std_logic_1164.all;

entity Gate_NOR_T is
    port(
        a   : in std_logic_vector (1 downto 0);
        s   : out std_logic);
end Gate_NOR_T;

architecture behavior of Gate_NOR_T is

    begin

    with a select
        s<= '1' when "00",
            '0' when others;

end behavior;