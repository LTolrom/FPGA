library IEEE;
use IEEE.std_logic_1164.all;

entity Gate_AND_T is
    port(
        a   : in std_logic_vector (1 downto 0);
        s   : out std_logic);
end Gate_AND_T;

architecture behavior of Gate_AND_T is

    begin

    with a select
        s<= '1' when "11",
            '0' when others;

end behavior;