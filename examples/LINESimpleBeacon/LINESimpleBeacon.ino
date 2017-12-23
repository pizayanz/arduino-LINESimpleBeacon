// Copyright (c) Pizayanz. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <LINESimpleBeacon.h>

// https://admin-official.line.me/beacon/register#/
// LINEから払い出されたhw idを2桁区切りにして0x__の部分に入れる
unsigned char hwid[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

LINESimpleBeacon lineSimpleBeacon = LINESimpleBeacon(hwid);

void setup() {
  Serial.begin(9600);

  // deviceMessage は 13文字まで
  lineSimpleBeacon.begin("foobarbaz");

  Serial.println(F("Line Simple Beacon"));
}

void loop() {
  lineSimpleBeacon.loop();
}