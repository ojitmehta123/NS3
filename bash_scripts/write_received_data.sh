#!/bin/bash

# Extracting only the data from the frame and writing it to a file
RECEIVED_DATA=$(tcpdump -r /home/tyjo/projects/sop/ns3/NS3/NS3/build/bin/fd-server-0-1.pcap -c 1 -A udp port 9 | awk -F'~|~' '{print $2}' | tail -n 2)
RECEIVED_DATA=${RECEIVED_DATA%?}
echo $RECEIVED_DATA > /home/tyjo/projects/sop/ns3/NS3/NS3/bash_scripts/received_data.txt
