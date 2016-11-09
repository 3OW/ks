package ks.simulations.lab.integration;

import inet.node.inet.StandardHost;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;

network HostX
{
    @display("bgb=225,161");

    submodules:
        HostX: StandardHost {
            parameters:
                numExtInterfaces = 1;
                @display("p=118,94");
        }

        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=50,21");
        }

    connections  allowunconnected:
}
