const char P_index[] PROGMEM =  R"=====(
<html>
    <head>
        <meta name = "viewport" content = "width=device-width, initial-scale=1.0">
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Informer_clock_weath на ESP8266</title>
        <link rel="icon" href="/img/favicon.png" type="images/png">
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_led(submit) {
                server = "/led?dayModeFrom=" + val('dayModeFrom') + "&dayModeTo=" + val('dayModeTo') + "&brightDay=" + val('brightDay') + "&brightNight=" + val('brightNight');
                server += "&onClock=" + val_sw('onClock') + "&updInter=" + val('updInter');
                send_request(submit,server);
                load();
                alert("Ok");                
            }
            function set_man_temp(submit) {
                server = "/tempman?onAirMan=" + val_sw('onAirMan') + "&airManTemp=" + val('airManTemp') + "&onSeaMan=" + val_sw('onSeaMan') + "&seaManTemp=" + val('seaManTemp');
                send_request(submit,server);
                load();
                alert("Ok");                
            }
            
            function set_weather(submit) {
                server = "/weather?weatherKey=" + val('weatherKey') + "&weatherHost=" + val('weatherHost') + "&cityID=" + val('cityID') + "&seaID=" + val('seaID');
                send_request(submit, server);
                load();
                alert("Ok");                 
            }            
            function sync_time(submit) {
                server = "/Time";
                send_request(submit,server);
                //load_time(submit);
                load();
                alert("Ok");
            }   
            function get_last_update(submit) {
                server = "/Getlastup";
                send_request(submit,server);
                //load_time(submit);
                //load();
                window.location.reload();
                alert("Ok");
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
                <a class="link__img" href="/index.html"><span class="ico__text">Setup</span></a>
                <a class="link__img" href="/wifi.html"><span class="ico__text">Wifi</span></a>
                <a class="link__img" href="/time.html"><span class="ico__text">Time</span></a>
                <a class="link__img" href="/help.html"><span class="ico__text">Help</span></a>
                <a class="link__img" href="#"><span class="ico__text" onclick="restart(this,'ResetESP?');">Restart</span></a>
                <!--<a class="link__img" href="#"><span class="ico__text" onclick="resetConfig(this,'Factory reset?');">Reset</span></a>-->
            </div>
            <titles>
                <span class="opt_cn">Settings Screen</span>
            </titles>
            <div id="main_unit">
                <center>
                    <table>
                        <tr>
                            <td align = "right"><span class="opt_cn">Day mode with:</span></td>
                            <td><select id = "dayModeFrom">
                                <option value = "0"> 0 </option>
                                <option value = "1"> 1 </option>
                                <option value = "2"> 2 </option>
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                                <option value = "9"> 9 </option>
                                <option value = "10"> 10 </option>
                                <option value = "11"> 11 </option>
                                <option value = "12"> 12 </option>
                                <option value = "13"> 13 </option>
                                <option value = "14"> 14 </option>
                                <option value = "15"> 15 </option>
                                <option value = "16"> 16 </option>
                                <option value = "17"> 17 </option>
                                <option value = "18"> 18 </option>
                                <option value = "19"> 19 </option>
                                <option value = "20"> 20 </option>
                                <option value = "21"> 21 </option>
                                <option value = "22"> 22 </option>
                                <option value = "23"> 23 </option>
                            </select></td>
                            <td align = "right"><span class="opt_cn">to:</span></td>
                            <td><select id = "dayModeTo">
                                <option value = "1"> 1 </option>
                                <option value = "2"> 2 </option>
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                                <option value = "9"> 9 </option>
                                <option value = "10"> 10 </option>
                                <option value = "11"> 11 </option>
                                <option value = "12"> 12 </option>
                                <option value = "13"> 13 </option>
                                <option value = "14"> 14 </option>
                                <option value = "15"> 15 </option>
                                <option value = "16"> 16 </option>
                                <option value = "17"> 17 </option>
                                <option value = "18"> 18 </option>
                                <option value = "19"> 19 </option>
                                <option value = "20"> 20 </option>
                                <option value = "21"> 21 </option>
                                <option value = "22"> 22 </option>
                                <option value = "23"> 23 </option>
                                <option value = "24"> 24 </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Brightness during the day:</span></td>
                            <td><input id="brightDay" type="range" value="{{brightDay}}" min="1" max="255">
                            </td>
                            <td align = "right"><span class="opt_cn">at night:</span></td>
                            <td><input id="brightNight" type="range" value="{{brightNight}}" min="1" max="255">
                            </td>
                        </tr>
                        <tr>
                            <td colspan=2 align = "right"><span class="opt_cn">Update interval (min):</span></td>
                            <td colspan=2><select id = "updInter">
                                <option value = "2"> 2 </option>
                                <option value = "5"> 5 </option>
                                <option value = "10"> 10 </option>
                                <option value = "20"> 20 </option>
                                <option value = "30"> 30 </option>
                                <option value = "45"> 45 </option>
                                <option value = "60"> 60 </option>
                            </select>
                            </td>
                        </tr>
                    </table>  
                    <center>
                        <label class="switch"><span class="opt_cn">Display clock</span>
                            <input type="checkbox" id="onClock">
                            <span class="switch-btn"></span>
                        </label>
                    </center>                                          
                    <span class="save_booton" onclick="set_led(this);">Save</span><br><br>

                    <titles>
                        <span class="opt_cn">Setting manual temperatures</span>
                    </titles>
                      <table>
                          <tr>
                              <td align = "center"><span class="opt_cn">On/Off</span></td>
                              <td align = "center"><span class="opt_cn">Name</span></td>
                              <td align = "center"><span class="opt_cn">Temperature</span></td>
                          </tr>
                          <tr>
                              <td align = "right"><input type="checkbox" id="onAirMan"></td>
                              <td align = "right"><span class="opt_cn">Air temperature</span></td>
                              <td><input type="text" class="field" id="airManTemp" value="{{airManTemp}}" class="form-control" pattern="[\+\-]{1}[0-9.]{1,4}"></td>
                          </tr>
                          <tr>
                              <td align = "right"><input type="checkbox" id="onSeaMan"></td>
                              <td align = "right"><span class="opt_cn">Sea temperature</span></td>
                              <td><input type="text" class="field" id="seaManTemp" value="{{seaManTemp}}" class="form-control" pattern="[\+\-]{1}[0-9.]{1,4}"></td>
                          </tr>
                      </table>
                      <span class="save_booton" onclick="set_man_temp(this);">Save</span>




                    <titles>
                        <span class="opt_cn">Setting the weather</span>
                    </titles>
                    <div class="informer">
                        <span class="opt_cn">To obtain the weather forecast,
                        <a href = "http://openweathermap.org/api" align = "center" target = "_blank">here</a>  we take the API key,
                        and <a href = "https://led-lightwell.eu/city_list.txt" align = "center" target = "_blank">here</a> we find the cityID of our city.
                        </span>
                    </div>
                      <table>
                          <tr>
                              <td align = "right"><span class="opt_cn">Weather Server</span></td>
                              <td><input type="text" class="field" id="weatherHost" value="{{weatherHost}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}"></td>
                          </tr>
                          <tr>
                              <td align = "right"><span class="opt_cn">API weather key</span></td>
                              <td><input type="text" class="field" id="weatherKey" value="{{weatherKey}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}"></td>
                          </tr>
                          <tr>
                              <td align = "right"><span class="opt_cn">City (name or coord)</span></td>
                              <td><input type="text" class="field" id="cityID" value="{{cityID}}" class="form-control" pattern="[ 0-9a-zA-Zа-яА-Я._]{1,32}"></td>
                          </tr>
                      </table>
                    <div class="informer">
                        <span class="opt_cn">To obtain the Sea temperature,</span>
                        <a href = "https://worldseatemp.com/" align = "center" target = "_blank">here we take city code,</a> 
                    </div>
                      <table>
                           <tr>
                              <td align = "right"><span class="opt_cn">Sea City code</span></td>
                              <!--td><input type="text" class="field" id="seaID" value="{{seaID}}" class="form-control" pattern="[0-9]{1,10}"></td-->
                            <td><select id = "seaID">
                                <option value="55">Балчик</option>
                                <option value="57">Св. Константин и Елена</option>
                                <option value="58">Елените</option>
                                <option value="59">Святи Влас</option>
                                <option value="61">Несебър</option>
                                <option value="62">Злати песци</option>
                                <option value="63">Обзор</option
                                ><option value="66">Албена</option>
                                <option value="68">Поморие</option>
                                <option value="69">Кранево</option>
                                <option value="70">Царево</option>
                                <option value="71">Бургас</option>
                                <option value="72">Варна</option>
                                <option value="75">Слънчев бряг</option>
                                <option value="736">Созопол</option>
                                <option value="789">Приморско</option>
                                <option value="921">Резово</option>
                                <option value="922">Синеморец</option>
                                <option value="923">Черноморец</option>
                                <option value="924">Крайморие</option>
                                <option value="925">Сарафово</option>
                                <option value="926">Шкорпиловци</option>
                                <option value="927">Каварна</option>
                                <option value="928">Равда</option>
                                <option value="929">Лозенец</option>
                                <option value="930">Дюни</option>
                                <option value="931">Китен</option>
                                <option value="932">Бяла</option>
                                <option value="933">Ахтопол</option>
                            </select></td>                              
                          </tr>
                      </table>                      
                      <span class="save_booton" onclick="set_weather(this);">Save</span>

                    <table>
                        <tr>
                            <td align = "right"><span class="opt_cn">Sea {{seaTemp}} *C. Last update:</span></td>
                            <td align = "center">{{timeSendSea}}</td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Air {{airTemp}} *C. Last update:</span></td>
                            <td align = "center">{{timeSendAir}}</td>
                        </tr>
                    </table>         
                    <!--span class="save_booton" onclick="get_last_update(this);">Get last update temp</span><br><br-->
                    <span class="save_booton" onclick="sync_time(this);">Synchronization LED time from ESP</span>
                </center>
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