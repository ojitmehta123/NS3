#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/fd-net-device-module.h"
#include <vector>
#include <set>
#include <sstream>
#include  <cstdlib>
#include <cmath>
#include <ctime> 
#include <math.h> 
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("WifiSimpleAdhoc");

struct Neighbour
{
  int nodeid;
  double bPower;
  double distance;
};

class Sensor_Node {  
  public:
     double bPower;
     std::vector<Neighbour> v;
     int cluster_id;
};  

Sensor_Node nodes[30];
int numNodes = 30;
int sendPacketCount = 0;
int receivedPacketCount = 0;
static void GenerateTraffic (Ptr<Socket> socket, uint32_t pktSize,
                             uint32_t pktCount, Time pktInterval )
{
  if (pktCount > 0)
    {
      std::ostringstream msg; 
      msg << rand() % 100 + 1 << '\0';
      Ptr<Packet> packet = Create<Packet> ((uint8_t*) msg.str().c_str(), msg.str().length());
      socket->Send (packet);
      sendPacketCount++;
      NS_LOG_UNCOND("Sending packet from node at " << Simulator::Now()); 
      Simulator::Schedule (pktInterval, &GenerateTraffic,
                           socket, pktSize,pktCount - 1, pktInterval);
    }
  else
    {
      socket->Close ();
    }
}

void ReceivePacket (Ptr<Socket> socket)
{ 
  while (Ptr<Packet> msg = socket->Recv ())
    {
      uint8_t *buffer = new uint8_t[msg->GetSize ()];
      msg->CopyData(buffer, msg->GetSize ());
      std::string s = std::string((char*)buffer);
      receivedPacketCount++;
      NS_LOG_UNCOND ("CH received one data packet : " << s  << " at " << Simulator::Now());
      NS_LOG_UNCOND("");
    }
}

void NodetoNodeCommunication (NodeContainer c , int node1 , int node2 , uint32_t pktSize, uint32_t pktCount, Time pktInterval)
{
  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
  Ptr<Socket> recvSink = Socket::CreateSocket (c.Get (node2), tid);
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
  recvSink->Bind (local);
  recvSink->SetAllowBroadcast (true);
  recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
  Ptr<MobilityModel> mob = c.Get(node2)->GetObject<MobilityModel>();
  Vector pos = mob->GetPosition ();
  NS_LOG_UNCOND("Receiver's Position" << " POS: x=" << pos.x << ", y=" << pos.y);
  
  Ptr<Socket> source = Socket::CreateSocket (c.Get (node1), tid);  
  InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
  source->SetAllowBroadcast (true);
  source->Connect (remote);
  mob = c.Get(node1)->GetObject<MobilityModel>();
  pos = mob->GetPosition ();
  NS_LOG_UNCOND("Transmitter's Position" << " POS: x=" << pos.x << ", y=" << pos.y);
  Simulator::ScheduleWithContext (source->GetNode ()->GetId (),
                                Seconds (1.0), &GenerateTraffic,
                                source, pktSize, pktCount, pktInterval);
}

void CHtoCHCommunication (NodeContainer c , int node1 , int node2 , uint32_t pktSize, uint32_t pktCount, Time pktInterval)
{
  NS_LOG_UNCOND("..........Inter CH-CH communication..........");
  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
  Ptr<Socket> recvSink = Socket::CreateSocket (c.Get (node2), tid);
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 180);
  recvSink->Bind (local);
  recvSink->SetAllowBroadcast (true);
  recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));

  Ptr<Socket> source = Socket::CreateSocket (c.Get (node1), tid);  
  InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 180);
  source->SetAllowBroadcast (true);
  source->Connect (remote);

  Simulator::ScheduleWithContext (source->GetNode ()->GetId (),
                                Seconds (1.0), &GenerateTraffic,
                                source, pktSize, pktCount, pktInterval);
}

static void GenerateBroadCastTraffic (Ptr<Socket> socket, uint32_t pktSize,
                             uint32_t pktCount, Time pktInterval , int nodeid)
{
  if (pktCount > 0)
    {
      std::ostringstream msg;
      NS_LOG_UNCOND("Sending broadcast packet from node : " << nodeid << " at " << Simulator::Now()); 
      msg << "NodeID:" << nodeid << '\0';
      nodes[nodeid].bPower--;
      Ptr<Packet> packet = Create<Packet> ((uint8_t*) msg.str().c_str(), msg.str().length());
      socket->Send (packet);
      Simulator::Schedule (pktInterval, &GenerateBroadCastTraffic,
                           socket, pktSize,pktCount - 1, pktInterval, nodeid);
    }
  else
    {
      socket->Close ();
    }
}

