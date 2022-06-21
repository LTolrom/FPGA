library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Flipflop is
    port(
        D,Clk,R   : in std_logic;
        Q,Qn    : out std_logic);
end Flipflop;

architecture behavior of Flipflop is
    begin
        process(Clk,R)
        begin
            if R='0' then
                Q<='0';
                Qn<='1';
            elsif rising_edge(clk) then
                Q<=D;
                Qn<=not(D);
            end if;
        end process;
end architecture;
