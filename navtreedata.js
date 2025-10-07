/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Project Shadow Flight - A 1U Cubesat", "index.html", [
    [ "Project-Shadow-Flight", "index.html#autotoc_md0", [
      [ "Introduction", "index.html#autotoc_md1", [
        [ "Web documentation", "index.html#autotoc_md2", null ],
        [ "Design Videos for visual consumers", "index.html#autotoc_md3", null ]
      ] ],
      [ "Motivation", "index.html#autotoc_md4", null ],
      [ "Mission statement", "index.html#autotoc_md5", null ]
    ] ],
    [ "System components", "index.html#autotoc_md6", [
      [ "Onboard Computer", "index.html#autotoc_md7", [
        [ "Introduction", "index.html#autotoc_md8", null ],
        [ "Functional requirements", "index.html#autotoc_md9", null ],
        [ "Components of the OBC", "index.html#autotoc_md10", null ]
      ] ],
      [ "Sensor Board", "index.html#autotoc_md11", [
        [ "Introduction", "index.html#autotoc_md12", null ],
        [ "Functional requirements", "index.html#autotoc_md13", null ],
        [ "Communication protocol for sensors", "index.html#autotoc_md14", null ],
        [ "The PC/104 ISA Bus", "index.html#autotoc_md15", null ]
      ] ],
      [ "", "index.html#autotoc_md17", [
        [ "My Pin definition", "index.html#autotoc_md19", null ]
      ] ],
      [ "Attitude Determination and Control", "index.html#autotoc_md20", null ],
      [ "Electrical Power System (EPS)", "index.html#autotoc_md21", [
        [ "Introduction", "index.html#autotoc_md22", null ],
        [ "a) Power consumption of different bus components", "index.html#autotoc_md23", null ],
        [ "b) Power generation", "index.html#autotoc_md24", null ],
        [ "c) Energy storage", "index.html#autotoc_md25", null ],
        [ "d) Mission analysis in regards to power", "index.html#autotoc_md26", null ],
        [ "e) EPS Schematics summary", "index.html#autotoc_md27", [
          [ "Conversion", "index.html#autotoc_md28", null ],
          [ "Power Distribution Schemes", "index.html#autotoc_md29", null ],
          [ "Power supply control", "index.html#autotoc_md30", null ]
        ] ],
        [ "f) Isolated tests", "index.html#autotoc_md31", null ],
        [ "g) EPS integration and Testing", "index.html#autotoc_md32", [
          [ "Battery and solar panel sizing data", "index.html#autotoc_md33", null ]
        ] ]
      ] ]
    ] ],
    [ "Payload and Mission Design", "index.html#autotoc_md34", [
      [ "Payload PCB", "index.html#autotoc_md37", [
        [ "Payload system requirements", "index.html#autotoc_md35", null ],
        [ "Payload communication interface", "index.html#autotoc_md36", [
          [ "Tracks", "index.html#autotoc_md38", null ],
          [ "3D view", "index.html#autotoc_md39", null ]
        ] ]
      ] ]
    ] ],
    [ "Communication Protocol", "index.html#autotoc_md40", [
      [ "CCSDS Telemetry(TM) Space Data Link Protocol", "index.html#autotoc_md41", [
        [ "What is CCSDS Space Data Link Protocol", "index.html#autotoc_md42", null ],
        [ "CCSDS protocol data unit (PDU)", "index.html#autotoc_md43", null ],
        [ "Field descriptions", "index.html#autotoc_md44", null ],
        [ "How it is implemented", "index.html#autotoc_md45", null ],
        [ "Protocol data frame (PDU)", "index.html#autotoc_md46", [
          [ "Primary header", "index.html#autotoc_md48", null ],
          [ "Transfer Frame Version Number", "index.html#autotoc_md49", null ],
          [ "Spacecraft Identifier (SCID)", "index.html#autotoc_md50", null ]
        ] ],
        [ "CCSDS Transfer Frame Header – Virtual Channel, Control Flag, and Counters", "index.html#autotoc_md51", [
          [ "Virtual Channel Identifier (VCID)", "index.html#autotoc_md52", null ],
          [ "Operational Control Field Flag (OCF Flag)", "index.html#autotoc_md53", null ],
          [ "Master Channel Frame Count (MCFC)", "index.html#autotoc_md54", null ],
          [ "Virtual Channel Frame Count (VCFC)", "index.html#autotoc_md55", null ],
          [ "Transfer Frame Data Field Status (TFDFS)", "index.html#autotoc_md56", null ],
          [ "Purpose", "index.html#autotoc_md57", null ]
        ] ],
        [ "CCSDS Transfer Frame Secondary Header", "index.html#autotoc_md58", [
          [ "Overview", "index.html#autotoc_md59", null ],
          [ "Structure", "index.html#autotoc_md60", null ],
          [ "Channel Association", "index.html#autotoc_md61", null ],
          [ "Usage Rules", "index.html#autotoc_md62", null ],
          [ "Secondary header data field usage", "index.html#autotoc_md63", null ]
        ] ],
        [ "Transfer Frame Data Field", "index.html#autotoc_md64", [
          [ "Overview", "index.html#autotoc_md65", null ],
          [ "Field Length", "index.html#autotoc_md66", null ],
          [ "Field Contents", "index.html#autotoc_md67", null ],
          [ "Channel Data Rules", "index.html#autotoc_md68", null ],
          [ "Packet Placement", "index.html#autotoc_md69", null ]
        ] ],
        [ "OID (Only Idle Data) Transfer Frames", "index.html#autotoc_md71", [
          [ "OID Frame Rules", "index.html#autotoc_md72", null ],
          [ "LFSR Initialization", "index.html#autotoc_md73", null ],
          [ "VCID Association", "index.html#autotoc_md74", null ],
          [ "Notes", "index.html#autotoc_md75", null ],
          [ "Idle data", "index.html#autotoc_md76", null ]
        ] ],
        [ "Frame Error Control Field (FECF)", "index.html#autotoc_md77", [
          [ "Overview", "index.html#autotoc_md78", null ],
          [ "Encoding Procedure", "index.html#autotoc_md80", null ]
        ] ],
        [ "Interface with the ground station", "index.html#autotoc_md81", null ],
        [ "Data limits and known issues", "index.html#autotoc_md82", null ]
      ] ],
      [ "Related documents", "index.html#autotoc_md83", null ],
      [ "Relevant videos and resource materials", "index.html#autotoc_md84", null ],
      [ "Contribution and support", "index.html#autotoc_md85", null ],
      [ "Contributors", "index.html#autotoc_md86", null ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"index.html"
];

var SYNCONMSG = 'click to disable panel synchronization';
var SYNCOFFMSG = 'click to enable panel synchronization';