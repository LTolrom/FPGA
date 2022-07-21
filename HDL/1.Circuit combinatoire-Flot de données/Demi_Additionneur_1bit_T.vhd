library IEEE;
use IEEE.std_logic_1164.all;

entity DemiA_1b2_T is
    port(
        a   : in std_logic_vector (1 downto 0);
        r   : out std_logic;
        s   : out std_logic);
end DemiA_1b2_T;

architecture behavior of DemiA_1b2_T is

    begin

    with a select
        r <= '1' when "11",
            '0' when others;
    with a select
        s <= '0' when "00" | "11",
            '1' when others;

end behavior;