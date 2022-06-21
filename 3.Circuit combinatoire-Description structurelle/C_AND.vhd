library IEEE;
use IEEE.std_logic_1164.all;

entity C_AND is
    port(
        A_AND,B_AND : in std_logic;
        S_AND   : out std_logic);
end C_AND;

architecture behavior of C_AND is
    begin

    with (A_AND&B_AND) select
        s<= '1' when "11",
            '0' when others;

end behavior;

    
