library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Machine3 is
    port(
        clk,r,e : in std_logic;
        Sout    : out std_logic);
end Machine3;

architecture behavoir of machine3 is
    type state_type is (S0,S1,S2);
    signal y    : state_type;
    begin
        process(clk,r)
            begin
                if r='0' then
                    y<=S0;
                elsif rising_edge(clk) then
                    case y is
                        when S0 =>  if (E='0') then y<=S2;
                                    else y<=S1;
                                    end if;
                        when S1 =>  if (E='0')then y<=S2;
                                    end if;
                        when S2 =>  if (E='1') then y<=S1;
                                    end if;
                        when others =>  y<=S0;
                        end case;
                end if;
        end process;

        process(y,E)
            begin
                case y is
                    when S0 =>  if (E='0') then Sout<='0';
                                else Sout<='0';
                                end if;
                    when S1 =>  if (E='0')then Sout<='1';
                                else Sout<='1';
                                end if;
                    when S2 =>  if (E='0') then Sout<='0';
                                else Sout <='0';
                                end if;
                    when others =>  Sout<='0';  
                end case;
        end process;
end behavoir;