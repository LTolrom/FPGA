library IEEE;
use IEEE.std_logic_1164.all;

entity DemiA_1b_E is
    port(
        a   : in std_logic_vector (1 downto 0);
        r   : out std_logic;
        s   : out std_logic);
end DemiA_1b_E;

architecture behavior of DemiA_1b_E is

    begin
    
    r<=a(0) and a(1);
    s<=a(0) xor a(1);

end behavior;