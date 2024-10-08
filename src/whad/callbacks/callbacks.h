#ifndef PBCALLBACKS_H
#define PBCALLBACKS_H
#include "stddef.h"
#include "stdbool.h"
#include <whad.h>
#include "capabilities.h"

bool whad_verbose_msg_encode_cb_(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg);
bool whad_disc_enum_capabilities_cb_(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg);
bool whad_phy_frequency_range_encode_cb_(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg);
#endif
