library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity C2 is
    port(
        E : in std_logic_vector(3 downto 0);
        S : out std_logic);
end C2;

architecture behavoir of C2 is

    signal s1,s2     : std_logic;


    component C_OR is
        port(
            A_OR,B_OR : in std_logic;
            S_OR   : out std_logic);
    end component;

    component C_AND is
        port(
            A_AND,B_AND : in std_logic;
            S_AND   : out std_logic);
    end component;

    component C_XNOR is
        port(
            A_XNOR,B_XNOR   : in std_logic;
            S_XNOR          : out std_logic);
    end component;
    

    begin
        U1:C_XNOR(A_XNOR =>E(0),B_XNOR =>E(1),S_XNOR=>s0);
        U2:C_AND(A_AND=>E(2),B_AND=>E(3),S_AND=>s2);
        U3:C_OR(A_OR=>s1,B_OR=>s2,S_OR=>S);

end behavior;