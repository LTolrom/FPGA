library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity circuit4_E_S is
    port(A      : in std_logic;
        B       : in std_logic;
        c_in    : in std_logic;
        T       : out std_logic;
        C_out   : out std_logic );

end circuit4_E_S;

architecture behavior of circuit4_E_S is
    signal s0,s1,s2     : std_logic;
  
    begin
  
        s0<= A xor B;
        s1<= s0 and c_in;
        s2<=A and B;
        T<=s0 xor c_in;
        c_out <=s1 or s2;
        
    end behavior;