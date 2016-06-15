#!/bin/sh

echo "All Camels on Market ---> cannot TAKE, cannot TRADE!"

read a

cat allCML_cantTake_cantTrade.txt - | ./jaipur


echo "No Hand cards ---> cannot SELL!"

read a

cat noHand_cantSell.txt - | ./jaipur
