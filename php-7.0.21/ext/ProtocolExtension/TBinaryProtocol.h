#ifndef _CPP_CONVERT_TBINARYPROTOCOL_H_
#define _CPP_CONVERT_TBINARYPROTOCOL_H_

#include "TProtocol.h"
#include "TException.h"
#include "TType.h"
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace CPPConvert {
namespace CPPProtocol {
class TBinaryProtocol: public TProtocol {

public:
    static const i32 VERSION_MASK = ((i32)0xffff0000);
    static const i32 VERSION_1 = ((i32)0x80010000);

    /**
     * 原thrift_cpp版本使用智能指针进行protocol的解析。
     * 暂时采用这种方案。
     * 从php似乎不太好变成boost::shared_ptr
     */

    //TBinaryProtocol(boost::shared_ptr<CPPTransport::TTransport> trans_)
    //:TProtocol(trans_) {}

    TBinaryProtocol(CPPTransport::TTransport &trans, bool strictRead, bool strictWrite)
        : TProtocol(trans), strictRead_(strictRead), strictWrite_(strictWrite) {}

    /* write */
    ui32 writeMessageBegin(char *funcName, TMessageType type, i32 seqid);
    ui32 writeMessageEnd();

    ui32 writeStructEnd() throw(CPPException::CPPTException);
    ui32 writeStructBegin(const char *structName) throw(CPPException::CPPTException);

    ui32 writeFieldBegin(const char *fieldName, const TType fieldType, i16 fieldId) throw(CPPException::CPPTException);
    ui32 writeFieldEnd() throw(CPPException::CPPTException);
    ui32 writeFieldStop() throw(CPPException::CPPTException);

    ui32 writeMapBegin(const TType keyType, const TType valType, const ui32 size) throw(CPPException::CPPTException);
    ui32 writeMapEnd() throw(CPPException::CPPTException);

    ui32 writeListBegin(const TType elemType, const ui32 size) throw(CPPException::CPPTException);
    ui32 writeListEnd() throw(CPPException::CPPTException);

    ui32 writeSetBegin(const TType elemType, const ui32 size) throw(CPPException::CPPTException);
    ui32 writeSetEnd() throw(CPPException::CPPTException);

    ui32 writeBool(const bool value) throw(CPPException::CPPTException);

    ui32 writeByte(const i8 byte) throw(CPPException::CPPTException);

    ui32 writeI16(const i16 val) throw(CPPException::CPPTException);

    ui32 writeI32(const i32 val) throw(CPPException::CPPTException);

    ui32 writeI64(const i64 val) throw(CPPException::CPPTException);

    ui32 writeDouble(const double dub) throw(CPPException::CPPTException);

    ui32 writeString(const char *str, const i32 len) throw(CPPException::CPPTException);

    /* read */
    ui32 readMessageBegin(char **name, TMessageType &messageType, i32 &seqid) throw(CPPException::CPPTException);
    ui32 readMessageEnd() throw(CPPException::CPPTException);

    ui32 readStructBegin(char **name) throw(CPPException::CPPTException);
    ui32 readStructEnd() throw(CPPException::CPPTException);

    ui32 readFieldBegin(char **name, TType &fieldType, i16 &fieldId) throw(CPPException::CPPTException);
    ui32 readFieldEnd() throw(CPPException::CPPTException);

    ui32 readMapBegin(TType &keyType, TType &valType, ui32 &size) throw(CPPException::CPPTException);
    ui32 readMapEnd() throw(CPPException::CPPTException);

    ui32 readListBegin(TType &elemType, ui32 &size) throw(CPPException::CPPTException);
    ui32 readListEnd() throw(CPPException::CPPTException);

    ui32 readSetBegin(TType &elemType, ui32 &size) throw(CPPException::CPPTException) = 0;
    ui32 readSetEnd() throw(CPPException::CPPTException) = 0;

    ui32 readBool(bool &value) throw(CPPException::CPPTException);
    //ui32 readBool(std::vector<bool>::reference value) throw(CPPException::CPPTException);

    ui32 readByte(i8 &byte) throw(CPPException::CPPTException);

    ui32 readI16(i16 &val) throw(CPPException::CPPTException);

    ui32 readI32(i32 &val) throw(CPPException::CPPTException);

    ui32 readI64(i64 &val) throw(CPPException::CPPTException);

    ui32 readDouble(double &dub) throw(CPPException::CPPTException);

    ui32 readString(char **str) throw(CPPException::CPPTException);

    ui32 readStringBody(char **str, i32 size) throw(CPPException::CPPTException);

protected:
    bool strictRead_ = false;
    bool strictWrite_ = true;

};
};
};

#endif
