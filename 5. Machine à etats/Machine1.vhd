library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Machine1 is
    port(
        E,Clk,R     : in std_logic;
        Sout        : out std_logic);
end Machine1;

architecture behavior of Machine1 is

    type state_type is (Q0,Q1,Q2,Q3,Q4);
    signal y    : state_type;

    begin
        process(Clk,R)
        begin
        if (R='0') then
            y<=Q0;
        elsif rising_edge(clk) then
            case(y) is
                when Q0 =>  if (E='0') then y<=Q1;
                            else y<=Q2;
                            end if;
                when Q1 =>  if (E='1')then y<=Q3;
                            end if;
                when Q2 =>  if (E='0') then y<=Q4;
                            end if;
                when Q3 =>  if (E='0') then y<=Q4;
                            else y<=Q2;
                            end if;
                when Q4 =>  if (E='0') then y<=Q1;
                            else y<=Q3;
                            end if;
                when others =>  y<=Q0;
                end case;
        end if;
        end process;
    
    Sout<='1' when (y=Q3 OR y=Q4) else '0';
    
end behavior;