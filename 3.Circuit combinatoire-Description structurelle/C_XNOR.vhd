library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity C_XNOR is
    port(
        A_XNOR,B_XNOR   : in std_logic;
        S_XNOR          : out std_logic);
end C_XNOR;

architecture behavior of C_XNOR is
    begin
        with (A_XNOR&B_XNOR) select
        s<= '1' when "11" | "00",
            '0' when others;
end behavior;