void initUpdFirmware(void) {
    HTTP.on("/update", HTTP_POST, []() { //For Update firmware and data.bin
        //HTTP.sendHeader("Connection", "close");
        //HTTP.sendHeader("Access-Control-Allow-Origin", "*");
        //HTTP.send(200, "text/plain", (Update.hasError())?"FAIL":"OK");
        //HTTP.send(302, "text/plain", "Please wait while the device reboots" + (Update.hasError())?"FAIL":"OK");
        HTTP.client().setNoDelay(true);
        //HTTP.send(302, "text/plain", (Update.hasError())?"FAIL":"OK");    
        HTTP.sendHeader("Refresh", "20");
        HTTP.sendHeader("Location", "/");
        delay(500);  
        HTTP.client().stop();
        ESP.restart();
    },[](){
        HTTPUpload& upload = HTTP.upload();
        if(upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        WiFiUDP::stopAll();
        Serial.printf("Update: %s\n", upload.filename.c_str());
        Serial.print("Size: "); Serial.println(upload.totalSize);
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        //size_t content_len = upload.totalSize;
        int cmd = (upload.filename.indexOf("spiffs") > -1) ? 100 : 0; //U_FS : U_FLASH;
        if(!Update.begin(maxSketchSpace,cmd)) {//start with max available size
        //if(!Update.begin(content_len,cmd)) {//start with max available size
                Update.printError(Serial);
        }
        }
        else if(upload.status == UPLOAD_FILE_WRITE) {
        if(Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
            Update.printError(Serial);
        }
        }
        else if(upload.status == UPLOAD_FILE_END) {
        if(Update.end(true)) { //true to set the size to the current progress
            Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
            String answerUpdate = "Status update: " + String(Update.hasError()?"FAIL":"OK") + ". Please wait while the device reboots";
            HTTP.send(302, "text/html", answerUpdate);
            delay(500);
        } else {
            Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
        }
        yield();
    }); 
} 