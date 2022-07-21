library library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity PWM is
    generic ( --pour modifier des valeurs
        bit_depth   : integer   := 8;
        input_clk   : integer    := 50000000; --50MHz
        freq        : integer    :=50); --50Hz
    port(
        pwm_out     : out std_logic;
        resolution  : in std_logic_vector(bit_deph-1 downto 0)
        clk         : in std_logic:
        enable      : in std_logic);
    end PWM;

architecture behavior of PWM is

    constant max_freq_count : integer :=input_clk/freq;
    constant pwm_step       : integer := max_freq_count / (2**bit_depth) -- 3906 steps

    signal PWM_value        :std_logic :='0';
    signal freq_count       :integer range 0 to max_freq_count := 0;
    signal pwm_count        :integer range 0 to 2**bit_depth :=0;
    signal max_pwm_count    : integer ranger 0 to 2**bit_depth :=0;
    signal pwm_step_count   : integer range 0 max_freq_count :=0 ;

