#ifndef _CPP_CONVERT_TPROTOCOL_H_
#define _CPP_CONVERT_TPROTOCOL_H_

#include "../transport/TTransport.h"
#include "../TException.h"
#include "../TType.h"
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace CPPConvert {
namespace CPPProtocol {

/* TProtocol */
class TProtocol {
public:
    CPPTransport::TTransport getTransport();

    /* write */
    virtual ui32 writeMessageBegin(char *funcName, TMessageType type, i32 seqid) = 0;
    virtual ui32 writeMessageEnd() = 0;

    virtual ui32 writeStructEnd() throw(CPPException::CPPTException) = 0;
    virtual ui32 writeStructBegin(const char *structName) throw(CPPException::CPPTException) = 0;

    virtual ui32 writeFieldBegin(const char *fieldName, const TType fieldType, i16 fieldId) throw(CPPException::CPPTException) = 0;
    virtual ui32 writeFieldEnd() throw(CPPException::CPPTException) = 0;
    virtual ui32 writeFieldStop() throw(CPPException::CPPTException) = 0;

    virtual ui32 writeMapBegin(const TType keyType, const TType valType, const ui32 size) throw(CPPException::CPPTException) = 0;
    virtual ui32 writeMapEnd() throw(CPPException::CPPTException) = 0;

    virtual ui32 writeListBegin(const TType elemType, const ui32 size) throw(CPPException::CPPTException) = 0;
    virtual ui32 writeListEnd() throw(CPPException::CPPTException) = 0;

    virtual ui32 writeSetBegin(const TType elemType, const ui32 size) throw(CPPException::CPPTException) = 0;
    virtual ui32 writeSetEnd() throw(CPPException::CPPTException) = 0;

    virtual ui32 writeBool(const bool value) throw(CPPException::CPPTException) = 0;

    virtual ui32 writeByte(const i8 byte) throw(CPPException::CPPTException) = 0;

    virtual ui32 writeI16(const i16 val) throw(CPPException::CPPTException) = 0;

    virtual ui32 writeI32(const i32 val) throw(CPPException::CPPTException) = 0;

    virtual ui32 writeI64(const i64 val) throw(CPPException::CPPTException) = 0;

    virtual ui32 writeDouble(const double dub) throw(CPPException::CPPTException) = 0;

    virtual ui32 writeString(const char *str, const i32 len) throw(CPPException::CPPTException) = 0;

    /**
     * read
     * 所有string &改为char **进行数据的获取与交换。
     */
    virtual ui32 readMessageBegin(char **name, TMessageType &messageType, i32 &seqid) = 0;
    virtual ui32 readMessageEnd() = 0;

    virtual ui32 readStructBegin(char **name) throw(CPPException::CPPTException) = 0;
    virtual ui32 readStructEnd() throw(CPPException::CPPTException) = 0;
    virtual ui32 readFieldBegin(char **name, TType &fieldType, i16 &fieldId) throw(CPPException::CPPTException) = 0;
    virtual ui32 readFieldEnd() throw(CPPException::CPPTException) = 0;

    virtual ui32 readMapBegin(TType &keyType, TType &fieldType, ui32 &size) throw(CPPException::CPPTException) = 0;
    virtual ui32 readMapEnd() throw(CPPException::CPPTException) = 0;

    virtual ui32 readListBegin(TType &elemType, ui32 &size) throw(CPPException::CPPTException) = 0;
    virtual ui32 readListEnd() throw(CPPException::CPPTException) = 0;

    virtual ui32 readSetBegin(TType &elemType, ui32 &size) throw(CPPException::CPPTException) = 0;
    virtual ui32 readSetEnd() throw(CPPException::CPPTException) = 0;

    virtual ui32 readBool(bool &value) throw(CPPException::CPPTException) = 0;
    //virtual ui32 readBool(std::vector<bool>::reference value) throw(CPPException::CPPTException) = 0;

    virtual ui32 readByte(i8 &byte) throw(CPPException::CPPTException) = 0;

    virtual ui32 readI16(i16 &val) throw(CPPException::CPPTException) = 0;

    virtual ui32 readI32(i32 &val) throw(CPPException::CPPTException) = 0;

    virtual ui32 readI64(i64 &val) throw(CPPException::CPPTException) = 0;

    virtual ui32 readDouble(double &dub) throw(CPPException::CPPTException) = 0;

    virtual ui32 readString(char **str) throw(CPPException::CPPTException) = 0;

    virtual ui32 readStringBody(char **str, i32 size) throw(CPPException::CPPTException) = 0;

protected:
    TProtocol(CPPTransport::TTransport &trans)
        : trans_(trans) {
        endian_ = new TNetworkBigEndian();
    }

    TProtocol(CPPTransport::TTransport &trans, NetWorkEndian *endian)
        : trans_(trans), endian_(endian) {}

    ~TProtocol();

    //TProtocol(boost::shared_ptr<CPPTransport::TTransport> ptrans_)
    //: trans_(t) {}

    //boost::shared_ptr<CPPTransport::TTransport> ptrans_;

    CPPTransport::TTransport &trans_;

    NetWorkEndian *endian_;
};
};
};

#endif
