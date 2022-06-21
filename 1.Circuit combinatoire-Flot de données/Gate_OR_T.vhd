library IEEE;
use IEEE.std_logic_1164.all;

entity Gate_OR_T is
    port(
        a   : in std_logic_vector (1 downto 0);
        s   : out std_logic);
end Gate_OR_T;

architecture behavior of Gate_OR_T is

    begin

    with a select
        s<= '0' when "00",
            '1' when others;

end behavior;