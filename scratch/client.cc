/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 University of Washington, 2012 INRIA 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


/* OSI Network Model
 * Application Layer
 * Presentation Layer
 * Session Layer
 * Transport Layer
 * Network Layer
 * Data Link Layer
 * Physical Layer
 */

/* Need this header file to execute shell scripts from the C program */
#include <stdio.h>
/* Need this header file to execute keyboard interrupts */
#include <signal.h>
/* Need this header file to read from a file */
#include <fstream>
#include <sstream>

#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/fd-net-device-module.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("EmulatedUdpEchoExample");


void destroySimulator(int sig){
  Simulator::Destroy();
}

int
main (int argc, char *argv[])
{

  /**********************************************************************************************/

  /* Echo messages */

  std::cout<<"In client mode..."<<std::endl;
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);

  /**********************************************************************************************/

  /* Keyboard interrupt to destroy simulator */

  signal(SIGINT, destroySimulator);

  /**********************************************************************************************/


  /* wlp58s0 should be replaced with the name of the wifi card on your laptop */
  std::string deviceName ("wlp2s0");
  std::string encapMode ("Dix"); 
  double stopTime = 8;
  uint32_t nNodes = 2;

  /***********************************************************************************************/

  /* Getting the data to be sent to the server from a file */

  char data[200];
  FILE *file;
  file = fopen("/home/tyjo/projects/sop/ns3/NS3/NS3/bash_scripts/receive_data.txt","r");
  while(fgets(data, sizeof(data), file)!=NULL)
  std::cout<<data;
  fclose(file);

  /***********************************************************************************************/

  /* Bash scripts */

  /* Turn off our hotspot */
  system("/home/tyjo/projects/sop/ns3/NS3/NS3/bash_scripts/turn_off_hotspot.sh");
  /* Connect to hotspot 'up-squared' */
  system("/home/tyjo/projects/sop/ns3/NS3/NS3/bash_scripts/connect_to_hotspot.sh");

  /***********************************************************************************************/

  GlobalValue::Bind ("SimulatorImplementationType",
                     StringValue ("ns3::RealtimeSimulatorImpl"));
  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

  /***********************************************************************************************/

  /* Creating the nodes required by the topology */

  nNodes = nNodes < 2 ? 2 : nNodes;
  NS_LOG_INFO ("Create nodes.");
  NodeContainer n;
  n.Create (nNodes);

  /***********************************************************************************************/

  /* Setting up an IPV4 stack on the nodes */

  InternetStackHelper internet;
  internet.Install (n);

  /***********************************************************************************************/

  /*Defining the physical layer */
  
  /* By using EmuFdNetDevice, we don't have to define the physical layer.
   * We use the network device that is present on hardware whether it is an ethernet device 
   * or a WiFi card.
   * There is no need to define a WifiHelper like the other ns3 examples
   */
  NS_LOG_INFO ("Create channels.");
  EmuFdNetDeviceHelper emu;
  emu.SetDeviceName (deviceName);
  emu.SetAttribute ("EncapsulationMode", StringValue (encapMode));

  NetDeviceContainer d;
  Ipv4AddressHelper ipv4;
  Ipv4InterfaceContainer i;
  ApplicationContainer apps;

  /***********************************************************************************************/

  /* Assigning an IP address to the client 
   * Client - 10.1.1.1
   */

  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  d = emu.Install (n.Get (0));
  Ptr<FdNetDevice> dev = d.Get (0)->GetObject<FdNetDevice> ();
  /* 9c:b6:d0:dc:d2:b5 : MAC address of the WiFi card on my laptop */
  dev->SetAddress (Mac48Address ("7c:67:a2:b7:f2:f0")); 
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.NewAddress();
  i = ipv4.Assign (d);

  /**********************************************************************************************/

  /* Setting up a UDP client application */
    
  std::string buffer = data;
  uint32_t packetSize = 2048;
  uint32_t maxPacketCount = 1;
  Time interPacketInterval = Seconds (0.1);
  UdpEchoClientHelper client (Ipv4Address ("10.1.1.1"), 9);
  
  client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client.SetAttribute ("PacketSize", UintegerValue (packetSize));
  apps = client.Install (n.Get (0));
  /* Sending a string through a UDP packet */
  client.SetFill(apps.Get(0), data);

  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (stopTime));

  /**********************************************************************************************/

  /* Writing to a pcap file */

  emu.EnablePcapAll ("fd-client", true);
  emu.EnableAsciiAll ("fd-client.tr");

  /**********************************************************************************************/

  /* Actual simulation */

  NS_LOG_INFO ("Run Simulation.");
  NS_LOG_INFO ("Done.");
  Simulator::Stop(Seconds(stopTime+1));
  Simulator::Run ();
  Simulator::Destroy();

  /**********************************************************************************************/
}
