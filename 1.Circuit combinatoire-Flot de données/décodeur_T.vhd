library IEEE;
use IEEE.std_logic_1164.all;

entity decodeur_T is
    port(
        A   : in std_logic_vector(1 downto 0);
        D   : out std_logic_vector(3 downto 0));
end decodeur_T;

architecture behavior of decodeur_T is
    begin
        D(0)<=not A(0) and not A(1);
        D(1)<=A(0) and not A(1);
        D(2)<=not A(0) and A(1);
        D(3)<=A(0) and A(1);
end behavior;