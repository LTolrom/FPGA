library IEEE;
use IEEE.std_logic_1164.all;

entity Multiplex_2a1_T is
    port(E0 : in std_logic_vector(7 downto 0);
        E1  : in std_logic_vector(7 downto 0);
        Sel : in std_logic;
        S   : out std_logic_vector(7 downto 0));

end Multiplex_2a1_T;

architecture behavior of Multiplex_2a1_T is
 
    begin

        with Sel select
            S<= E0 when '0',
                E1 when '1';
    
end behavior;