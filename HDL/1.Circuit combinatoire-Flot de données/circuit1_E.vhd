library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity circuit1_E is
    port(a  : in std_logic_vector(5 downto 0);
        b   : in std_logic_vector(5 downto 0);
        f   : out std_logic_vector(5 downto 0) );
end circuit1_E;

architecture behavior of circuit1_E is

    begin
        f(0)<=a(0) and b(0);
        f(1)<=a(0) nand b(0);
        f(2)<=a(0) or b(0);
        f(3)<=a(0) nor b(0);
        f(4)<=a(0) xor b(0);
        f(5)<=a(0) xnor b(0);
        
    end behavior;