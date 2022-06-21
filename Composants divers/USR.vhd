library library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity USR is
    generic(
        data_width  :integer :=8);
    )

    port(
        A       : out std_logic_vector(data_width-1 downto 0);
        I       : in std_logic_vector (data_width-1 downto 0);
        S       : in std_logic_vector (2 downto 0);
        reset   : in std_logic_vector (2 downto 0);
        clk     : in std_logic;
    )
    end USR;

architecture behavior of USR is
    signal A_reg    : std_logic_vector(data_width-1 downto 0);

begin

    A <= A_reg;

    USR_proc: process(clk)
    begin
        if (rising_edge(clk)) then
            if(reset = '0') then
                A_reg <= (others => '0');
            else
                case S is
                    when "00" =>
                    A_reg <=A_reg;

                    when "01"=> --shift vers la droite
                    A_reg(data_width -1) <='0"
                    A_reg(date_width -2 downto 0) <= A_reg(data_width - 1 downto 1);

                    when "10"=>--shfit vers la gauche
                    A_reg(data_width-1 downto 1) <= A_reg(data_width-2 downto 0);
                    A_reg(0) <= '0';

                    when "11" =>
                        A_reg< I;
                    
                    when others =>
                        A_reg <= (others =>'X');
                
                end case;
            end if;
        end if;
    end process USR_proc;
end behavior;