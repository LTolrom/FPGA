library IEEE;
use IEEE.std_logic_1164.all;

entity decodeur_e is
    port(
        A   : in std_logic_vector(1 downto 0);
        D   : out std_logic_vector(3 downto 0));
end decodeur_e;

architecture behavior of decodeur_e is
    begin
        with A select
            d<="0001" when "00",
                "0010" when "01",
                "0100" when "10",
                "1000" when "11",
                "0000" when others;
    end behavior;