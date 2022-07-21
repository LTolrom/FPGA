library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity C4 is
    generic(
        bit_lenght      : integer :=8);
    port(
        X0,X1,X2,X3     : in std_logic_vector(bit_lenght-1 downto 0);
        C               : in std_logic_vector(1 downto 0);
        S               : out std_logic_vector(bit_lenght-1 downto 0));
end C4;

architecture behavoir of C4 is

    signal s0,s1    : std_logic;

    component C_2x1_mux is
        generic(
        bit_lenght      : integer :=8);
        port(
        E0  : in std_logic_vector(bit_lenght-1 downto 0);
        E1  : in std_logic_vector(bit_lenght-1 downto 0);
        Sel : in std_logic;
        S   : out std_logic_vector(bit_lenght-1 downto 0));
    end component;
    

    begin
        U1:C_2x1_mux    (E0=>X0  ,E1=>X1    ,Sel=>C(0)     ,S=>s0);
        U2:C_2x1_mux    (E0=>X2  ,E1=>X3    ,Sel=>C(0)     ,S=>s1);
        U3:C_2x1_mux    (E0=>s0  ,E1=>s1    ,Sel=>C(1)     ,S=>S);

end behavior;