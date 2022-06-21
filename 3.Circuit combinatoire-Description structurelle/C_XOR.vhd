library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity C_XOR is
    port(
        A_XOR,B_XOR   : in std_logic;
        S_XOR       : out std_logic);

End C_XOR;

Architecture behavior of C_XOR is
    begin
        with (A_XOR&B_XOR) select
        s<= '1' when "10" | "10",
            '0' when others;
end behavior;