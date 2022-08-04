/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.7-dev */

#ifndef PB_PROTOCOL_WHAD_PB_H_INCLUDED
#define PB_PROTOCOL_WHAD_PB_H_INCLUDED
#include <pb.h>
#include "protocol/device.pb.h"
#include "protocol/generic.pb.h"
#include "protocol/ble/ble.pb.h"
#include "protocol/zigbee/zigbee.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _Message { 
    pb_size_t which_msg;
    union {
        generic_Message generic;
        discovery_Message discovery;
        ble_Message ble;
        zigbee_Message zigbee;
    } msg;
} Message;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define Message_init_default                     {0, {generic_Message_init_default}}
#define Message_init_zero                        {0, {generic_Message_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define Message_generic_tag                      1
#define Message_discovery_tag                    2
#define Message_ble_tag                          3
#define Message_zigbee_tag                       4

/* Struct field encoding specification for nanopb */
#define Message_FIELDLIST(X, a) \
X(a, STATIC,   ONEOF,    MESSAGE,  (msg,generic,msg.generic),   1) \
X(a, STATIC,   ONEOF,    MESSAGE,  (msg,discovery,msg.discovery),   2) \
X(a, STATIC,   ONEOF,    MESSAGE,  (msg,ble,msg.ble),   3) \
X(a, STATIC,   ONEOF,    MESSAGE,  (msg,zigbee,msg.zigbee),   4)
#define Message_CALLBACK NULL
#define Message_DEFAULT NULL
#define Message_msg_generic_MSGTYPE generic_Message
#define Message_msg_discovery_MSGTYPE discovery_Message
#define Message_msg_ble_MSGTYPE ble_Message
#define Message_msg_zigbee_MSGTYPE zigbee_Message

extern const pb_msgdesc_t Message_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Message_fields &Message_msg

/* Maximum encoded size of messages (where known) */
#if defined(generic_Message_size) && defined(discovery_Message_size) && defined(ble_Message_size) && defined(zigbee_Message_size)
union Message_msg_size_union {char f1[(6 + generic_Message_size)]; char f2[(6 + discovery_Message_size)]; char f3[(6 + ble_Message_size)]; char f4[(6 + zigbee_Message_size)];};
#endif
#if defined(generic_Message_size) && defined(discovery_Message_size) && defined(ble_Message_size) && defined(zigbee_Message_size)
#define Message_size                             (0 + sizeof(union Message_msg_size_union))
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
