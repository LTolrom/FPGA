library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity C_OR is
    port(
        A_OR,B_OR : in std_logic;
        S_OR   : out std_logic);
end C_OR;

architecture behavior of C_OR is
    begin

        with (A_OR&B_OR) select
            s<= '0' when "00",
                '1' when others;
end behavior;