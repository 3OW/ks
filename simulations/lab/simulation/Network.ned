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
                ethg[12];
        }

        SwitchA2: EtherSwitch {
            parameters:
                @display("p=242,241");
            gates:
                ethg[12];
        }

        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=50,21");
        }

        HostB: StandardHost {
            parameters:
                @display("p=407,527");
            gates:
                ethg[1];
        }

        HttpServerB: StandardHost {
            parameters:
                @display("p=376,242");
            gates:
                ethg[1];
        }

        RouterB: Router {
            parameters:
                @display("p=407,365");
            gates:
                ethg[2];
        }

        SwitchB1: EtherSwitch {
            parameters:
                @display("p=407,436");
            gates:
                ethg[12];
        }

        SwitchB2: EtherSwitch {
            parameters:
                @display("p=519,241");
            gates:
                ethg[12];
        }

        HostC: StandardHost {
            parameters:
                @display("p=653,527");
            gates:
                ethg[1];
        }

        HttpServerC: StandardHost {
            parameters:
                @display("p=622,242");
            gates:
                ethg[1];
        }

        RouterC: Router {
            parameters:
                @display("p=653,365");
            gates:
                ethg[2];
        }

        SwitchC1: EtherSwitch {
            parameters:
                @display("p=653,436");
            gates:
                ethg[12];
        }

        SwitchC2: EtherSwitch {
            parameters:
                @display("p=765,241");
            gates:
                ethg[12];
        }

        HostD: StandardHost {
            parameters:
                @display("p=924,527");
            gates:
                ethg[1];
        }

        HttpServerD: StandardHost {
            parameters:
                @display("p=893,242");
            gates:
                ethg[1];
        }

        RouterD: Router {
            parameters:
                @display("p=924,365");
            gates:
                ethg[2];
        }

        SwitchD1: EtherSwitch {
            parameters:
                @display("p=924,436");
            gates:
                ethg[12];
        }

        SwitchD2: EtherSwitch {
            parameters:
                @display("p=1036,241");
            gates:
                ethg[12];
        }

    connections allowunconnected:
        SwitchA1.ethg[7] <--> tpcable <--> HostA.ethg[0];
        SwitchA1.ethg[9] <--> tpcable <--> RouterA.ethg[0];
        SwitchA2.ethg[5] <--> tpcable <--> RouterM.ethg[0];
        SwitchA2.ethg[3] <--> tpcable <--> HttpServerA.ethg[0];
        SwitchA2.ethg[1] <--> tpcable <--> RouterA.ethg[1];
        SwitchB2.ethg[4] <--> tpcable <--> HttpServerB.ethg[0];
        SwitchB2.ethg[2] <--> tpcable <--> RouterB.ethg[1];
        SwitchB1.ethg[8] <--> tpcable <--> HostB.ethg[0];
        SwitchB1.ethg[10] <--> tpcable <--> RouterB.ethg[0];
        SwitchC2.ethg[3] <--> tpcable <--> HttpServerC.ethg[0];
        SwitchC2.ethg[1] <--> tpcable <--> RouterC.ethg[1];
        SwitchC1.ethg[7] <--> tpcable <--> HostC.ethg[0];
        SwitchC1.ethg[9] <--> tpcable <--> RouterC.ethg[0];
        SwitchD2.ethg[4] <--> tpcable <--> HttpServerD.ethg[0];
        SwitchD2.ethg[2] <--> tpcable <--> RouterD.ethg[1];
        SwitchD1.ethg[8] <--> tpcable <--> HostD.ethg[0];
        SwitchD1.ethg[10] <--> tpcable <--> RouterD.ethg[0];
        SwitchB2.ethg[6] <--> tpcable <--> RouterM.ethg[1];
        SwitchC2.ethg[5] <--> tpcable <--> RouterM.ethg[2];
        SwitchD2.ethg[6] <--> tpcable <--> RouterM.ethg[3];
}

