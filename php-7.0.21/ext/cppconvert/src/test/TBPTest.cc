#include "../transport/TBufferdTransport.h"
#include "../protocol/TBinaryProtocol.h"
#include <iostream>
#include <string>
#include <time.h>
#define LOOP 10000000

using namespace CPPConvert;


int main() {
    CPPTransport::TBufferdTransport transport(1024);
    CPPProtocol::TBinaryProtocol protocol(transport, true, true);

    /* 分别进行Write bool, byte, i16, i32, i64, string的测试 */

    clock_t ss, se;

    ss = clock();
    for (int i = 0; i < LOOP; i++) {
        protocol.writeBool(false);
    }
    se = clock();
    printf("time: %.9lf\n", (double)(se - ss) / CLOCKS_PER_SEC);
    ss = se;

    for (int i = 0; i < LOOP; i++) {
        protocol.writeByte('a');
    }
    se = clock();
    printf("time: %.9lf\n", (double)(se - ss) / CLOCKS_PER_SEC);
    ss = se;

    for (int i = 0; i < LOOP; i++) {
        protocol.writeI16((short)12);
    }
    se = clock();
    printf("time: %.9lf\n", (double)(se - ss) / CLOCKS_PER_SEC);
    ss = se;

    for (int i = 0; i < LOOP; i++) {
        protocol.writeI32(12);
    }
    se = clock();
    printf("time: %.9lf\n", (double)(se - ss) / CLOCKS_PER_SEC);
    ss = se;

    for (int i = 0; i < LOOP; i++) {
        protocol.writeI64((long)23154812394);
    }
    se = clock();
    printf("time: %.9lf\n", (double)(se - ss) / CLOCKS_PER_SEC);
    ss = se;

    for (int i = 0; i < LOOP; i++) {
        protocol.writeDouble(312341.2334);
    }
    se = clock();
    printf("time: %.9lf\n", (double)(se - ss) / CLOCKS_PER_SEC);
    ss = se;

    char str[] = "transport input input";

    for (int i = 0; i < LOOP; i++) {
        protocol.writeString(&str[0], strlen(str));
    }
    se = clock();
    printf("time: %.9lf\n", (double)(se - ss) / CLOCKS_PER_SEC);
    ss = se;

    //B b;
    //std::cout << b.getVal() << std::endl;
    //std::cout << b.getString() << std::endl;


    //for(int i = 0; i < 10000; i++) {
    //transport.write((const ui8 *)&str[0], strlen(str));
    //}

    //bool b_val = true;
    //i8 by_val = 0;
    //i16 i16_val = 0;
    //i32 i32_val = 0;
    //i64 i64_val = 0;
    //double dub = 0;
    //char * str_p = 0; //protocol.readBool(b_val);
    //protocol.readByte(by_val);
    //protocol.readI16(i16_val);
    //protocol.readI32(i32_val);
    //protocol.readI64(i64_val);
    //protocol.readDouble(dub);
    //protocol.readString(&str_p);

    //printf("bool: %d, byte: %c, i16: %d, i32: %d, i64: %lld, double: %lf, string: %s\n", \
    //b_val, by_val, i16_val, i32_val, i64_val, dub, str_p);

    return 0;
}
