# P10 LED board informer for displaying the seawater temperature and air temperature obtained from the Internet (with DMD2 library)P10 LED board informer for displaying the seawater temperature and air temperature obtained from the Internet (with DMD2 library)
Wemos ESP8266 board receives data on sea water temperature and air temperature via the Internet at **openweathermap.org** and **worldseatemp.com** and transmits them via the **UART protocol** to the Arduino board for further display on LED modules.

## Features include:
- Accurate Clock refresh off Internet Time Servers
- Local Seawater temperature and Local air temperature (refreshed every 10 - 30 minutes)
- Configured through Web Interface
- Support for OTA (loading firmware over WiFi)
- Update firmware through web interface
- Video: [https://www.youtube.com/](https://www.youtube.com/watch?v=WpL9w_X3GiA&feature=youtu.be "https://www.youtube.com/")

## Required Parts:
Wemos D1 Mini:  [http://alii.pub/40d3u7](http://alii.pub/40d3u7 "http://alii.pub/40d3u7")
Arduino Nano Mini USB [http://alii.pub/4ekhzu](http://alii.pub/4ekhzu "http://alii.pub/4ekhzu")
Dip 16 PIN 2.54MM pitch Male Socket straight IDC [http://alii.pub/5ym6j6](http://alii.pub/5ym6j6 "http://alii.pub/5ym6j6")
Power supply 5V  – $8 from Aliexpress [http://got.by/4ekh09](http://got.by/4ekh09 "http://got.by/4ekh09")
Note: **Using the links provided here help to support these types of projects. Thank you for the support.**

## Wiring for the Wemos D1 Mini and Arduino Nano to the LED Matrix Display
[![](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/2021-08-23_16-40-08.png)](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/2021-08-23_16-40-08.png)

## Packages -- the following packages and libraries are used (download and install):
**ESP8266**

- &lt;ESP8266WiFi.h&gt;
- &lt;ESP8266WebServer.h&gt;
- &lt;ESP8266HTTPClient.h&gt;
- &lt;WiFiClientSecure.h&gt;
- &lt;ESP8266SSDP.h&gt;
- &lt;Updater.h&gt;//for update firmware and SPIFFS
- &lt;FS.h&gt;
- &lt;ArduinoJson.h&gt;        //https://github.com/bblanchon/ArduinoJson.git
- "RTClib.h" //https://github.com/adafruit/RTClib
- "ESPTimeFunc.h" https://github.com/Lightwell-bg/ESPTimeFunc
- "NetCrtESP.h" https://github.com/Lightwell-bg/NetCrtESP

**Arduino Nano**

- &lt;DMD2.h&gt;
- &lt;EEPROM.h&gt;
- &lt;avr/wdt.h&gt; //Interrupt
- &lt;SoftwareSerial.h&gt;
- &lt;TimeLib.h&gt; //https://github.com/PaulStoffregen/Time Michael Margolis


## Initial Configuration
Starting with version 2.0 editing the config.h file is optional. All API Keys are now managed in the Web Interface It is not required to edit the config.h file before loading and running the code.

Open Weather Map free API key: [http://openweathermap.org/](http://openweathermap.org/ "http://openweathermap.org/") -- this is used to get weather data and the latitude and longitude for the current time zone. 
NOTE: The settings in the config.h are the default settings for the first loading. After loading you will manage changes to the settings via the Web Interface. If you want to change settings again in the config.h, you will need to erase the file system on the Wemos or use the “Reset Settings” option in the Web Interface.
During the first time run Wemos D1 mini will try to connect to your Wi-Fi and fail (because it doesn't have any previously saved Wi-Fi credentials). This will cause it to start up an access point, which serves up a captive configuration portal.
You can connect to this access point to select and enter credentials for your network. Save configuration and restart device. (Wemos  D1 mini will restart and connect to your Wi-Fi network).

## Web Interface
All LED board informer management is carried out using a web browser.  On first power-up, it  will serve a hotspot called **LWSeaTemp**. For clock adjustment and manipulation open a webpage with the **192.168.4.1** address. Within this hotspot you can manually override the time and date, set temperature manually and update software.
For Wi-Fi network connection please input its SSID and password.  After successful connection LED board informer will begin to receive and transmit information over the Internet. NTP servers are used to get accurate time. To get the current weather and forecast use the service [https://openweathermap.org](https://openweathermap.org "https://openweathermap.org") (you need to register and get an API key). 
[![](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/wi01.png)](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/wi01.png)[![](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/wi03.png)](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/wi03.png)

## Donation or Tip
Please do not feel obligated, but donations and tips are warmly welcomed. I have added the donation button at the request of a few people that wanted to contribute and show appreciation. Thank you, and enjoy the application and project.

<form action="https://www.paypal.com/donate" method="post" target="_top">
<input type="hidden" name="hosted_button_id" value="7A5NNR3623WZ2" />
<input type="image" src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif" border="0" name="submit" title="PayPal - The safer, easier way to pay online!" alt="Donate with PayPal button" />
<img alt="" border="0" src="https://www.paypal.com/en_BG/i/scr/pixel.gif" width="1" height="1" />
</form>


Or -- you can buy me something from our store: [https://diy.led-lightwell.eu/](https://diy.led-lightwell.eu/ "https://diy.led-lightwell.eu/")

## Contributors
Contributing to this software is warmly welcomed. You can do this basically by forking from master, committing modifications and then making a pulling requests against the latest DEV branch to be reviewed (follow the links above for operating guide). Detailed comments are encouraged. Adding change log and your contact into file header is encouraged. Thanks for your contribution.
When considering making a code contribution, please keep in mind the following goals for the project:
User should not be required to edit the config.h file to compile and run. This means the feature should be simple enough to manage through the web interface.
Changes should always support the recommended hardware (links above).

[![](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/t00.jpg)](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/t00.jpg)[![](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/inf6416-01.png)](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/inf6416-01.png)[![](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/pcbst03.jpg)](https://github.com/Lightwell-bg/P10-LED-board-informer/blob/main/images/pcbst03.jpg)