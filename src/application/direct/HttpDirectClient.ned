
package ks.application.direct;

// -----------------------------------------------------

//
// Ein HTTP-Client-Modul, das ohne Netzwerk mit einem HTTP-Server-Modul kommuniziert
//
simple HttpDirectClient
{
    parameters:
        string httpHost; //< Hostname für Host-Feld im HTTP-Request 
        string page; //< Name des Dokuments im HTTP-Request 

    gates:
        input in;
        output out;
}

