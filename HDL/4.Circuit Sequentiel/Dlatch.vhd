library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Dlatch is
    port(
        D,EN    : in std_logic;
        Q,Qn    : out std_logic);
end Dlatch;

architecture behavior of Dlatch is
    begin
        process(D,EN)
            begin
                if (EN='1') then
                    Q<=D;
                    Qn<=not(D);
                end if;
        end process;
end behavior;