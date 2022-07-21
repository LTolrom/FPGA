library ieee;
use ieee.std_logic_1164.all;


entity [test_UUT] is -- empty entity
end [test_UUT]





architecture [testbenk_arch] of [test_UUT] is
------------Component declaration ------------------
Component UUT:
port
(
.....................
);
end component;--------------------------------

------------Define signal for each port in the UUT---------------------------
signal ..........
signal .......... :=’0’; -- start value for inputs--------------------

begin

-------------------Component instantiation-----------------------
U1: UUT
port map (...........);------------------------


--------------Test sequencer to provide stimuli----------------------
STIMULI:
process
begin
.......
wait;
end process;
end architecture;
