library IEEE;
use IEEE.std_logic_1164.all;

entity Multiplex_2a1_E is
    port(E0 : in std_logic_vector(7 downto 0);
        E1  : in std_logic_vector(7 downto 0);
        Sel : in std_logic;
        S   : out std_logic_vector(7 downto 0));
end Multiplex_2a1_E;

architecture behavior of Multiplex_2a1_E is
begin 
    s<=(not(Sel) and E0) or (Sel and E1);

end behavior;