void ReceiveBroadCastPacket( int nodeid  ,Ptr<Socket> socket){
  while (Ptr<Packet> msg = socket->Recv ())
    {
      NS_LOG_UNCOND ("Received one broadcast packet by node : " <<  nodeid << " at " << Simulator::Now());
      
      uint8_t *buffer = new uint8_t[msg->GetSize ()];
      msg->CopyData(buffer, msg->GetSize ());
      std::string s = std::string((char*)buffer);
      std::string delimiter = ":";
      size_t pos = 0;
      std::string token;
      while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
      }
      receivedPacketCount++;
      std::stringstream temp(s); 
      int neigh = 0; 
      temp >> neigh;
      Neighbour n;
      n.nodeid = neigh;
      n.bPower = nodes[neigh].bPower;
      //n.distance = sqrt(pow((nodes[neigh].xLoc - nodes[nodeid].xLoc),2) + pow((nodes[neigh].yLoc - nodes[nodeid].yLoc),2) + pow((nodes[neigh].zLoc - nodes[nodeid].zLoc),2));
      n.distance = 5;
      nodes[nodeid].v.push_back(n);
    }
}

void BroadCastCommunication (NodeContainer c , int nodecount , int nodeid, uint32_t pktSize, uint32_t pktCount , Time pktInterval)
{
  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");

  Ptr<Socket> source = Socket::CreateSocket (c.Get (nodeid), tid);  
  InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 100);
  source->SetAllowBroadcast (true);
  source->Connect (remote);
  Ptr<Socket> recvSink[nodecount - 1];
  Ptr<MobilityModel> mob = c.Get(nodeid)->GetObject<MobilityModel>();
  Vector pos = mob->GetPosition ();
  NS_LOG_UNCOND("");
  NS_LOG_UNCOND("Broadcast Node's Positon: x=" << pos.x << ", y=" << pos.y);

  int j=0;
  for (int i = 0; i < nodecount ;i++)
  {
    if(i != nodeid){
      sendPacketCount++;
      recvSink[j] = Socket::CreateSocket (c.Get(i), tid );
      InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 100);
      recvSink[j]->Bind(local);
      recvSink[j]->SetRecvCallback(MakeBoundCallback (&ReceiveBroadCastPacket ,i));
      mob = c.Get(i)->GetObject<MobilityModel>();
      pos = mob->GetPosition ();
      NS_LOG_UNCOND("Neighbour Node :"<< i <<" Positon: x=" << pos.x << ", y=" << pos.y);
    }
  }

  Simulator::ScheduleWithContext (source->GetNode ()->GetId (),
                                Seconds (1.0), &GenerateBroadCastTraffic,
                                source, pktSize, pktCount, pktInterval , nodeid);
}

static void GenerateClusterHeadTraffic (Ptr<Socket> socket, uint32_t pktSize, uint32_t pktCount, Time pktInterval , int nodeid)
{
  if (pktCount > 0)
    {
      std::ostringstream msg;
      NS_LOG_UNCOND("Sending cluster head packet from node : " << nodeid  << " at " << Simulator::Now()); 
      msg << "ClusterID:" << nodeid << '\0';
      nodes[nodeid].bPower--;
      Ptr<Packet> packet = Create<Packet> ((uint8_t*) msg.str().c_str(), msg.str().length());
      socket->Send (packet);
      Simulator::Schedule (pktInterval, &GenerateClusterHeadTraffic,
                           socket, pktSize,pktCount - 1, pktInterval , nodeid);
    }
  else
    {
      socket->Close ();
    }
}

void ReceiveClusterHeadPacket(int nodeid ,Ptr<Socket> socket){
  while (Ptr<Packet> msg = socket->Recv ())
    {
      NS_LOG_UNCOND ("Received one cluster head packet by node : " <<  nodeid  << " at " << Simulator::Now());
      uint8_t *buffer = new uint8_t[msg->GetSize ()];
      msg->CopyData(buffer, msg->GetSize ());
      std::string s = std::string((char*)buffer);
      std::string delimiter = ":";
      size_t pos = 0;
      std::string token;
      receivedPacketCount++;
      while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
      }
      std::stringstream temp(s); 
      int cid = 0; 
      temp >> cid;
      if (nodes[nodeid].cluster_id > cid)
      {
        nodes[nodeid].cluster_id = cid;
      }
    }
}

