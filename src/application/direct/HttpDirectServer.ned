
package ks.application.direct;

// -----------------------------------------------------

//
// Ein HTTP-Server-Modul, das ohne Netzwerk mit einem HTTP-Client-Modul kommuniziert
//
simple HttpDirectServer
{
    parameters:
    	 	int numBytes = default(4000);	// Länge des HTML-Dokuments
    	 	
    gates:
        input in;
        output out;
}

