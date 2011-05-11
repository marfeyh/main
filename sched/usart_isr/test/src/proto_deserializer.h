
#ifndef PROTO_DESERIALIZER_H
#define PROTO_DESERIALIZER_H

#include <stdint.h>

/* array index that holds message ID */
#define ID_INDEX 1

/* navigation message array indexes */
#define NAV_TYPE_INDEX 2
#define NAV_ORDER_INDEX 3
#define NAV_HEIGHT_INDEX_LOWBYTE 4
#define NAV_HEIGHT_INDEX_HIGHBYTE 5
#define NAV_DISTANCE_INDEX_LOWBYTE 6
#define NAV_DISTANCE_INDEX_HIGHBYTE 7
#define NAV_YAW_INDEX_LOWBYTE 8
#define NAV_YAW_INDEX_HIGHBYTE 9

/* message ID for messages from navigation */
#define MSG_ID_NAV 1

uint8_t proto_reConstructMsgNav(uint8_t *data, struct navData *);

#endif /* PROTO_DESERIALIZER_H */