void CHCommunication (NodeContainer c,int nodeid, uint32_t pktSize, uint32_t pktCount , Time pktInterval)
{
  if(nodes[nodeid].cluster_id >= nodeid)
  {
    nodes[nodeid].cluster_id = nodeid;
    TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
    Ptr<Socket> source = Socket::CreateSocket (c.Get (nodeid), tid);  
    InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 120);
    source->SetAllowBroadcast (true);
    source->Connect (remote);
    Ptr<MobilityModel> mob = c.Get(nodeid)->GetObject<MobilityModel>();
    Vector pos = mob->GetPosition ();
    NS_LOG_UNCOND("");
    NS_LOG_UNCOND("CH Broadcast Node: " << nodeid << " Positon: x=" << pos.x << ", y=" << pos.y);
    int neighbours = nodes[nodeid].v.size();
    Ptr<Socket> recvSink[neighbours];

    for (int i = 0; i < neighbours ;i++)
    {
      sendPacketCount++;
      recvSink[i] = Socket::CreateSocket (c.Get(nodes[nodeid].v[i].nodeid), tid );
      InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 120);
      recvSink[i]->Bind(local);
      recvSink[i]->SetRecvCallback(MakeBoundCallback (&ReceiveClusterHeadPacket , nodes[nodeid].v[i].nodeid));
      mob = c.Get(nodes[nodeid].v[i].nodeid)->GetObject<MobilityModel>();
      pos = mob->GetPosition ();
      NS_LOG_UNCOND("Neighbour Node :"<< nodes[nodeid].v[i].nodeid <<" Positon: x=" << pos.x << ", y=" << pos.y);
    }

    Simulator::ScheduleWithContext (source->GetNode ()->GetId (),
                                  Seconds (1.0), &GenerateClusterHeadTraffic,
                                  source, pktSize, pktCount, pktInterval , nodeid);
  }
}

void CheckNeighbours()
{
  NS_LOG_UNCOND("");
  NS_LOG_UNCOND(".....Checking all the neighbour tables.....");
  for(int i = 0 ; i < numNodes; i++)
  {
    NS_LOG_UNCOND(nodes[i].v.size());
  }

}

void DataCollection(NodeContainer c , int cluster_id, uint32_t pktSize, uint32_t pktCount , Time pktInterval)
{
  NS_LOG_UNCOND("");
  NS_LOG_UNCOND("..........Data Collection..........");

  for(int i = 0; i < numNodes ; i++)
  {
    if(i!=cluster_id)
    {
      Simulator::Schedule(Seconds (i*2.0), &NodetoNodeCommunication, c, i, cluster_id , pktSize, pktCount, pktInterval);
    }
  }
}

void DisplayCH(NodeContainer c , uint32_t pktSize, uint32_t pktCount , Time pktInterval)
{
  std::set<int> ch;
  NS_LOG_UNCOND("");
  NS_LOG_UNCOND("..........Cluster Head ID..........");
  for(int i = 0; i< numNodes ; i++)
  {
    ch.insert(nodes[i].cluster_id);
    NS_LOG_UNCOND(nodes[i].cluster_id);
  }
  std::set<int>::iterator it1;
  for (it1 = ch.begin(); it1!=ch.end();  ++it1){
    NS_LOG_UNCOND("Cluster Head Node ID : " << *it1);
  }
  Simulator::Schedule(Seconds (5.0) , &DataCollection , c , *it1 , pktSize , pktCount , pktInterval);
}

