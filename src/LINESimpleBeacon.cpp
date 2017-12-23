// Copyright (c) Pizayanz. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "LINESimpleBeacon.h"

#define UUID_FOR_LINECORP "fe6f"

  // {0x02, 
  //  0x00, 0x00, 0x00, 0x00, 0x00,  // LINE HWID
  //  0x7f, 
  //  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // LINE Device Message

LINESimpleBeacon::LINESimpleBeacon(const unsigned char* hwid) :
  BLEPeripheral(),
  _bleService(UUID_FOR_LINECORP),
  _bleCharacteristic(UUID_FOR_LINECORP, BLEBroadcast, MAX_SERVICE_DATA_SIZE)
{
  memcpy(this->_hwid, hwid, 5);
  this->setConnectable(false);

  this->addAttribute(this->_bleService);
  // https://github.com/line/line-simple-beacon
  // こちら Advertising data の Byte Offset 4 (5バイト目)
  //  0x02: Complete list of 16-bit UUIDs available
  //  0x03: Incomplete list of 16-bit UUIDs available
  // を 0x03 にすべきだが、ライブラリ内
  // https://github.com/sandeepmistry/arduino-BLEPeripheral/blob/f591da1a841bf6b0a5c1eac4d1255ba6e71154e8/src/BLEPeripheral.cpp#L97
  // BLEPeripheral.cpp 
  //   advertisementData[advertisementDataSize].type = (uuidLength > 2) ? 0x06 : 0x02;
  // にて、0x02 がセットされてしまう。
  // 0x02 でも、問題なく LINE App が反応して動くので、そのままにしておく。

  this->addAttribute(this->_bleCharacteristic);

  this->_serviceData[0] = 0x02;
  for (int i = 0; i < 5; i++) {
    this->_serviceData[i + 1] = this->_hwid[i];
  }
  this->_serviceData[6] = 0x7f;
  for (int i = 0; i < MAX_DEVICE_MESSAGE_SIZE; i++) {
    this->_serviceData[i + 7] = 0x00;
  }

}

void LINESimpleBeacon::begin() {
  this->setAdvertisedServiceUuid(this->_bleService.uuid());
  BLEPeripheral::begin();
  this->_bleCharacteristic.broadcast();
}

void LINESimpleBeacon::begin(const char* deviceMessage) {
  this->setDeviceMessage(deviceMessage);
  this->begin();
}

void LINESimpleBeacon::setDeviceMessage(const char* deviceMessage) {
  int dmsize = min(strlen(deviceMessage), MAX_DEVICE_MESSAGE_SIZE);

  for (int i = 0; i < dmsize; i++) {
    this->_serviceData[i + 7] = deviceMessage[i];
  }
  for (int i = dmsize; i < MAX_DEVICE_MESSAGE_SIZE; i++) {
    this->_serviceData[i + 7] = 0x00;
  }

  this->_bleCharacteristic.setValue(this->_serviceData, dmsize + 7);
}

void LINESimpleBeacon::loop() {
  this->poll();
}
