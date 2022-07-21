library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity circuit3_E is
    port(D  : in std_logic_vector(3 downto 0);
        A   : out std_logic_vector(1 downto 0);
        V   : out std_logic );
end circuit3_E;

architecture behavior of circuit3_E is
  
    begin
  
        A(0)<=D(3) nor (not D(2) and D(1));
        A(1)<=D(3) nor D(2);
        V<= ((D(3) nor D(2)) nor D(0)) nor D(1);
        
    end behavior;