library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Machine4 is
    port(
        clk,r,e : in std_logic;
        Sout    : out std_logic_vector (2 downto 0));
end Machine4;

architecture behavior of Machine 4 is
    type state_type is (A,B,C);
    signal y    : state_type;
    begin
        process(clk,r)
            begin
                if r='0' then
                    y<=S0;
                elsif rising_edge(clk) then
                    case y is
                        when A =>  if (E='1') then y<=B;
                                    end if;
                        when B =>  if (E='0')then y<=A;
                                    else y<=C;
                                    end if;
                        when C =>  if (E='0') then y<=A;
                                    end if;
                        when others =>  y<=A;
                        end case;
                end if;
        end process;

        process(y,E)
            begin
                case y is
                    when A =>  if (E='0') then Sout<="00";
                                else Sout<="01";
                                end if;
                    when B =>  if (E='0')then Sout<="01";
                                else Sout<="10";
                                end if;
                    when C =>  if (E='0') then Sout<="10";
                                else Sout <="01";
                                end if;
                    when others =>  Sout<="00";  
                end case;
        end process;