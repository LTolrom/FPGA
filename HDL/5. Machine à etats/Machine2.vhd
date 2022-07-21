library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Machine2 is
    port(
        clk,E,R :in std_logic;
        Sout    :out std_logic);
end Machine2;

architecture behavior of Machine2 is
    type state_type is (Q0,Q1,Q2);
    signal y    : state_type;

    begin
        process(clk,R)
        begin
            if R='0' then
                y<=Q0;
            elsif rising_edge(clk) then
                case y is
                    when Q0 =>  if (E='0') then y<=Q1;
                                else y<=Q2;
                                end if;
                    when Q1 =>  if (E='1')then y<=Q2;
                                end if;
                    when Q2 =>  if (E='0') then y<=Q1;
                                end if;
                    when others =>  y<=Q0;
                    end case;
            end if;
        end process;
    Sout<= '1' when y=Q1 else '0';
end behavior; 

