library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Circuit1 is
    port(
        A,B,C,D,Clk,R   : in std_logic;
        S               : out std_logic);
end Circuit1;

architecture behavior of Circuit1 is
    signal s1,s2    : std_logic;
    signal Q        : std_logic_vector(1 downto 0);

    begin
        s1<=A and B;
        s2<=C and D;

    process(clk,R)
        begin
            if (R='0')then
                Q(0)<='0';
                Q(1)<='0';
            elsif rising_edge(clk) then
                Q(0)<=s1;
                Q(1)<=s2;
            end if;
    end process;

    S<=Q(0) NOR Q(1);

end behavior;

