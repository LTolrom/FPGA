library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity C1 is
    port(
        A,B : in std_logic;
        R,S : out std_logic);
end C1;

architecture behavoir of C1 is

    component C_XOR is
        port(
            A_XOR,B_XOR : in std_logic;
            S_XOR       : out std_logic);
    
    End component;

    component C_AND is
        port(
            A_AND,B_AND : in std_logic;
            S_AND       : out std_logic);
    end component;

    begin
        U1:C_XOR(A_XOR=>A,B_XOR=>B,S_XOR=>S);
        U2:C_AND(A_AND=>A,B_AND=>B,S_AND=>R);

end behavior;