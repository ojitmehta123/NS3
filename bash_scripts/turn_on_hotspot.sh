#!/bin/bash
# Enable it (run this command each time you want to enable the access point)

sudo nmcli connection up up-squared-2
sudo ifconfig wlp2s0 10.1.1.2 netmask 255.255.255.0
