#ifndef __test_tpp_h_

/// This cplusplus header file is gengerated by tpp 2.0 generated.You shouldn't changed it.

/// include header files
/// system or c++ standard
#include <string>

/// tpbuff
#include <tang_tpb_command.h>

class Inner : public Command
{
public:
};
class CloseConf : public Command
{
public:
    // constructor
    CloseConf();
    // destructor
    ~CloseConf();

    // Convert object to bytes stream
    virtual bool Serialize(OutputArchive *archive);
    // Convert bytes stream to object
    virtual bool Deserialize(InputArchive *archive);

    // Return the size of the object
    int ByteSize();

    // setter/getter
    int WebConfID(){return WebConfID_;}
    void setWebConfID(int WebConfID){WebConfID_ = WebConfID;}

    // string memeber 
    std::string name(){return name_;}
    void set_name(const char *s);
    void set_name(const char *s, int len);
    void set_name(const std::string &s);
    // object memver
    inner *i(){return i_;}
    void set_allocated_i(inner *i);
private:
    int WebConfID_;
    std::string name_;
    inner *i_;
};

bool CloseConf::Serialize(OutputArchive *archive)
{
    archive->writeInt(WebConfID);
}

bool CloseConf::Deserialize(InputArchive archive)
{
    WebConfID=archive->readInt();
}

#endif//__test_tpp_h_

