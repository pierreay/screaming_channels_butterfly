#ifndef WHAD_H
#define WHAD_H

#include <stdlib.h>
#include "nrf.h"
#include "whad/callbacks/callbacks.h"
#include "version.h"
#include "capabilities.h"
#include "packet.h"

class Whad {

  public:
    static bool isDomainSupported(whad_domain_t domain);
    static uint64_t getSupportedCommandByDomain(whad_domain_t domain);

    static Message decodeMessage(uint8_t *buffer, size_t size);
    static size_t encodeMessage(Message* msg, uint8_t* buffer, size_t maxSize);

    static Message* buildMessage();

    // Generic messages builders
    static Message* buildResultMessage(generic_ResultCode code);
    static Message* buildVerboseMessage(const char* data);
    static Message* buildDiscoveryDeviceInfoMessage();
    static Message* buildDiscoveryReadyResponseMessage();
    static Message* buildDiscoveryDomainInfoMessage(whad_domain_t domain);

    static Message* buildMessageFromPacket(Packet* packet);
    static Message* buildESBRawPduMessage(ESBPacket* packet);
    static Message* buildDot15d4EnergyDetectionSampleMessage(uint32_t sample, uint32_t timestamp);
    static Message* buildDot15d4RawPduMessage(Dot15d4Packet* packet);
    static Message* buildBLERawPduMessage(BLEPacket* packet);
    static Message* buildPhyPacketMessage(GenericPacket* packet);
    static Message* buildPhySupportedFrequencyRangeMessage();
    static Message* buildBLESynchronizedMessage(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, uint8_t *channelMap);
    static Message* buildBLEDesynchronizedMessage(uint32_t accessAddress);
    static Message* buildBLEInjectedMessage(bool success, uint32_t injectionAttempts, uint32_t accessAddress);
    static Message* buildBLEHijackedMessage(bool success, uint32_t accessAddress);
    static Message* buildBLETriggeredMessage(uint8_t identifier);
    static Message* buildBLEAccessAddressDiscoveredMessage(uint32_t accessAddress, uint32_t timestamp, int32_t rssi);
    static Message* buildBLEConnectedMessage(uint8_t *initiator, bool initiatorRandom, uint8_t *advertiser, bool advertiserRandom, uint32_t accessAddress, int connectionHandle);
    static Message* buildBLEDisconnectedMessage(uint32_t reason);

};

#endif
