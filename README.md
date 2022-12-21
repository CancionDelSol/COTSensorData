Directory Structure:
  AsyncTCP                : Arduino library for asynchronous usage of TCP 
  BLEClient               : ESP32 module BLE client implementation
  BLEServer               : ESP32 module BLE server implementation
  BTClient                : ESP32 module Bluetooth client implementation
  BTServer                : ESP32 module Bluetooth server implementation
  COTProject              : Custom Arduino library
  Clicker                 : 6LoWPAN implementation for NECTO Studio's IDE
  ESPAsyncWebServer       : Arduino library for asynchronous web server
  UARTBridge              : ESP32 module UART bridge
  WifiClient              : ESP32 module wifi client implementation
  WifiServer              : ESP32 module wifi server implementation
  data/configFileDefaults : Default config files for java program
  lib                     : JAR libraries
  reports                 : Output reports
  src                     : Java source code
  
  ############## Main Program #######################
  The java software is designed to run on a linux operating system
  and was tested on the Raspberry Pi 4. The main program runs an
  experimental session using settings in the configuration files.
  
  Compile from parent directory using make. Here are the targets and
  their descriptions:
  
    start            : Build the main java executable and run a session
    deconfig         : Remove all configuration files
    config           : Copy default config files into runtime directory
    clearData        : Remove all csv files under the reports folder
    prepEnv          : Copy the custom arduino library into Arduino's library directory
    serialMonitor    : Connect to a serial port and print out the output
    serialMessenger  : Start a messaging session with the serial port
    clean            : Clean all binaries, class files, manifest and intermediate build outputs
    
