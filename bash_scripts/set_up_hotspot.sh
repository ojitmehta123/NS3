#!/bin/bash
# Checking if a hotspot with name 'up-squared' exists
STR1=$(nmcli connection show | grep 'up-squared-2')
STR2="up-squared-2"
if [[ $STR1 == *$STR2* ]]
then
    echo "No new hotspot created" 
else
    echo "Hotspot with ssid 'up-squared-2' created" 
    # Create a connection
    nmcli connection add type wifi ifname '*' con-name up-squared-2 autoconnect yes ssid up-squared-2
    # Put it in access point
    nmcli connection modify up-squared-2 802-11-wireless.mode ap 802-11-wireless.band bg ipv4.method shared
    # There is no need to add a password
fi