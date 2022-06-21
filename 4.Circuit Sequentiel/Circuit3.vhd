library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Circuit3 is
    generic(
        bit_lenght  : integer :=8);
    port(
        clk :in std_logic;
        D   :in std_logic_vector(bit_lenght-1 downto 0);
        S   :out std_logic_vector(bit_lenght-1 downto 0));
end Circuit3;

architecture behavior of Circuit3 is
    signal Qa,Qb,Qc : std_logic_vector(bit_lenght-1 downto 0);

    begin
        process(clk)
        begin
            if rising_edge(clk) then
                Qa<=D;
                Qb<=Qa;
                Qc<=Qb;
                S<=Qc;
            end if;
        end process;
end behavior;
