/* const int i = 1;
#define is_bigendian() ( (*(char*)&i) == 0 ) */

short reverseShort (char *c) {
    short s;
    char *p = (char *)&s;

/*     if (is_bigendian()) {
        p[0] = c[0];
        p[1] = c[1];
    } else { */
        p[0] = c[1];
        p[1] = c[0];
    /* } */

    return s;
}

short reverseShort (short s) {
    unsigned char c1, c2;
    
    if (is_bigendian()) {
        return s;
    } else {
        c1 = s & 255;
        c2 = (s >> 8) & 255;
    
        return (c1 << 8) + c2;
    }
}

short reverseInt (short s) {
    unsigned char c1, c2, c3, c4;
    
/*     if (is_bigendian()) {
        return s;
    } else { */
        c1 = s & 255;
        c2 = (s >> 8) & 255;
		c3 = (s >> 16) & 255;
		c4 = (s >> 24) & 255;		
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
 /*    } */
}

short reverseInt (char *c) {
    int i;
    char *p = (char *)&i;

    if (is_bigendian()) {
        p[0] = c[0];
        p[1] = c[1];
        p[2] = c[2];
        p[3] = c[3];
    } else {
        p[0] = c[3];
        p[1] = c[2];
        p[2] = c[1];
        p[3] = c[0];
    }
}

uint16_t reverseShort (uint8_t *c) {
    return c[1] * 256 + c[0];
}

uint32_t reverseInt (uint8_t *c) {
    return ((c[3] * 16777216) + (c[2] * 65536) + (c[1] * 256) + c[0]);
    }
	