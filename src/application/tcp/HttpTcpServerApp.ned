
package ks.application.tcp;

import inet.applications.contract.ITCPApp;

// -----------------------------------------------------

//
// Ein HTTP-Server-Modul, das über einen kompletten Netzwerkstack mittels TCP  mit einem HTTP-Client-Modul kommuniziert.
//
// Das Modul ist als TCPApp ausgeführt und kann deshalb als Anwendung mit einem StandardHost-Modul verwendet werden
//
simple HttpTcpServerApp like ITCPApp
{
    parameters:
		string localAddress = default(""); // IP-Adresse, die beim Senden verwendet wird; hier: automatisch festgelegt
        int localPort = default(80); // Die eigene Portadresse.
    	 	int numBytes = default(4000);	// Länge des HTML-Dokuments

        string dataTransferMode = default("bytestream"); // Es werden reale Daten übertragen.
        
    gates:
        input tcpIn;
        output tcpOut;
}
