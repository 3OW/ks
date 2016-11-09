package ks.simulations.netzwerkzugang;

import inet.node.ethernet.EtherHost;
import inet.node.ethernet.EtherSwitch;
import ned.DatarateChannel;

import inet.common.scenario.ScenarioManager;

//
// Sample Ethernet LAN: four hosts connected to two switches.
//
network Network

{
    @display("bgb=653,267");
    types:
        channel TPcable extends DatarateChannel
        {
            delay = 0.1us;  // ca. 20 m Kabellänge
            datarate = 100Mbps;
        }
    submodules:
        scenarioManager: ScenarioManager {
            @display("p=582,24");
        }

        hostA: EtherHost {
            parameters:
                @display("p=82,55");
        }

        hostB: EtherHost {
            parameters:
                @display("p=258,55");
        }

        hostC: EtherHost {
            parameters:
                @display("p=506,201");
        }

        hostD: EtherHost {
            parameters:
                @display("p=325,201");
        }

        switch1: EtherSwitch {
            parameters:
                @display("p=162,124");
            gates:
                ethg[4];
        }

        switch2: EtherSwitch {
            parameters:
                @display("p=404,133");
            gates:
                ethg[4];
        }

    connections allowunconnected:
        switch1.ethg[0] <--> TPcable <--> hostA.ethg;
        switch1.ethg[1] <--> TPcable <--> hostB.ethg;
        switch2.ethg[0] <--> TPcable <--> hostC.ethg;
        switch2.ethg[1] <--> TPcable <--> hostD.ethg;

        switch1.ethg[2] <--> TPcable <--> switch2.ethg[2];
}


