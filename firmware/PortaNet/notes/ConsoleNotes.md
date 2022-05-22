# ***CONSOLE NOTES***
***

## *INTERFACE*
`TaskConsole`

- interface to the task
<br><br/>

***

## *CONTROLLER*
`ConsoleController`

- handles the console processes to execute
<br><br/>

`RegisterAllCommands`

- registers all wanted commands
<br><br/>

`CmdReset`

- command function to request a reset of the wifi access point to its defualt credentials 
<br><br/>

`RegisterReset`

- register the reset command
<br><br/>

`CmdRestart`

- command function to request a restart of the wifi access point
<br><br/>

`RegisterRestart`

- register the restart command
<br><br/>

`CmdOn`

- command function to request the wifi access point on
<br><br/>

`RegisterOn`

- register the on command
<br><br/>

`CmdOff`

- command function to request the wifi access point off
<br><br/>

`RegisterOff`

- register the off command
<br><br/>

`CmdStatus`

- command function to request the status of the wifi access point. The status info should include the network name, the network password, the max number of connected devices allowed, and the current wifi channel.
<br><br/>

`RegisterStatus`

- register the status command
<br><br/>

`CmdDevices`

- command function to show the info of the currently connected stations/devices
<br><br/>

`RegisterDevices`

- register the devices command
<br><br/>

`CmdSsid`

- command function to request a change to the wifi access point's SSID and restart the wifi access point
- input arg of string
<br><br/>

`RegisterSsid`

- register the SSID command
<br><br/>

`CmdPassword`

- command function to request a change to the wifi access point's password and restart the wifi access point
- input arg of string
<br><br/>


`RegisterPassword`

- register the password command
<br><br/>

`CmdMaxConn`

- command function to request a change to the wifi access point's max number of connections and restart the wifi access point
- input arg of int
<br><br/>

`RegisterMaxConn`

- register the maxconn command
<br><br/>

***

## *CONSOLE DRIVER*
`InitConsole`

- initialises the console, should only need to be called once
<br><br/>

`ProcessConsole`

- continuous console function to process console changes
<br><br/>

`AddConsoleCommand`

- add/register console command
<br><br/>

***

## *COMMANDS*
`reset`

- resets the wifi access point with the defualt credentials
<br><br/>

`restart`

- restart the wifi access point 
<br><br/>

`on`

- turn on the wifi access point
<br><br/>

`off`

- turn off the wifi access point
<br><br/>

`status`

- show the status of the network if it running. The status info should include the network name, the network password, the max number of connected devices allowed, and the current wifi channel.
<br><br/>

`devices`

- shows the currently connected devices
<br><br/>

`ssid <newssid>`

- change the ssid name and restart the wifi access point
<br><br/>

`password <password>`

- change the password and restart the wifi access point
<br><br/>

`maxconn <connections>`

- change the number of max device connections and restart the wifi access point 
<br><br/>

