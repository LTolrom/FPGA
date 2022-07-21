library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Circuit4 is
    port(
        clk,load    : in std_logic;
        D           : in std_logic_vector(3 downto 0);
        O_sig       : out std_logic);
end Circuit4;

architecture behavior of Circuit4 is
    signal Q    : std_logic_vector(3 downto 0);

    begin
        process(clk)
        begin
            if rising_edge(clk) then
                if load='1' then
                    Q<=D;
                else
                    Q<='0'&Q(3 downto 1);
                end if;
            end if;
        end process;
        O_sig<=Q(0);
end behavior;