#include "TBinaryProtocol.h"
#include <boost/static_assert.hpp>
#include "TFunc.h"

namespace CPPConvert {
namespace CPPProtocol {

ui32 TBinaryProtocol::writeMessageBegin(char *funcName, TMessageType type, i32 seqid) {
    //if (this->strictWrite_) {
    //i32 version = this->VERSION_1 | (int)type;

    //return this->writeI32(version) + this->writeString(funcName) + this->writeI32(seqid);
    //} else {
    //return this->writeString(funcName) + this->writeByte((i8)type) + this->writeI32(seqid);
    //}
    return 0;
}

ui32 TBinaryProtocol::writeMessageEnd() {
    return 0;
}

ui32 TBinaryProtocol::writeStructBegin(const char *structName) throw(CPPException::CPPTException) {
    (void)structName;
    return 0;
}

ui32 TBinaryProtocol::writeStructEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::writeFieldBegin(const char *fieldName, const TType fieldType, i16 fieldId) throw(CPPException::CPPTException) {
    (void)fieldName;
    return this->writeByte((i8)fieldType) + this->writeI16(fieldId);
}

ui32 TBinaryProtocol::writeFieldEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::writeFieldStop() throw(CPPException::CPPTException) {
    return this->writeByte((i8)T_STOP);
}

ui32 TBinaryProtocol::writeMapBegin(const TType keyType, const TType valType, const ui32 size) throw(CPPException::CPPTException) {
    return this->writeByte((i8)keyType) + this->writeByte((i8)valType) + this->writeI32(size);
}

ui32 TBinaryProtocol::writeMapEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::writeListBegin(const TType elemType, const ui32 size) throw(CPPException::CPPTException) {
    return this->writeByte((i8)elemType) + this->writeI32(size);
}

ui32 TBinaryProtocol::writeListEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::writeSetBegin(const TType elemType, const ui32 size) throw(CPPException::CPPTException) {
    return this->writeByte((i8)elemType) + this->writeI32(size);
}

ui32 TBinaryProtocol::writeSetEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::writeBool(const bool value) throw(CPPException::CPPTException) {
    ui8 tmp = value ? 1 : 0;
    this->trans_.write(&tmp, 1);
    return 1;
}

ui32 TBinaryProtocol::writeByte(const i8 byte) throw(CPPException::CPPTException) {
    this->trans_.write((ui8 *)&byte, 1);
    return 1;
}

ui32 TBinaryProtocol::writeI16(const i16 val) throw(CPPException::CPPTException) {
    i16 net = (i16)this->endian_.toWire16(val);
    this->trans_.write((ui8 *)&net, 2);
    return 2;
}

ui32 TBinaryProtocol::writeI32(const i32 val) throw(CPPException::CPPTException) {
    i32 net = (i32)this->endian_.toWire32(val);
    this->trans_.write((ui8 *)&net, 4);
    return 4;
}

ui32 TBinaryProtocol::writeI64(const i64 val) throw(CPPException::CPPTException) {
    i64 net = (i64)this->endian_.toWire64(val);
    this->trans_.write((ui8 *)&net, 8);
    return 8;
}

ui32 TBinaryProtocol::writeDouble(const double dub) throw(CPPException::CPPTException) {
    /* double是否为指定数据类型*/
    BOOST_STATIC_ASSERT(sizeof(double) == sizeof(uint64_t));
    BOOST_STATIC_ASSERT(std::numeric_limits<double>::is_iec559);

    ui64 net = bitwise_cast<double, ui64>(dub);
    net = this->endian_.toWire64(net);
    this->trans_.write((ui8 *)&net, 8);
}

ui32 TBinaryProtocol::writeString(const char *str, const i32 len) throw(CPPException::CPPTException) {
    if (len > std::numeric_limits<i32>::max()) {
        throw new CPPException::CPPTException();
    }

    ui32 size = (ui32)len;
    ui32 res = this->writeI32(size);
    if (size > 0) {
        this->trans_.write((ui8 *)str, size);
    }
    return res + size;
}

/**
 * message read module
 */

ui32 TBinaryProtocol::readMessageBegin(char **name, TMessageType &messageType, i32 &seqid) throw(CPPException::CPPTException) {
    ui32 result = 0;
    i32 sz;
    result += readI32(sz);
    if (sz < 0) {
        i32 version = sz & VERSION_MASK;
        if (version != VERSION_1) {
            throw CPPException::CPPTException();
        }
        messageType = (TMessageType)(sz & 0x000000ff);
        result += this->readString(name);
        result += this->readI32(seqid);
    } else {
        i8 type;
        if (this->strictRead_) {
            throw CPPException::CPPTException();
        } else {
            i8 type;
            result += this->readStringBody(name, sz);
            result += this->readByte(type);
            messageType = (TMessageType)type;
            result += this->readI32(seqid);
        }
    }
    return result;
}

ui32 TBinaryProtocol::readMessageEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::readStructBegin(char **name) throw(CPPException::CPPTException) {
    /**
     * null_str is define in TType.h
     */
    *name = &none_str[0];
    return 0;
}

ui32 TBinaryProtocol::readStructEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::readFieldBegin(char **name, TType &fieldType, i16 &fieldId) throw(CPPException::CPPTException) {
    (void)name;
    ui32 result = 0;
    i8 type;
    result += this->readByte(type);
    fieldType = (TType)type;

    if (fieldType == T_STOP) {
        fieldId = 0;
        return result;
    }

    result += this->readI16(fieldId);
    return result;
}

ui32 TBinaryProtocol::readFieldEnd() throw (CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::readMapBegin(TType &keyType, TType &valType, ui32 &size) throw(CPPException::CPPTException) {
    i8 k, v;
    i32 sizei;
    ui32 result = 0;
    result += this->readByte(k);
    keyType = (TType)k;
    result += this->readByte(v);
    valType = (TType)v;
    result += this->readI32(sizei);
    size = (ui32)sizei;
    return result;
}

ui32 TBinaryProtocol::readMapEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::readListBegin(TType &elemType, ui32 &size) throw(CPPException::CPPTException) {
    i8 et;
    i32 sizei;

    ui32 result = 0;
    result += this->readByte(et);
    elemType = (TType)et;
    result += this->readI32(sizei);
    size =  (ui32)sizei;
    return result;
}

ui32 TBinaryProtocol::readListEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::readSetBegin(TType &elemType, ui32 &size) throw(CPPException::CPPTException) {
    i8 et;
    i32 sizei;

    ui32 result = 0;
    result += this->readByte(et);
    elemType = (TType)et;
    result += this->readI32(sizei);
    size =  (ui32)sizei;
    return result;
}

ui32 TBinaryProtocol::readSetEnd() throw(CPPException::CPPTException) {
    return 0;
}

ui32 TBinaryProtocol::readBool(bool &value) throw(CPPException::CPPTException) {
    ui8 b[1];
    this->trans_.readAll(b, 1);
    value = *(i8 *)b != 0;
    return 1;
}

ui32 TBinaryProtocol::readByte(i8 &byte) throw(CPPException::CPPTException) {
    ui8 b[1];
    this->trans_.readAll(b, 1);
    byte = *(i8 *)b;
    return 1;
}

ui32 TBinaryProtocol::readI16(i16 &val) throw(CPPException::CPPTException) {
    /* 奇技淫巧 */
    b2i16 b_trans;
    this->trans_.readAll(b_trans.b, 2);
    val = (i16)this->endian_.fromWire16(b_trans.val);

    return 2;
}

ui32 TBinaryProtocol::readI32(i32 &val) throw(CPPException::CPPTException) {
    b2i32 b_trans;
    this->trans_.readAll(b_trans.b, 4);
    val = (i32)this->endian_.fromWire32(b_trans.val);
    return 4;
}

ui32 TBinaryProtocol::readI64(i64 &val) throw(CPPException::CPPTException) {
    b2i64 b_trans;
    this->trans_.readAll(b_trans.b, 8);
    val = (i64)this->endian_.fromWire64(b_trans.val);
    return 8;
}

ui32 TBinaryProtocol::readDouble(double &dub) throw(CPPException::CPPTException) {
    BOOST_STATIC_ASSERT(sizeof(double) == sizeof(ui64));
    BOOST_STATIC_ASSERT(std::numeric_limits<double>::is_iec559);

    b2dub b_trans;
    this->trans_.readAll(b_trans.b, 8);
    b_trans.val = this->endian_.fromWire64(b_trans.val);
    dub = bitwise_cast<ui64, double>(b_trans.val);
    return 8;
}

ui32 TBinaryProtocol::readString(char **str) throw(CPPException::CPPTException) {
    ui32 result;
    i32 size;
    result = this->readI32(size);
    return result + this->readStringBody(str, size);
}

ui32 TBinaryProtocol::readStringBody(char **str, i32 size) throw(CPPException::CPPTException) {
    ui32 result = 0;

    if (size < 0) {
        throw CPPException::CPPTException();
    }

    if (size == 0) {
        *str = &none_str[0];
    }

    /* 原CPP实现 */
    const ui8* borrow_buf;
    ui32 got = size;
    if((borrow_buf = this->trans_.borrow(NULL, &got))) {
        *str = (char *)borrow_buf;
        this->trans_.consume(got);
        return size;
    }

    /**
     * 需要在Protocol外free
     * 如果使用zend_string_init()则要在init后free
     * 如果直接赋值给zend_string可以不需要free
     */
    ui8 *tmp_str = (ui8 *)malloc(size);

    *str = (char *)tmp_str;

    this->trans_.readAll(tmp_str, size);
    return (ui32)size;
}

};
};
