#include <stdio.h>
#include "tp_cxx_generator.h"
#include "tp_symbol_list.h"

static int tp_gen_cxx_getter_setter(FILE *out, struct item_node *n)
{
    struct item_node *in = n;

    fprintf(out, "\n  // getter/setter\n");
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  uint8_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(uint8_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  int8_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(int8_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  uint8_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(uint8_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  int16_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(int16_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  uint16_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(uint16_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  int32_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(int32_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  uint32_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(uint32_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  int64_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(int64_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  uint64_t %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(uint64_t i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  int %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(int i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  long %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(long l){%s_=l;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  short %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(short i){%s_=i;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  char %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(char c){%s_=c;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  double %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(double d){%s_=d;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  float %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(float f){%s_=f;}\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  std::string %s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(std::string s){%s_=s;}\n", in->name, in->name);
        }
    }

    return 0;
}
static int tp_gen_cxx_data_member(FILE *out, struct item_node *n)
{
    fprintf(out, "\nprivate:\n");

    struct item_node *in = n;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  uint8_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            fprintf(out, "  std::vector<uint8_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  int8_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            fprintf(out, "  std::vector<int8_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  uint8_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            fprintf(out, "  std::vector<uint8_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  int16_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            fprintf(out, "  std::vector<int16_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  uint16_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            fprintf(out, "  std::vector<uint16_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  int32_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            fprintf(out, "  std::vector<int32_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  uint32_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            fprintf(out, "  std::vector<uint32_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  int64_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            fprintf(out, "  std::vector<int64_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  uint64_t %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            fprintf(out, "  std::vector<uint64_t> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  std::string %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_STR_VEC){
            fprintf(out, "  std::vector<std::string> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  int %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT_VEC){
            fprintf(out, "  std::vector<int> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  long %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_LONG_VEC){
            fprintf(out, "  std::vector<long> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  short %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            fprintf(out, "  std::vector<short> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  char %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            fprintf(out, "  std::vector<char> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  double %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            fprintf(out, "  std::vector<double> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  float %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            fprintf(out, "  std::vector<float> %s_vec_;\n", in->name);
        }
    }
}
static int tp_gen_cxx_proto_decl(FILE *out, struct protocol *p)
{
    //Generate class header
    fprintf(out, "class %s : public Command {\npublic:\n ", p->name);
    fprintf(out, "  // constructor\n");
    fprintf(out, "  %s();\n", p->name);
    fprintf(out, "  // destructor\n");
    fprintf(out, "  ~%s();\n", p->name);
    fprintf(out, "  // Convert object to bytes stream\n");
    fprintf(out, "  virtual bool Serialize(OutputArchive *oa);\n");
    fprintf(out, "  // Convert bytes stream to object\n");
    fprintf(out, "  virtual bool Deserialize(InputArchive *ia);\n");
    fprintf(out, "  // Return the size of the object\n");
    fprintf(out, "  virtual int ByteSize();\n");
    tp_gen_cxx_getter_setter(out, p->head);
    tp_gen_cxx_data_member(out, p->head);
    fprintf(out, "};\n\n");

    return 0;
}

static int tp_gen_cxx_proto_impl_ctor(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    fprintf(out, "%s::%s(struct tp_buff *tpb):Command(tpb)\n{\n", p->name, p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE
                || in->val_type == VALUE_TYPE_INT8
                || in->val_type == VALUE_TYPE_UINT8
                || in->val_type == VALUE_TYPE_INT16
                || in->val_type == VALUE_TYPE_UINT16
                || in->val_type == VALUE_TYPE_INT32
                || in->val_type == VALUE_TYPE_UINT32
                || in->val_type == VALUE_TYPE_INT64
                || in->val_type == VALUE_TYPE_UINT64
                || in->val_type == VALUE_TYPE_LONG
                || in->val_type == VALUE_TYPE_INT
                || in->val_type == VALUE_TYPE_SHORT
                || in->val_type == VALUE_TYPE_CHAR
                || in->val_type == VALUE_TYPE_DOUBLE
                || in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  %s_ = 0;\n", in->name); 
        }
    }
    fprintf(out, "}\n");
}

#define tp_gen_cxx_proto_impl_serialize_vec(type) \
    do{\
        fprintf(out, "\n  // Write size firstly\n");\
        fprintf(out, "  int %s_size = %s_vec_.size();\n", in->name, in->name);\
        fprintf(out, "  oa->writeInt(tpb, %s_size);\n", in->name);\
        fprintf(out, "  // Write element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %s_size; i++){\n", in->name);\
        fprintf(out, "    oa->write" #type "(tpb, %s_vec_[i]);\n", in->name);\
        fprintf(out, "  }\n\n");\
    } while(0);

#define tp_gen_cxx_proto_impl_deserialize_vec(type) \
    do{\
        fprintf(out, "\n  // Write size firstly\n");\
        fprintf(out, "  int %s_size = oa->readInt(tpb);\n", in->name);\
        fprintf(out, "  // Write element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %s_size; i++){\n", in->name);\
        fprintf(out, "    %s_vec_[i] = oa->read" #type "(tpb);\n", in->name);\
        fprintf(out, "  }\n\n");\
    } while(0);


     
static int tp_gen_cxx_proto_impl_serialize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "%s::Serialize(OutputArchive *oa)\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  oa->writeUInt8(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt8);
        }else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  oa->writeInt8(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int8);
        }else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  oa->writeUInt8(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt8);
        }else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  oa->writeInt16(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int16);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  oa->writeUInt16(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt16);
        }else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  oa->writeInt32(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int32);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  oa->writeUInt32(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt32);
        }else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  oa->writeInt64(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int64);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  oa->writeUInt64(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt64);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  oa->writeShort(tpb, %s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Short);
        } else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  oa->writeInt(tpb, %s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int);
        } else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  oa->writeLong(tpb, %s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Long);
        } else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  oa->writeChar(tpb, %s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Char);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  oa->writeStr(tpb, %s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Str);
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  oa->writeDouble(tpb, %s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Double);
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  oa->writeFloat(tpb, %s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Float);
        }
    }
    fprintf(out, "}\n");
 
}
static int tp_gen_cxx_proto_impl_deserialize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "%s::Deserialize(InputArchive *ia)\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  %s_ = ia->readUInt8(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt8);
        } else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  %s_ = oa->readInt8(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int8);
        } else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  %s_ = oa->readUInt8(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt8);
        } else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  %s_ = oa->readInt16(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int16);
        } else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  %s_ = oa->readUInt16(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt16);
        } else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  %s_ = oa->readInt32(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int32);
        } else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  %s_ = readUInt32(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt32);
        } else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  %s_ = readInt64(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int64);
        } else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  %s_ = readUInt64(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt64);
        } else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  %s_ = readInt(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int);
        } else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  %s_ = readShort(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Short);
        } else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  %s_ = readLong(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Long);
        } else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  %s_ = readChar(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Char);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  %s_ = readStr(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Str);
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  %s_ = readDouble(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Double);
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  %s_ = readFloat(tpb);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Float);
        }
    }
    fprintf(out, "}\n");
}

