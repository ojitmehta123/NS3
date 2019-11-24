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
#include <signal.h>

#include <fstream>
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

  std::cout<<"In server mode..."<<std::endl;
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);

  /**********************************************************************************************/

  /* Keyboard interrupt to destoy simulator */

  signal(SIGINT, destroySimulator);

  /**********************************************************************************************/

  /* wlp58s0 should be replaced with the name of the wifi card on your laptop */
  std::string deviceName ("wlp2s0");
  std::string encapMode ("Dix"); 
  double stopTime = 8;
  uint32_t nNodes = 2;

  /**********************************************************************************************/

  /* Bash scripts */

  /* Setup WiFi hotspot with ssid up-squared-1 */
  system("/home/tyjo/projects/sop/ns3/NS3/NS3/bash_scripts/set_up_hotspot.sh");
  /* Turn hotspot ON */
  system("/home/tyjo/projects/sop/ns3/NS3/NS3/bash_scripts/turn_on_hotspot.sh");

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

  /* Defining the physical layer */

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

  /* Assigning an ip address to the server
   * Server - 10.1.1.1
   */

  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  d = emu.Install (n.Get (0));
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.NewAddress();
  i = ipv4.Assign (d); 

  /***********************************************************************************************/
    

  /* Setting up a UDP server application */

  NS_LOG_INFO ("Create Applications.");
  UdpEchoServerHelper server (9);
  apps = server.Install (n.Get (0));
  apps.Start (Seconds (1.0));      
  apps.Stop (Seconds (stopTime));

  /***********************************************************************************************/

  /* Writing to a pcap file */

  emu.EnablePcapAll ("fd-server", true);
  emu.EnableAsciiAll ("fd-server.tr");

  /***********************************************************************************************/

  /* Actual simulation */

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Stop (Seconds(stopTime+0.5));
  Simulator::Run ();
  NS_LOG_INFO ("Done.");

  /***********************************************************************************************/
}
