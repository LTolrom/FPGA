library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity C4 is
    port(
        A,B,Cin     : in std_logic;
        S,Cout      : out std_logic);
end C4;

architecture behavoir of C4 is

    signal s0,s1,s3     : std_logic;

    component C_XOR is
        port(
            A_XOR,B_XOR : in std_logic;
            S_XOR       : out std_logic);
    
    End component;

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
        U1:C_XOR    (A_XOR=>A   ,B_XOR=>B   ,S_AND=>s0);
        U2:C_XOR    (A_XOR=>s0  ,B_XOR=>Cin ,S_XOR=>S);
        U3:C_AND    (A_AND=>Cin ,B_AND=>s0  ,S_AND=>s1);
        U4:C_AND    (A_AND=>A   ,B_AND=>B   ,S_AND=>s2);
        U4:C_OR     (A_OR=>s1   ,B_OR=>s2   ,S_OR=>Cout);

end behavior;