static int tp_gen_cxx_proto_impl_bytesize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "int %s::ByteSize()\n{\n", p->name);
    fprintf(out, "  int totalsize = 0;\n\n");
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE 
                || in->val_type == VALUE_TYPE_INT8
                || in->val_type == VALUE_TYPE_UINT8
                || in->val_type == VALUE_TYPE_INT16
                || in->val_type == VALUE_TYPE_UINT16
                || in->val_type == VALUE_TYPE_INT32
                || in->val_type == VALUE_TYPE_UINT32
                || in->val_type == VALUE_TYPE_INT64
                || in->val_type == VALUE_TYPE_UINT64
                || in->val_type == VALUE_TYPE_INT
                || in->val_type == VALUE_TYPE_SHORT
                || in->val_type == VALUE_TYPE_LONG
                || in->val_type == VALUE_TYPE_CHAR
                || in->val_type == VALUE_TYPE_DOUBLE
                || in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  totalsize += sizeof(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC
                || in->val_type == VALUE_TYPE_INT8_VEC
                || in->val_type == VALUE_TYPE_UINT8_VEC){
            fprintf(out, "  totalsize += sizeof(uint8_t)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT16_VEC
                || in->val_type == VALUE_TYPE_UINT16_VEC){
            fprintf(out, "  totalsize += sizeof(uint16_t)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32_VEC
                || in->val_type == VALUE_TYPE_UINT32_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT64_VEC
                || in->val_type == VALUE_TYPE_UINT64_VEC){
            fprintf(out, "  totalsize += sizeof(uint64_t)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            fprintf(out, "  totalsize += sizeof(int)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            fprintf(out, "  totalsize += sizeof(short)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            fprintf(out, "  totalsize += sizeof(long)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            fprintf(out, "  totalsize += sizeof(char)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  totalsize += %s_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            fprintf(out, "  for (int i=0; i < %s_vec_.size();i++){\n", in->name);
            fprintf(out, "    totalsize += %s_vec_[i].size();\n", in->name);
            fprintf(out, "  }\n");
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            fprintf(out, "  totalsize += sizeof(double)*%s_vec_.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            fprintf(out, "  totalsize += sizeof(float)*%s_vec_.size();\n", in->name);
        }
    }
    fprintf(out, "return totalsize;\n");
    fprintf(out, "}\n");

    return 0;
}

static int tp_gen_cxx_proto_impl(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    tp_gen_cxx_proto_impl_ctor(out, p);
    // The default constructor
    fprintf(out, "%s::%s()\n{\n", p->name, p->name);
    fprintf(out, "  %s::%s(NULL);\n", p->name, p->name);
    fprintf(out, "}\n");

    // Generate destructor
    fprintf(out, "%s::~%s()\n{\n", p->name, p->name);
    // delete object type
    fprintf(out, "}\n");

    // Generate serialize
    tp_gen_cxx_proto_impl_serialize(out, p);
    // Generate deserialize
    tp_gen_cxx_proto_impl_deserialize(out, p);
    // Generate ByteSize
    tp_gen_cxx_proto_impl_bytesize(out, p);


    return 0;
}

static int tp_gen_cxx_inc_file(FILE *out)
{
    // Generate include files
    fprintf(out, "\n#include <tpb_command.h>\n");

    // Other dynamic include

    return 0;
}

int tp_gen_cxx_code(const char *file)
{
    // Openfile
    FILE *hdrfile, *srcfile;
    struct protocol *proto, *cur_p;

    char hdrfilename[FILENAME_MAX]={0};
    char srcfilename[FILENAME_MAX]={0};

    hdrfile = srcfile = NULL;
    cur_p = proto = NULL;
    if (tpp_protocol_parse(file) != 0){
        fprintf(stderr, "Parse the protocol failed\n");
        return -1;
    }
    snprintf(hdrfilename, FILENAME_MAX-1, "%s%s", file, ".tpp.h"); 
    snprintf(srcfilename, FILENAME_MAX-1, "%s%s", file, ".tpp.cpp"); 
    // Create file for name.tpp.h
    hdrfile = fopen(hdrfilename, "w+");
    if (!hdrfile){
        fprintf(stderr, "Create the hdr file(%s) failed\n", hdrfilename);
        return -1;
    }
    // Create file for name.tpp.cpp
    srcfile = fopen(srcfilename, "w+");
    if (!hdrfile){
        fprintf(stderr, "Create the src file(%s) failed\n", srcfilename);
        fclose(hdrfile);
        return -1;
    }
    // Generate file header
    fprintf(hdrfile, "/// Generated by tpp compiler. Don't edit!\n");
    fprintf(hdrfile, "#ifndef _TPP_%s_TPP_H_\n#define _TPP_%s_TPP_H_\n", file, file);

    // Generate include file
    if (tp_gen_cxx_inc_file(hdrfile) != 0){
        // Generate include file failed
        fclose(hdrfile);
        fclose(hdrfile);
        return -1;
    }

    // Namespace for header file
    fprintf(hdrfile, "namespace tpp{\n");

    // Genereate the implementation
    fprintf(srcfile, "/// Generated by tpp compiler. Don't edit!\n");
    fprintf(srcfile, "#include \"%s\"\n", hdrfilename);

    // Namespace for source file
    fprintf(srcfile, "namespace tpp{\n");

    // Generate Protocol
    proto = tpp_protocol_tab_get();
    for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
        tp_gen_cxx_proto_decl(hdrfile, cur_p);
        tp_gen_cxx_proto_impl(srcfile, cur_p);
    }

    // namespace end for header file
    fprintf(hdrfile, "}\n");

    // namespace end for source file
    fprintf(srcfile, "}\n");

    // over
    fprintf(hdrfile, "#endif//_TPP_%s_TPP_H_\n\n", file);

    fflush(hdrfile);
    fclose(hdrfile);

    fflush(srcfile);
    fclose(srcfile);
}

