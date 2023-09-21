if [ $1 = '1' ]; then
sudo ~/SelfCode/relayPower/relay_power_local /dev/ttyUSB1 0 1
else
sudo ~/SelfCode/relayPower/relay_power_local /dev/ttyUSB1 0 0
fi
