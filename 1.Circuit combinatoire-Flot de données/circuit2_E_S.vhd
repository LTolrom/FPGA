library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity circuit2_E_S is
    port(e  : in std_logic_vector(3 downto 0);
        c   : out std_logic;
        s   : out std_logic );
end circuit2_E_S;

architecture behavior of circuit2_E_S is
    
    signal Sig1,Sig2        :std_logic :='0';

    begin
        sig1<=e(0) and e(1);
        sig2<=e(2) and e(3);
        s<=sig1 or sig2;
        c<=e(0) and e(3);
        
    end behavior;