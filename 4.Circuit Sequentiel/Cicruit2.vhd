library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Circuit2 is
    port(
        A,B,C,D,R,clk       : in std_logic;
        S               : out std_logic);
end Circuit2;

architecture behavior of Circuit2 is
    signal T    : std_logic;
    signal Q    : std_logic_vector(1 downto 0);

    begin
    T<= (A AND B) OR (C OR D);
    
    process(clk,r)
        begin
            if r='0' then
                Q(0)<='0';
                Q(1)<='0';
            elsif rising_edge(clk) then
                Q(0)<=T;
                Q(1)<=Q(0);
            end if;
    end process;
    S<=Q(0) NAND Q(1);

end behavior;