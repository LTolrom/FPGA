library IEEE;
use IEEE.std_logic_1164.all;

entity C_2x1_mux is
    generic(
        bit_lenght      : integer :=8);
    port(E0 : in std_logic_vector(bit_lenght-1 downto 0);
        E1  : in std_logic_vector(bit_lenght-1 downto 0);
        Sel : in std_logic;
        S   : out std_logic_vector(bit_lenght-1 downto 0));

end C_2x1_mux;

architecture behavior of C_2x1_mux is
 
    begin

        with Sel select
            S <= E0 when '0',
                E1 when '1';
    
end behavior;