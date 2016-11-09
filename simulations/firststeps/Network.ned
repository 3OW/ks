
package ks.simulations.firststeps;

import inet.examples.adhoc.hostautoconf.Host;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.EtherSwitch;
import inet.node.xmipv6.CorrespondentNode6;


network Network
{
    parameters:

        @display("bgb=712,295");
    types:
        channel EthernetTP100 extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = 0.1us; // 20 Meter Länge
        }

    submodules:
        server: StandardHost {
            parameters:
                @display("i=device/pc3;p=659,150");
            gates:
                ethg[1];
        }

        client: StandardHost {
            parameters:
                @display("p=93,125;i=device/pc2");
            gates:
                ethg[1];
        }

        router: Router {
            parameters:
                @display("p=383,129");
            gates:
                ethg[2];
        }

        switch1: EtherSwitch {
            @display("p=241,173");
            gates:
                ethg[2];
        }

        switch2: EtherSwitch {
            @display("p=500,55");
            gates:
                ethg[2];
        }

        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=62,31");
                config = xml("<config> <interface hosts='*' address='192.168.x.x' netmask='255.255.255.0'/> </config>");
        }

    connections:
        client.ethg[0] <--> EthernetTP100 <--> switch1.ethg[0];
        router.ethg[0] <--> EthernetTP100 <--> switch1.ethg[1];

        server.ethg[0] <--> EthernetTP100 <--> switch2.ethg[0];
        router.ethg[1] <--> EthernetTP100 <--> switch2.ethg[1];

}