void DisplayPacketCount()
{
  NS_LOG_UNCOND("Sent Packets: " << sendPacketCount);
  NS_LOG_UNCOND("Received Packets: " << receivedPacketCount);
}
int main (int argc, char *argv[])
{
  srand (time(NULL));
  std::string phyMode ("DsssRate1Mbps");
  uint32_t packetSize = 1000; // bytes
  uint32_t numPackets = 1;
  double interval = 1.0; // seconds
  bool verbose = false;
  int maxPower = 100;
  // Convert to time object
  Time interPacketInterval = Seconds (interval);

  // disable fragmentation for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2200"));
  // turn off RTS/CTS for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
  // Fix non-unicast data rate to be the same as that of unicast
  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode",
                      StringValue (phyMode));

  NodeContainer c;
  c.Create (numNodes);
  


  for (int i = 0 ; i < numNodes ; i++)
  {
    nodes[i].bPower = maxPower;
    nodes[i].cluster_id = i;    
  }

  WifiHelper wifi;
  if (verbose)
  {
      wifi.EnableLogComponents ();  // Turn on all Wifi logging
  }

  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);

  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();


  wifiPhy.Set ("RxGain", DoubleValue (0) );
  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
  wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);

  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
 
  wifiChannel.AddPropagationLoss ("ns3::LogDistancePropagationLossModel", "Exponent", DoubleValue (3.26));
  //2.0 gives 1850 m distance range
  //3.0 gives 150 m distance range
  //3.5 gives 73 m distance range
  //4.0 gives 43 m distance range
  //150^(3/value) = range 

  wifiPhy.SetChannel (wifiChannel.Create ());

  // Add a mac and disable rate control
  WifiMacHelper wifiMac;
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));
  // Set it to adhoc mode
  wifiMac.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);

  // Note that with FixedRssLossModel, the positions below are not
  // used for received signal strength.
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  // positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  // positionAlloc->Add (Vector (5.0, 0.0, 0.0));
  // positionAlloc->Add (Vector(10.0,0.0,0.0));
  // positionAlloc->Add (Vector(15.0,0.0,0.0));
  for( int i = 0 ; i < numNodes ;i++)
  {
    double temp = 5 * i; 
    positionAlloc->Add(Vector(temp,0,0));
  }
  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel("ns3::ConstantVelocityMobilityModel");
  //mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  mobility.Install(c);
  for (NodeContainer::Iterator i = c.Begin(); i != c.End(); i++)
  {
    Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable> ();
    Ptr<ConstantVelocityMobilityModel> model = (*i)->GetObject<ConstantVelocityMobilityModel>();
    model->SetVelocity(Vector(rand->GetValue(0,5),0,0));
  }
  //CH-CH communication on higher power level
  NodeContainer ch;
  ch.Add (c.Get(nodes[0].cluster_id));
  ch.Create (1);
  WifiHelper wifiHP;
  wifiHP.SetStandard (WIFI_PHY_STANDARD_80211b);
  YansWifiPhyHelper wifiPhyHP =  YansWifiPhyHelper::Default ();
  wifiPhyHP.Set ("RxGain", DoubleValue (0) );
  wifiPhyHP.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
  YansWifiChannelHelper wifiChannelHP;
  wifiChannelHP.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannelHP.AddPropagationLoss ("ns3::LogDistancePropagationLossModel", "Exponent", DoubleValue (2.0));
  wifiPhyHP.SetChannel (wifiChannelHP.Create ());
  WifiMacHelper wifiMacHP;
  wifiHP.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));
  wifiMacHP.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devicesHP = wifiHP.Install (wifiPhyHP, wifiMacHP, ch);
  MobilityHelper mobilityHP;
  Ptr<ListPositionAllocator> positionAllocHP = CreateObject<ListPositionAllocator> ();
  //positionAllocHP->Add (Vector (0.0, 0.0, 0.0));
  positionAllocHP->Add (Vector (1000.0, 0.0, 0.0));
  mobilityHP.SetPositionAllocator (positionAllocHP);
  mobilityHP.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobilityHP.Install (ch.Get(1));

  InternetStackHelper internet;
  internet.Install (c);
  internet.Install (ch.Get(1));

  Ipv4AddressHelper ipv4;
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.SetBase ("192.168.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (devices);
  Ipv4InterfaceContainer iHP = ipv4.Assign (devicesHP);
  // Tracing
  wifiPhy.EnablePcap ("cluster_members", devices);
  wifiPhyHP.EnablePcap ("wifi-hp", devicesHP);
  // Output what we are doing
  NS_LOG_UNCOND ("..........Testing clustering algorithm..........");

 
  for ( int i = 0; i < numNodes ; i++){
    Simulator::Schedule(Seconds (2.0*i), &BroadCastCommunication, c, numNodes, i, packetSize, numPackets, interPacketInterval );
  }

  int rand_n = rand();
  rand_n = rand_n %1000;

  Simulator::Schedule(Seconds((2*numNodes+5)),&CheckNeighbours);
  // power : 90-100 80-90 70-90
  // connectivity : numNodes numNodes-2 numNodes-4
  for(int i = 0; i < numNodes; i++)
  { 
    Simulator::Schedule (Seconds((2*numNodes+6.0) + 3.0*std::fmod((rand_n*(i+1)),numNodes)) , &CHCommunication , c , i , packetSize , numPackets , interPacketInterval ); 
  }

  Simulator::Schedule(Seconds (30.0*numNodes) , &DisplayCH ,  c , packetSize , numPackets , interPacketInterval);

  Simulator::Schedule(Seconds (40.0*numNodes), &CHtoCHCommunication, ch, 0 , 1 , packetSize, numPackets, interPacketInterval);

  Simulator::Schedule(Seconds(42.0*numNodes),&DisplayPacketCount);
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}