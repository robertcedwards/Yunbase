#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int numRuns = 1;   // execution count, so this doesn't run forever
int maxRuns = 10;   // maximum number of times the Choreo should be executed

void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until a serial console is connected.
  delay(4000);
  while(!Serial);
  Bridge.begin();
}
void loop()
{
  if (numRuns <= maxRuns) {
    Serial.println("Running Put - Run #" + String(numRuns++));
    
    TembooChoreo PutChoreo;

    // invoke the Temboo client
    PutChoreo.begin();
    
    // set Temboo account credentials
    PutChoreo.setAccountName(TEMBOO_ACCOUNT);
    PutChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    PutChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // set choreo inputs
    PutChoreo.addInput("RequestBody", "{ \"first\": \"Jack\", \"last\": \"Spasadrrow\" }");
    PutChoreo.addInput("RequestHeaders", "{ \"Content-Type\":\"application/json\"}");
    PutChoreo.addInput("URL", "https://yun.firebaseio.com/Names/.json");
    // or 
    // identify choreo to run
    PutChoreo.setChoreo("/Library/Utilities/HTTP/Put");
    
    // run choreo; when results are available, print them to serial
    PutChoreo.run();
  delay(50); // Poll every 50ms
  Process p;        // Create a process and call it "p"
p.runShellCommand("curl -k -X POST https://yun.firebaseio.com/Names.json -d '{ \"first\" : \"peepee\",\"last\" : \"caca\"}'");  
    
    while(PutChoreo.available()) {
      char c = PutChoreo.read();
      Serial.print(c);
    }
    PutChoreo.close();

  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between Put calls
}
