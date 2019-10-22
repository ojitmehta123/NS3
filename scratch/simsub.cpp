#include "ros/ros.h"
#include "std_msgs/String.h"
#include <bits/stdc++.h>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

std_msgs::String r_str; 
std::string r_str_raw("");
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

void chatterCallback(const std_msgs::String &msg)
{
/*
Serialize the message data here
*/ 
  r_str = msg;
  r_str_raw = msg.data;

}

int main(int argc, char **argv)
{
	CommandLine cmd;
  cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
          
  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue ());
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
    

  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
//  serverApps.Start (Seconds (ros::Time::now().toSec()));
//   clientApps.Start (Seconds (ros::Time::now().toSec()));
//   serverApps.Stop (Seconds (ros::Time::now().toSec()+1000000000000));
//     clientApps.Stop (Seconds (ros::Time::now().toSec()+100000000000));

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  ros::Subscriber sub = n.subscribe("chatter", 10, chatterCallback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::Rate loop_rate(10);
  while (ros::ok())

  {
  //   serverApps.Start (Seconds (ros::Time::now().toSec()));
  // clientApps.Start (Seconds (ros::Time::now().toSec()));
  // serverApps.Stop (Seconds (ros::Time::now().toSec()+1000000000000));
  //   clientApps.Stop (Seconds (ros::Time::now().toSec()+100000000000));

   
      std::cout<<ros::Time::now()<<std::endl;
      std::ostringstream msg; 
      // msg << rand() % 100 + 1 << '\0';
      // std::cout<<r_str_raw.c_str()<<std::endl;
      Ptr<Packet> packet = Create<Packet> ((const uint8_t*) r_str_raw.c_str() , r_str_raw.length());
      // sendPacketCount++;
//   std::cout<<"running"<<std::endl;
      Packet::EnablePrinting();
      // packet->Print(std::cout);
      NS_LOG_UNCOND("Sending packet from node at " << ros::Time::now()); 
      std::cout<<*packet<<std::endl;
      // Simulator::Run();
      // Simulator::Destroy();
  ros::spinOnce();
  loop_rate.sleep();
  }
  Simulator::Destroy ();
  ros::spin();

  return 0;
}