
package ks.application.tcp;

import inet.applications.contract.ITCPApp;

// -----------------------------------------------------

//
// Ein HTTP-Client-Modul, das über einen kompletten Netzwerkstack mittels TCP  mit einem HTTP-Server-Modul kommuniziert.
//
// Das Modul ist als TCPApp ausgeführt und kann deshalb als Anwendung mit einem StandardHost-Modul verwendet werden.
//
simple HttpTcpClientApp like ITCPApp
{
    parameters:
        string httpHost; //< Hostname für Host-Feld im HTTP-Request 
        string page; //< Name des Dokuments im HTTP-Request 

        string connectAddress; // Die IP-Adresse (der Name kann verwendet werden) des Servers.
        int connectPort; // Die Portadresse des Servers.
        volatile double processingTime @unit(s) = default(0); // Die Zeit (je Empfang), die der Client zum Verarbeiten 
        																						 // der vom Server empfangenen Daten benötigt.

        int localPort = default(2080);	// Die eigene Portadresse.
        string localAddress = default(""); // IP-Adresse, die beim Senden verwendet wird; hier: automatisch festgelegt.
        string dataTransferMode = default("bytestream"); // Es werden reale Daten übertragen.

    gates:
        input tcpIn;
        output tcpOut;
}

