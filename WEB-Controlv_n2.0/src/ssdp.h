void SSDP_init(void) {
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(SSDP_Name);
  SSDP.setSerialNumber("001788102201");
  SSDP.setURL("/");
  SSDP.setModelName(modelName);
  SSDP.setModelNumber(nVersion);
  SSDP.setModelURL("http://"+(WiFi.status() != WL_CONNECTED ? WiFi.softAPIP().toString() : WiFi.localIP().toString()));
  SSDP.setManufacturer("LIGHTWELL");
  SSDP.setManufacturerURL("https://led-lightwell.eu");
  SSDP.begin();
}