package ks.simulations.lab.simulation;

import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.EtherSwitch;
import ned.DatarateChannel;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;

network Network
{
    @display("bgb=1092,602,white");
    types:
        channel tpcable extends DatarateChannel
        {
            parameters:
                delay = 0.1us;
                datarate = 100Mbps;
        }

    submodules:
        HostA: StandardHost {
            parameters:
                @display("p=130,527");
            gates:
                ethg[1];
        }

        HttpServerA: StandardHost {
            parameters:
                @display("p=99,242");
            gates:
                ethg[1];
        }

        RouterA: Router {
            parameters:
                @display("p=130,365");
            gates:
                ethg[2];
        }

        RouterM: Router {
            parameters:
                @display("p=558,97");
            gates:
                ethg[4];
        }

        SwitchA1: EtherSwitch {
            parameters:
                @display("p=130,436");
            gates:
                ethg[2];
        }

        SwitchA2: EtherSwitch {
            parameters:
                @display("p=242,241");
            gates:
                ethg[3];
        }

        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=50,21");
        }

    connections:
        SwitchA1.ethg[0] <--> tpcable <--> HostA.ethg[0];
        SwitchA1.ethg[1] <--> tpcable <--> RouterA.ethg[0];
        SwitchA2.ethg[0] <--> tpcable <--> RouterM.ethg[0];
        SwitchA2.ethg[1] <--> tpcable <--> HttpServerA.ethg[0];
        SwitchA2.ethg[2] <--> tpcable <--> RouterA.ethg[1];
}

