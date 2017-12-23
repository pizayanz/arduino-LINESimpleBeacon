// Copyright (c) Pizayanz. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef _LINE_SIMPLE_BEACON_H_
#define _LINE_SIMPLE_BEACON_H_

#include "BLEPeripheral.h"
#include "BLEUuid.h"

#define MAX_SERVICE_DATA_SIZE 20
#define MAX_DEVICE_MESSAGE_SIZE 13

class LINESimpleBeacon : public BLEPeripheral
{
  public:
    LINESimpleBeacon(const unsigned char* hwid);

    void begin();
    void begin(const char* deviceMessage);
    void setDeviceMessage(const char* deviceMessage);
    void loop();

  private:
    unsigned char     _serviceData[MAX_SERVICE_DATA_SIZE] = {};
    unsigned char     _hwid[5] = {};
    BLEService        _bleService;
    BLECharacteristic _bleCharacteristic;
};

#endif
