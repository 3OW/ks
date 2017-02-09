//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package ks.simulations.uebung_vrmittlung;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;


//
// TODO documentation
//
network Network
{
    @display("bgb=860,625");
    types:
        channel focable extends ned.DatarateChannel
        {
            delay = 5us;
            datarate = 10Gbps;
        }

        channel tpcable extends ned.DatarateChannel
        {
            delay = 0.5us;
            datarate = 1Gbps;
        }

		// Fiber-Optics-Cable 
    submodules:
        RouterA: Router {
            @display("p=142,373");
            gates:
                pppg[4];

        }
        RouterB: Router {
            @display("p=142,94");
            gates:
                pppg[4];
        }
        S1: StandardHost {
            @display("p=608,369;i=device/server");
            gates:
                pppg[1];
        }
        extern: Router {
            parameters:
                @display("p=142,487");
            gates:
                pppg[1];

        }
        W1: StandardHost {
            @display("p=341,88");
            gates:
                pppg[1];
        }
        W2: StandardHost {
            @display("p=566,130");
            gates:
                pppg[1];
        }
        W3: StandardHost {
            @display("p=439,191");
            gates:
                pppg[1];
        }
        W4: StandardHost {
            @display("p=433,298");
            gates:
                pppg[1];
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=760,579");

        }
    connections:
        extern.pppg[0] <--> focable <--> RouterA.pppg[3];
        RouterA.pppg[1] <--> focable <--> RouterB.pppg[3];
        RouterA.pppg[0] <--> tpcable <--> S1.pppg[0];
        RouterB.pppg[0] <--> tpcable <--> W1.pppg[0];
        RouterB.pppg[1] <--> tpcable <--> W2.pppg[0];
        RouterB.pppg[2] <--> tpcable <--> W3.pppg[0];
        RouterA.pppg[2] <--> tpcable <--> W4.pppg[0];
}

