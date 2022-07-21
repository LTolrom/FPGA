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
        process (Sel,X0,X1,X2,X3)
            begin
                if Sel = "00" then
                    M<=X0;
                elsif Sel ="01" then
                    M<=X1;
                elsif Sel ="10" then
                    M<=X2;
                elsif Sel ="11" then
                    M<=X3;
                end if;
        end process;

end behavior;