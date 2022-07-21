library IEEE;
use IEEE.std_logic_1164.all;

entity Gate_AND_E is
    port(
        a   : in std_logic_vector (1 downto 0);
        s   : out std_logic);
end Gate_AND_E;

architecture behavior of Gate_AND_E is

    begin

    s<=a(0) and a(1);

end behavior;

    
