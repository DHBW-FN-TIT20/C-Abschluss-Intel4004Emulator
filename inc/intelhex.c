#include "intelhex.h"
#include <stdint.h>
#include <stdio.h>

const static char * const ENDHEADER = {":00000001FF"};

enum {
    COUNT_POSITION = 1,
    ADDRESS_POSITION = 3,
    TYPE_POSITION = 7,
    DATAFIELD_POSITION = 9,
    CHECKSUM_TYPE1_POSITION = 9,
    ONE_LINE = 256
};

static uint8_t readOneHexSign(const char c) {
    if((c>='0')&&(c<='9')) return c - '0';
    else if((c>='A')&&(c<='F')) return c - '7';
    else if((c>='a')&&(c<='f')) return c - 'W';
    else return 0;
}

static uint8_t readOneHexByte(const char *c) {
    return (readOneHexSign(*c)<<4)+readOneHexSign(*(c+1));
}

int readHexFile(const char *path, uint8_t *destination, int max_length) {
    if(max_length < 1) return 0;

    FILE *fd = {NULL};
    fd = fopen(path,"r");

    //Speicher fuer eine Line Code
    char line[ONE_LINE];
    //Anzahl der Speicherzellen die ausgelesen wurde
    int ret = {0};

    while(fgets(line,sizeof(line),fd)) {

        //Linie hat eine falsche Startsequenz
        if(*line != ':') return ret;

        //Addresse in einer Zeile
        int address = {0};

        //Anzahl ist der erste Wert
        uint8_t checksum = {readOneHexByte(line + COUNT_POSITION)};
        const int count = {checksum};

        {
            const uint8_t a1 = {readOneHexByte(line + ADDRESS_POSITION)},a0 = {readOneHexByte(line + ADDRESS_POSITION + 2)};
            address = ((int)(a1)) << 8 + (int)a0;
            checksum = checksum + a1 + a0;
        }

        //Type
        const uint8_t type = readOneHexByte(line + TYPE_POSITION);
        checksum += type;

        switch(type) {
        case 0: {
            //Nutzdaten 16Bit Adressen
            for(int i = 0; i < count; ++i) {
                const int8_t data = readOneHexByte(line + DATAFIELD_POSITION + i*2);
                checksum += data;

                if(ret < max_length) destination[ret++] = data;
                else return ret;

                ++address;
            }

            //Checksumme pr�fen
            const uint8_t rest = checksum + readOneHexByte(line + DATAFIELD_POSITION + count*2);
            //Checksumme falsch, beenden
            if(rest) return ret;

            break;
        }
        case 1: {
            //Endchunk
            //Checksumme pr�fen
            const uint8_t rest = checksum + readOneHexByte(line + CHECKSUM_TYPE1_POSITION);

            //Checksumme falsch, beenden
            if(rest) return ret;
            break;
        }
        default:
            fprintf(stderr,"Unbekannter Header Typ (%d)\n",type);
        }
    }

    fclose(fd);
    return ret;
}

int writeHexFile(const char *path, uint8_t *source, int startaddress, int length) {
    if(length < 1) return -1;

    FILE *fd;
    fd = fopen(path,"wb");

    int countsign = {0};
    uint8_t checksum = {0};
    for(int i = 0; i < length; ++i) {
        if(!countsign) {
            countsign = (length-i) < 16 ? (length - i) : 16;
            const int address = i + startaddress;

            checksum = ':' + (uint8_t)countsign + ((uint8_t)address)>>8 + (uint8_t)address;
            fprintf(fd,":%02X%04X00",countsign,address);
        }

        {
            const uint8_t data = source[i];
            fprintf(fd,"%02X",(int)data);
            checksum = checksum + data;
            --countsign;
        }


        if(!countsign) {
            //Aus der Checksumme eine negative Zahl machen
            checksum = ~checksum + 1;
            fprintf(fd,"%02X\n",checksum);
        }
    }

    //Endheader eintragen
    fputs(ENDHEADER,fd);
    fflush(fd);
    fclose(fd);
    return -1;
}
