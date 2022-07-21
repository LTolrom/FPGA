library IEEE;
use IEEE.std_logic_1164.all;

entity Gate_OR_E is
    port(
        a   : in std_logic_vector (1 downto 0);
        s   : out std_logic);
end Gate_OR_E;

architecture behavior of Gate_OR_E is

    begin

    s<=a(0) or a(1);

end behavior;