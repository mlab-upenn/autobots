#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__

#include "mbed.h"
#include "rtos.h"
#include "string"
#include "shared.h"
#include "MRF24J40.h"

// RF tranceiver to link with handheld.
static MRF24J40 mrf(p11, p12, p13, p14, p21);

// function
void receive_command(void const *);

#endif