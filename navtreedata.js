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
  [ "Project Shadow Flight - A 1U amateur Cubesat", "index.html", [
    [ "System components", "index.html#autotoc_md5", [
      [ "Introduction", "index.html#autotoc_md0", [
        [ "Web documentation", "index.html#autotoc_md1", null ],
        [ "Design Videos for visual consumers", "index.html#autotoc_md2", null ]
      ] ],
      [ "Motivation", "index.html#autotoc_md3", null ],
      [ "Mission statement", "index.html#autotoc_md4", null ],
      [ "Onboard Computer", "index.html#autotoc_md6", [
        [ "Introduction", "index.html#autotoc_md7", null ],
        [ "Functional requirements", "index.html#autotoc_md8", null ],
        [ "Components of the OBC", "index.html#autotoc_md9", null ]
      ] ],
      [ "Sensor Board", "index.html#autotoc_md10", [
        [ "Introduction", "index.html#autotoc_md11", null ],
        [ "Functional requirements", "index.html#autotoc_md12", null ],
        [ "Communication protocol for sensors", "index.html#autotoc_md13", null ],
        [ "The PC/104 ISA Bus", "index.html#autotoc_md14", null ]
      ] ],
      [ "", "index.html#autotoc_md16", [
        [ "My Pin definition", "index.html#autotoc_md18", null ]
      ] ],
      [ "Attitude Determination and Control", "index.html#autotoc_md19", null ],
      [ "Electrical Power System (EPS)", "index.html#autotoc_md20", [
        [ "Introduction", "index.html#autotoc_md21", null ],
        [ "a) Power consumption of different bus components", "index.html#autotoc_md22", null ],
        [ "b) Power generation", "index.html#autotoc_md23", null ],
        [ "c) Energy storage", "index.html#autotoc_md24", null ],
        [ "d) Mission analysis in regards to power", "index.html#autotoc_md25", null ],
        [ "e) EPS Schematics summary", "index.html#autotoc_md26", [
          [ "Conversion", "index.html#autotoc_md27", null ],
          [ "Power Distribution Schemes", "index.html#autotoc_md28", null ],
          [ "Power supply control", "index.html#autotoc_md29", null ]
        ] ],
        [ "f) Isolated tests", "index.html#autotoc_md30", null ],
        [ "g) EPS integration and Testing", "index.html#autotoc_md31", [
          [ "Battery and solar panel sizing data", "index.html#autotoc_md32", null ]
        ] ]
      ] ]
    ] ],
    [ "Payload and Mission Design", "index.html#autotoc_md33", [
      [ "Payload PCB", "index.html#autotoc_md36", [
        [ "Payload system requirements", "index.html#autotoc_md34", null ],
        [ "Payload communication interface", "index.html#autotoc_md35", [
          [ "Tracks", "index.html#autotoc_md37", null ],
          [ "3D view", "index.html#autotoc_md38", null ]
        ] ]
      ] ]
    ] ],
    [ "Communication Protocol", "index.html#autotoc_md39", [
      [ "CCSDS Telemetry(TM) Space Data Link Protocol", "index.html#autotoc_md40", [
        [ "What is CCSDS Space Data Link Protocol", "index.html#autotoc_md41", null ],
        [ "CCSDS protocol data unit (PDU)", "index.html#autotoc_md42", null ],
        [ "Field descriptions", "index.html#autotoc_md43", null ],
        [ "How it is implemented", "index.html#autotoc_md44", null ],
        [ "Protocol data frame (PDU)", "index.html#autotoc_md45", [
          [ "Primary header", "index.html#autotoc_md47", null ],
          [ "Transfer Frame Version Number", "index.html#autotoc_md48", null ],
          [ "Spacecraft Identifier (SCID)", "index.html#autotoc_md49", null ]
        ] ],
        [ "CCSDS Transfer Frame Header – Virtual Channel, Control Flag, and Counters", "index.html#autotoc_md50", [
          [ "Virtual Channel Identifier (VCID)", "index.html#autotoc_md51", null ],
          [ "Operational Control Field Flag (OCF Flag)", "index.html#autotoc_md52", null ],
          [ "Master Channel Frame Count (MCFC)", "index.html#autotoc_md53", null ],
          [ "Virtual Channel Frame Count (VCFC)", "index.html#autotoc_md54", null ],
          [ "Transfer Frame Data Field Status (TFDFS)", "index.html#autotoc_md55", null ],
          [ "Purpose", "index.html#autotoc_md56", null ]
        ] ],
        [ "CCSDS Transfer Frame Secondary Header", "index.html#autotoc_md57", [
          [ "Overview", "index.html#autotoc_md58", null ],
          [ "Structure", "index.html#autotoc_md59", null ],
          [ "Channel Association", "index.html#autotoc_md60", null ],
          [ "Usage Rules", "index.html#autotoc_md61", null ],
          [ "Secondary header data field usage", "index.html#autotoc_md62", null ]
        ] ],
        [ "Transfer Frame Data Field", "index.html#autotoc_md63", [
          [ "Overview", "index.html#autotoc_md64", null ],
          [ "Field Length", "index.html#autotoc_md65", null ],
          [ "Field Contents", "index.html#autotoc_md66", null ],
          [ "Channel Data Rules", "index.html#autotoc_md67", null ],
          [ "Packet Placement", "index.html#autotoc_md68", null ]
        ] ],
        [ "OID (Only Idle Data) Transfer Frames", "index.html#autotoc_md70", [
          [ "OID Frame Rules", "index.html#autotoc_md71", null ],
          [ "LFSR Initialization", "index.html#autotoc_md72", null ],
          [ "VCID Association", "index.html#autotoc_md73", null ],
          [ "Notes", "index.html#autotoc_md74", null ],
          [ "Idle data", "index.html#autotoc_md75", null ]
        ] ],
        [ "Frame Error Control Field (FECF)", "index.html#autotoc_md76", [
          [ "Overview", "index.html#autotoc_md77", null ],
          [ "Encoding Procedure", "index.html#autotoc_md79", null ]
        ] ],
        [ "Interface with the ground station", "index.html#autotoc_md80", null ],
        [ "Data limits and known issues", "index.html#autotoc_md81", null ]
      ] ],
      [ "Related documents", "index.html#autotoc_md82", null ],
      [ "Relevant videos and resource materials", "index.html#autotoc_md83", null ],
      [ "Contribution and support", "index.html#autotoc_md84", null ],
      [ "Contributors", "index.html#autotoc_md85", null ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"index.html"
];

var SYNCONMSG = 'click to disable panel synchronization';
var SYNCOFFMSG = 'click to enable panel synchronization';