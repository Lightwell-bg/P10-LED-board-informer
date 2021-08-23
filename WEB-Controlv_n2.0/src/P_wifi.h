const char P_wifi[] PROGMEM =  R"=====(
<html>
    <head>
        <meta name = "viewport" content = "width=device-width, initial-scale=1.0">
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led screen ver:2.0</title>
        <link rel="icon" href="/img/favicon.png" type="images/png">
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_ssid(submit) {
                server = "/ssid?ssid=" + val('ssid') + "&password=" + encodeURIComponent(val('password'))+"&ssidAP=" 
                + val('ssidap') + "&passwordAP=" + encodeURIComponent(val('passwordAp'))+"&ssdp=" + val('ssdp') +"&ipap4=" + val('ipap4');
                send_request(submit,server);
                alert("Изменения вступят в силу после перезагрузки");
            }
        </script>
    </head>
    <body onload = "load();">
        <header>
            <span class="opt_cn">{{modelName}}_</span><span id="ver">{{nVersion}}</span><br>
            <span class="opt_cn">IP_</span>
            <span id="ip">{{ip}}</span><br>
            <span class="opt_cn">Time on ESP:</span>
            <span id="time">{{time}}</span>
        </header>       
        <central-unit>
            <div class="menu_unit">
                <a class="link__img" href="/index.html"><span class="ico__text">Screen</span></a>			
                <a class="link__img" href="/wifi.html"><span class="ico__text">Wifi</span></a>
                <a class="link__img" href="/time.html"><span class="ico__text">Time</span></a>
                <a class="link__img" href="/help.html"><span class="ico__text">Help</span></a>
                <a class="link__img" href="#"><span class="ico__text" onclick="restart(this,'Restart ESP?');">Restart</span></a>
            </div>
            <div class="body__center">
                <titles>
                    <span class="opt_cn">WIFI SETUP</span>
                </titles>
                <div class="informer">
                    <span class="opt_cn">Connecting to the internet network will allow you to synchronize the time and receive a weather forecast.</span>
                </div>
                <div id="main_unit">
                    <paragraph>
                        <span class="opt_cn">Connecting to WiFi router</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn">Enter the name of the WiFi network</span></td>
                                <td><input type="text" class="field" id="ssid" value="{{ssid}}" pattern="[-\w\s#@/]{1,15}" placeholder="name WiFi network"></td>
                            </tr>
                            <tr>  
                                <td align = "right"><span class="opt_cn">Enter the WiFi network password</span></td>
                                <td><input class="field" id="password" value="{{password}}" pattern=".{6,15}" onfocus="this.type='text'" type="password"></td>
                            </tr>
                        </table>
                    </center>
                    <paragraph>
                        <span class="opt_cn">Access Point Parameters</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn">Enter the name of the access point	</span></td>
                                <td><input type="text" class="field" id="ssidap" value="{{ssidAP}}" class="form-control" pattern="[-\w\s#@/]{1,15}" placeholder="access point name"></td>
                            </tr>
                            <tr>
                                <td align = "right"><span class="opt_cn">Enter the access point password	</span></td>  
                                <td><input class="field" id="passwordAp" value="{{passwordAP}}" pattern=".{0,15}" onfocus="this.type='text'" type="password"></td>
                            <tr>
                            <tr>
                                <td align = "right"><span class="opt_cn" id="P_wifi_ipAP">Access Point IP </span><strong> {{ipap1_3}}</strong></td>  
                                <td><input type="text" class="field" id="ipap4" value="{{ipap4}}" class="form-control" pattern="[0-9]{1,2}" placeholder="access point IP"></td>
                            <tr>
                        </table>
                    </center>
                    <paragraph>
                        <span class="opt_cn" id="P_wifi_setSSDP">Device name in LAN</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn" id="P_wifi_ssdp">Enter the name of SSDP</span></td>
                                <td><input type="text" class="field" id="ssdp" value="{{SSDP}}" class="form-control" pattern="[-\w\s#@/]{1,15}" placeholder="name of SSDP"></td>
                            </tr>
                        </table>
                    </center>					
                    <span class="save_booton" id="save" onclick="set_ssid(this);">Save</span>
                </div>
            </div>
            <div class="menu_unit" id="langs">
                <a><span class="ico__text" onclick="set_lang_f(this, 'EN');">EN</span></a>			
                <a><span class="ico__text" onclick="set_lang_f(this, 'RU');">RU</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'BG');">BG</span></a>
            </div>
        </central-unit>
    </body>
</html>
)=====";