library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Multiplex_4a1_T is
    generic(
        bit_depth : integer :=8);
    port(X0 : in std_logic_vector(bit_depth-1 downto 0);
        X1  : in std_logic_vector(bit_depth-1 downto 0);
        X2 : in std_logic_vector(bit_depth-1 downto 0);
        X3  : in std_logic_vector(bit_depth-1 downto 0);
        sel : in std_logic_vector(1 downto 0);
        M   : out std_logic_vector(bit_depth-1 downto 0));
end Multiplex_4a1_T;

architecture behavior of Multiplex_4a1_T is

     begin

        with Sel select
            M<= X0 when "00",
                X1 when "01",
                X2 when "10",
                X3 when "11";

end behavior;