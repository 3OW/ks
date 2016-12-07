#include <httpServer.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>


using namespace std;
using namespace inet;

namespace http {

//#############################################################################
// Dieser Bereich ist durch Sie zu analysieren bzw. zu bearbeiten
//#############################################################################

//---------------------------------------------------------------//

void prepareReply(char *request, RawPacket *packet, int numBytes) {

    string document = "";
    string reply;
    string retcode;

    // Pfad zum bereitszustellenden Dokument extrahieren
    string result = parseGET(request);
    string contentType;

    if (!isdigit(result[0])) {
        // Kein Fehler beim parsen aufgetreten

        // Test welches Dokument angefordert wurde
        if (result == "page1") {

            // HTTP-body (HTML == Dokument) erzeugen
            document = "<html><body> Es wurde das Dokument '" + result + "' angefordert!</body></html>";
            contentType = "text/html";
            // HTTP-Returncode
            retcode = CODE_200;

        } else if (result == "page2") {
            // hier muss eine bestimmte Menge Text erzeugt werden: Anzahl der Zeichen im Text = "numBytes"
            for (int i=0; i<numBytes; i++) {
                document += 'a';
            }
            contentType = "text/plain";
            // HTTP-Returncode
            retcode = CODE_200;

        } else {
            // Dokument nicht gefunden
            retcode = CODE_404;

            // HTTP-body (HTML == Dokument) erzeugen
            document = "<html><body>Datei nicht gefunden: " + retcode + "</body></html>";
            contentType = "text/html";
        }
    } else  {
        // Fehler

        retcode = result;

        // HTTP-body (HTML == Dokument) erzeugen
        document = "<html><body>Fehler im HTTP-Request: " + retcode + "</body></html>";
        contentType = "text/html";
    }

    // HTTP-Reply erzeugen
    reply = "HTTP/1.0 " + retcode + "\r\n"
            "Content-Type: " + contentType + "\r\n"
            "Content-Length: " + to_string(document.length()) + "\r\n\r\n" +
            document;

    // HTTP-Reply zum Übertragen vorbereiten
    fillPacket(packet, reply);
}

//---------------------------------------------------------------//

string parseGET(string message) {

    // aus der empfangenen HTTP-Nachricht ein C++ Input-String-Stream-Objekt erzeugen
    istringstream msg(message);
    string line, str;

    // erste Zeile des HTTP-Requests lesen
    getline(msg, line);
    size_t first = 0;

    try {
        // ersten Eintrag ("GET") suchen
        size_t last = line.find_first_of(' ', first);
        str = trim(line.substr(first, (last - first)));
        if (str != "GET")
            // Fehler - kein "GET-Request "
            return CODE_400;

        // zweiten Eintrag ("/path/to") suchen
        first =last;
        last = line.find_first_of(' ', first + 1);
        string path = trim(line.substr(first, (last - first + 1))).substr(1);

        // dritten Eintrag ("HTTP/1.0") suchen
        first = last;
        last = line.find_first_of("\n\r", first + 1);
        str = trim(line.substr(first, (last - first)));
        if (str != "HTTP/1.0")
            // Fehler
            return CODE_505;

        // Test auf Feld: "Host"
        getline(msg, line);

        first = line.find_first_of(" ");
        last = line.find_first_of("\n\r");
        str = trim(line.substr(first, last-first));

        if (str != SERVER_NAME)
            // Fehler - kein oder falsches "Host"-Feld
            return CODE_403;

        // Kein Fehler gefunden - Pfad übergeben
        return path;
    }
    catch (int e)
    {
        // Konsole und Event-Log schreiben
        cout << "Unbekannter Fehler im HTTP-Request" << '\n';
        EV << "Unbekannter Fehler im HTTP-Request" << '\n';
        return CODE_400;
    }
}
};

//#############################################################################
// ENDE Dieser Bereich ist durch Sie zu analysieren bzw. zu bearbeiten
//#############################################################################
