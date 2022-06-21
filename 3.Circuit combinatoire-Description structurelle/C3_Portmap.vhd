library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity C3 is
    port(
        E : in std_logic_vector(3 downto 0);
        C,S : out std_logic);
end C3;

architecture behavoir of C1 is

    signal s1,s2     : std_logic;


    component C_OR is
        port(
            A_OR,B_OR   : in std_logic;
            S_OR        : out std_logic);
    end component;

    component C_AND is
        port(
            A_AND,B_AND : in std_logic;
            S_AND       : out std_logic);
    end component;
    

    begin
        U1:C_AND(A_AND=>E(0),B_AND=>E(1),S_AND=>s1);
        U2:C_AND(A_AND=>E(2),B_AND=>E(3),S_AND=>s2);
        U3:C_AND(A_AND=>E(0),B_AND=>E(3),S_AND=>C);
        U4:C_OR(A_OR=>s0,B_OR=>S1,S_OR=>S);

end behavior;