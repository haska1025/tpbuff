#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#include "tp_cxx_generator.h"
#include "tp_symbol_list.h"

extern int g_gen_struct;

#define tp_gen_cxx_getter_setter_type(type) \
    do {\
        fprintf(out, "  " #type " get_%s(){return %s;}\n", in->name, in->name);\
        fprintf(out, "  void set_%s(" #type " i){%s=i;}\n\n", in->name, in->name);\
    }while(0);

#define tp_gen_cxx_getter_setter_type_vec(type) \
    do {\
        fprintf(out, "  std::vector<" #type "> &get_%s_vec(){return %s;}\n", in->name, in->name);\
        fprintf(out, "  void set_%s_vec(std::vector<" #type "> &i){%s=i;}\n", in->name, in->name);\
        fprintf(out, "  void append_to_%s_vec(" #type " i){%s.push_back(i);}\n\n",in->name, in->name);\
    }while(0);

static int tp_gen_cxx_getter_setter(FILE *out, struct item_node *n)
{
    struct item_node *in = n;

    fprintf(out, "\n  // getter/setter\n");
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE || in->val_type == VALUE_TYPE_UINT8){
            tp_gen_cxx_getter_setter_type(uint8_t);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC ||in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_getter_setter_type_vec(uint8_t);
        }else if (in->val_type == VALUE_TYPE_INT8){
            tp_gen_cxx_getter_setter_type(int8_t);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_getter_setter_type_vec(int8_t);
        }else if (in->val_type == VALUE_TYPE_INT16){
            tp_gen_cxx_getter_setter_type(int16_t);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_getter_setter_type_vec(int16_t);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            tp_gen_cxx_getter_setter_type(uint16_t);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_getter_setter_type_vec(uint16_t);
        }else if (in->val_type == VALUE_TYPE_INT32){
            tp_gen_cxx_getter_setter_type(int32_t);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_getter_setter_type_vec(int32_t);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            tp_gen_cxx_getter_setter_type(uint32_t);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_getter_setter_type_vec(uint32_t);
        }else if (in->val_type == VALUE_TYPE_INT64){
            tp_gen_cxx_getter_setter_type(int64_t);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_getter_setter_type_vec(int64_t);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            tp_gen_cxx_getter_setter_type(uint64_t);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_getter_setter_type_vec(uint64_t);
        }else if (in->val_type == VALUE_TYPE_INT){
            tp_gen_cxx_getter_setter_type(int);
        }else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_getter_setter_type_vec(int);
        }else if (in->val_type == VALUE_TYPE_LONG){
            tp_gen_cxx_getter_setter_type(long);
        }else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_getter_setter_type_vec(long);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            tp_gen_cxx_getter_setter_type(short);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_getter_setter_type_vec(short);
        }else if (in->val_type == VALUE_TYPE_CHAR){
            tp_gen_cxx_getter_setter_type(char);
        }else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_getter_setter_type_vec(char);
        }else if (in->val_type == VALUE_TYPE_DOUBLE){
            tp_gen_cxx_getter_setter_type(double);
        }else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_getter_setter_type_vec(double);
        }else if (in->val_type == VALUE_TYPE_FLOAT){
            tp_gen_cxx_getter_setter_type(float);
        }else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_getter_setter_type_vec(float);
        }else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  std::string &get_%s(){return %s;}\n", in->name, in->name);
            fprintf(out, "  void set_%s(std::string &s){%s=s;}\n", in->name, in->name);
            fprintf(out, "  void set_%s(const char *s){%s = s;}\n\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_getter_setter_type_vec(std::string);
        }else if (in->val_type == VALUE_TYPE_BOOL){
            tp_gen_cxx_getter_setter_type(bool);
        }else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_getter_setter_type_vec(bool);
        }else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  %s &get_%s(){return %s;}\n",in->ref_type, in->name, in->name);
            fprintf(out, "  void set_%s(const %s &obj){%s=obj;}\n",in->name, in->ref_type, in->name);
        }else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  std::vector<%s> &get_%s_vec(){return %s;}\n", in->ref_type, in->name, in->name);
            fprintf(out, "  void append_to_%s_vec(const %s &obj);\n\n",in->name, in->ref_type);
        }
    }

    return 0;
}
static int tp_gen_cxx_protid(FILE *out, struct item_node *n)
{
    struct item_node *in = n;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_PROTID_INT){
            fprintf(out, "  static const int %s=%d;\n", in->name, in->value.int_val);
        }else if (in->val_type == VALUE_TYPE_PROTID_HEX){
            fprintf(out, "  static const int %s=%s;\n", in->name, in->value.str_val);
        }
    }
    return 0;
}

static int tp_gen_cxx_data_member(FILE *out, struct item_node *n)
{
    struct item_node *in = n;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  uint8_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            fprintf(out, "  std::vector<uint8_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  int8_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            fprintf(out, "  std::vector<int8_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  uint8_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            fprintf(out, "  std::vector<uint8_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  int16_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            fprintf(out, "  std::vector<int16_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  uint16_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            fprintf(out, "  std::vector<uint16_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  int32_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            fprintf(out, "  std::vector<int32_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  uint32_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            fprintf(out, "  std::vector<uint32_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  int64_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            fprintf(out, "  std::vector<int64_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  uint64_t %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            fprintf(out, "  std::vector<uint64_t> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  std::string %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_STR_VEC){
            fprintf(out, "  std::vector<std::string> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  int %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT_VEC){
            fprintf(out, "  std::vector<int> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  long %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_LONG_VEC){
            fprintf(out, "  std::vector<long> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  short %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            fprintf(out, "  std::vector<short> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  char %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            fprintf(out, "  std::vector<char> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  double %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            fprintf(out, "  std::vector<double> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  float %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            fprintf(out, "  std::vector<float> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  bool %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            fprintf(out, "  std::vector<bool> %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  %s %s;\n", in->ref_type, in->name);
        }else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  std::vector<%s> %s;\n", in->ref_type, in->name);
        }
    }
    return 0;
}
static int tp_gen_cxx_proto_decl(FILE *out, struct protocol *p)
{
    //Generate class header
    fprintf(out, "class %s : public Command {\npublic:\n ", p->name);
    if (!g_gen_struct){
        tp_gen_cxx_protid(out, p->head);
    }
    fprintf(out, "  static Command * NewCommand();\n");
    fprintf(out, "  // constructor\n");
    fprintf(out, "  %s();\n", p->name);
    fprintf(out, "  // copy constructor\n");
    fprintf(out, "  %s(const %s &tpp_from);\n", p->name, p->name);
    fprintf(out, "  // assignment operator\n");
    fprintf(out, "  %s &operator=(const %s &tpp_from);\n", p->name, p->name);
    fprintf(out, "  // destructor\n");
    fprintf(out, "  ~%s();\n", p->name);
    fprintf(out, "  // Copy function\n");
    fprintf(out, "  void CopyFrom(const %s &tpp_from);\n", p->name);
    fprintf(out, "  // Convert object to bytes stream\n");
    fprintf(out, "  virtual bool Serialize(OutputArchive *oa);\n");
    fprintf(out, "  // Convert bytes stream to object\n");
    fprintf(out, "  virtual bool Deserialize(InputArchive *ia);\n");
    fprintf(out, "  // Return the size of the object\n");
    fprintf(out, "  virtual int ByteSize();\n");
    fprintf(out, "  void dump();\n");
    if (!g_gen_struct){
        tp_gen_cxx_getter_setter(out, p->head);
    }
    fprintf(out, "private:\n");
    fprintf(out, "  void SharedCtor();\n");
    fprintf(out, "  void SharedDtor();\n");
    if (!g_gen_struct){
        fprintf(out, "\nprivate:\n");
    }else{
        fprintf(out, "\npublic:\n");
    }
    tp_gen_cxx_data_member(out, p->head);
    fprintf(out, "};\n\n");

    return 0;
}

static void tp_gen_cxx_proto_impl_ctor(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate New
    fprintf(out, "Command *%s::NewCommand()\n{\n", p->name);
    fprintf(out, "  return new %s;\n", p->name);
    fprintf(out, "}\n");
    // Generate constructor
    fprintf(out, "%s::%s()\n{\n", p->name, p->name);
    fprintf(out, "  SharedCtor();\n"); 
    fprintf(out, "}\n");
    // Generate copy constructor
    fprintf(out, "%s::%s(const %s &tpp_from)\n{\n", p->name, p->name, p->name);
    fprintf(out, "  CopyFrom(tpp_from);\n");
    fprintf(out, "}\n");
    // Generate assignment operator 
    fprintf(out, "%s &%s::operator=(const %s &tpp_from)\n{\n", p->name, p->name, p->name);
    fprintf(out, "  if (&tpp_from != this){\n");
    fprintf(out, "    CopyFrom(tpp_from);\n");
    fprintf(out, "  }\n");
    fprintf(out, "  return *this;");
    fprintf(out, "}\n");
    // Generate shared ctor
    fprintf(out, "void %s::SharedCtor()\n{\n", p->name);
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
            fprintf(out, "  %s = 0;\n", in->name); 
        } 
    }
    fprintf(out, "}\n");
    // Generate CopyFrom
    fprintf(out, "void %s::CopyFrom(const %s &tpp_from)\n{\n", p->name, p->name);
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
                || in->val_type == VALUE_TYPE_FLOAT
                || in->val_type == VALUE_TYPE_REF
                || in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  %s = tpp_from.%s;\n", in->name, in->name); 
        }else if(in->val_type == VALUE_TYPE_PROTID_INT
                || in->val_type == VALUE_TYPE_PROTID_HEX){
            // do nothing;
        }else{
            fprintf(out, "  %s = tpp_from.%s;\n", in->name, in->name); 
        }
    }
    fprintf(out, "}\n");
}

static void tp_gen_cxx_proto_impl_dtor(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    fprintf(out, "%s::~%s()\n{\n", p->name, p->name);
    /*
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  if (%s != NULL){\n", in->name);
            fprintf(out, "    delete %s;\n", in->name);
            fprintf(out, "    %s = NULL;\n", in->name);
            fprintf(out, "  }\n");
        } else if(in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  int %ssize = %s.size();\n", in->name, in->name);
            fprintf(out, "  // Delete element iteratively\n");
            fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);
            fprintf(out, "    if (%s[i] != NULL){\n", in->name);
            fprintf(out, "      delete %s[i];\n", in->name);
            fprintf(out, "    }\n");
            fprintf(out, "  }\n");
            fprintf(out, "  %s.clear();\n\n", in->name);
        }
    }
    */
    fprintf(out, "}\n");
}

static void tp_gen_cxx_proto_impl_ref(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate reference member function 
    in = p->head;
    for (; in != NULL; in=in->next){
     if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n//Append function\n");
            fprintf(out, "void %s::append_to_%s_vec(const %s &obj)\n{\n", p->name, in->name, in->ref_type);
            fprintf(out, "  %s.push_back(obj);\n", in->name);
            fprintf(out, "}\n");
        }
    }
}


#define tp_gen_cxx_proto_impl_serialize_vec(type) \
    do{\
        fprintf(out, "\n  // Write size firstly\n");\
        fprintf(out, "  int %ssize = %s.size();\n", in->name, in->name);\
        fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeInt32(%ssize);\n", in->name);\
        fprintf(out, "  // Write element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);\
        fprintf(out, "    tpp_rc=!tpp_rc? tpp_rc: oa->write" #type "(%s[i]);\n", in->name);\
        fprintf(out, "  }\n\n");\
    } while(0);

#define tp_gen_cxx_proto_impl_deserialize_vec(type, datatype) \
    do{\
        fprintf(out, "\n  // Read size firstly\n");\
        fprintf(out, "  int %ssize = 0;\n", in->name);\
        fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readInt32(%ssize);\n", in->name);\
        fprintf(out, "  // Read element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);\
        fprintf(out, "    " #datatype " tmp;\n");\
        fprintf(out, "    tpp_rc = ia->read" #type "(tmp);\n");\
        fprintf(out, "    if (!tpp_rc)continue;\n");\
        fprintf(out, "    %s.push_back(tmp);\n", in->name);\
        fprintf(out, "  }\n\n");\
    } while(0);


     
static int tp_gen_cxx_proto_impl_serialize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "bool %s::Serialize(OutputArchive *oa)\n{\n", p->name);
    fprintf(out, "  bool tpp_rc = true;\n");
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeUInt8(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt8);
        }else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeInt8(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int8);
        }else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeUInt8(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt8);
        }else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeInt16(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int16);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeUInt16(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt16);
        }else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeInt32(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int32);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeUInt32(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt32);
        }else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeInt64(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int64);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeUInt64(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt64);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeShort(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Short);
        } else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeInt(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int);
        } else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeLong(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Long);
        } else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeChar(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Char);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeStr(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Str);
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeDouble(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Double);
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeFloat(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Float);
        } else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeInt8(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int8);
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: %s.Serialize(oa);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n  // Write size firstly\n");
            fprintf(out, "  int %ssize = %s.size();\n", in->name, in->name);
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeInt32(%ssize);\n", in->name);
            fprintf(out, "  // Write element iteratively\n");
            fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);
            fprintf(out, "    tpp_rc=!tpp_rc? tpp_rc: %s[i].Serialize(oa);\n", in->name);
            fprintf(out, "  }\n\n");
        }
    }
    fprintf(out, "  return tpp_rc;\n");
    fprintf(out, "}\n");
 
    return 0;
}
static int tp_gen_cxx_proto_impl_deserialize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "bool %s::Deserialize(InputArchive *ia)\n{\n", p->name);
    fprintf(out, "  bool tpp_rc = true;\n");
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readUInt8(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt8, uint8_t);
        } else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readInt8(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int8, int8_t);
        } else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readUInt8(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt8, uint8_t);
        } else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readInt16(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int16, int16_t);
        } else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readUInt16(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt16, uint16_t);
        } else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readInt32(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int32, int32_t);
        } else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readUInt32(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt32, uint32_t);
        } else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readInt64(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int64, int64_t);
        } else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readUInt64(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt64, uint64_t);
        } else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readInt(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int, int);
        } else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readShort(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Short, short);
        } else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readLong(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Long, long);
        } else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readChar(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Char, char);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readStr(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Str, std::string);
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readDouble(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Double, double);
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readFloat(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Float, float);
        } else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readInt8(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int8, int8_t);
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : %s.Deserialize(ia);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n  // Read size firstly\n");
            fprintf(out, "  int %ssize = 0;\n", in->name);
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readInt(%ssize);\n", in->name);
            fprintf(out, "  // Read element iteratively\n");
            fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);
            fprintf(out, "    %s ref_obj;\n", in->ref_type);
            fprintf(out, "    tpp_rc = ref_obj.Deserialize(ia);\n");
            fprintf(out, "    if (!tpp_rc) continue;\n");
            fprintf(out, "    %s.push_back(ref_obj);\n", in->name);
            fprintf(out, "  }\n\n");
        }
    }
    fprintf(out, "  return tpp_rc;\n");
    fprintf(out, "}\n");
    return 0;
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
                || in->val_type == VALUE_TYPE_FLOAT
                || in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  totalsize += sizeof(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC
                || in->val_type == VALUE_TYPE_INT8_VEC
                || in->val_type == VALUE_TYPE_BOOL_VEC
                || in->val_type == VALUE_TYPE_UINT8_VEC){
            fprintf(out, "  totalsize += sizeof(uint8_t)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT16_VEC
                || in->val_type == VALUE_TYPE_UINT16_VEC){
            fprintf(out, "  totalsize += sizeof(uint16_t)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32_VEC
                || in->val_type == VALUE_TYPE_UINT32_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT64_VEC
                || in->val_type == VALUE_TYPE_UINT64_VEC){
            fprintf(out, "  totalsize += sizeof(uint64_t)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            fprintf(out, "  totalsize += sizeof(int)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            fprintf(out, "  totalsize += sizeof(short)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            fprintf(out, "  totalsize += sizeof(long)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            fprintf(out, "  totalsize += sizeof(char)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  totalsize += %s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            fprintf(out, "  for (int i=0; i < %s.size();i++){\n", in->name);
            fprintf(out, "    totalsize += %s[i].size();\n", in->name);
            fprintf(out, "  }\n");
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            fprintf(out, "  totalsize += sizeof(double)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            fprintf(out, "  totalsize += sizeof(float)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  totalsize += %s.ByteSize();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  for (int i=0; i < %s.size();i++){\n", in->name);
            fprintf(out, "    totalsize += %s[i].ByteSize();\n", in->name);
            fprintf(out, "  }\n");
        }
    }
    fprintf(out, "  return totalsize;\n");
    fprintf(out, "}\n");

    return 0;
}

#define tp_gen_cxx_proto_impl_dump_format(fmt) \
    do{\
        fprintf(out, "  fprintf(stdout, \"%s = %" fmt "\\n\", %s);\n", in->name, in->name);\
    }while(0);

#define tp_gen_cxx_proto_impl_dump_vec_format(fmt) \
    do{\
        fprintf(out, "  int %ssize = %s.size();\n", in->name, in->name);\
        fprintf(out, "  // Write element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);\
        fprintf(out, "    fprintf(stdout, \"%svec[%%d] = %" fmt "\\n\",i, %s[i]);\n", in->name, in->name);\
        fprintf(out, "  }\n\n");\
    }while(0);

static int tp_gen_cxx_proto_impl_dump(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "void %s::dump()\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            tp_gen_cxx_proto_impl_dump_format("%u");
        } else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%u");
        } else if (in->val_type == VALUE_TYPE_INT8){
            tp_gen_cxx_proto_impl_dump_format("%d");
        } else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%d");
        } else if (in->val_type == VALUE_TYPE_UINT8){
            tp_gen_cxx_proto_impl_dump_format("%u");
        } else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%u");
        } else if (in->val_type == VALUE_TYPE_INT16){
            tp_gen_cxx_proto_impl_dump_format("%d");
        } else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%d");
        } else if (in->val_type == VALUE_TYPE_UINT16){
            tp_gen_cxx_proto_impl_dump_format("%u");
        } else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%u");
        } else if (in->val_type == VALUE_TYPE_INT32){
            tp_gen_cxx_proto_impl_dump_format("%d");
        } else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%d");
        } else if (in->val_type == VALUE_TYPE_UINT32){
            tp_gen_cxx_proto_impl_dump_format("%u");
        } else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%u");
        } else if (in->val_type == VALUE_TYPE_INT64){
            tp_gen_cxx_proto_impl_dump_format("%" PRId64);
        } else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%" PRId64);
        } else if (in->val_type == VALUE_TYPE_UINT64){
            tp_gen_cxx_proto_impl_dump_format("%" PRIu64);
        } else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%" PRIu64);
        } else if (in->val_type == VALUE_TYPE_INT){
            tp_gen_cxx_proto_impl_dump_format("%d");
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%d");
        } else if (in->val_type == VALUE_TYPE_SHORT){
            tp_gen_cxx_proto_impl_dump_format("%d");
        } else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%d");
        } else if (in->val_type == VALUE_TYPE_LONG){
            tp_gen_cxx_proto_impl_dump_format("%ld");
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%ld");
        } else if (in->val_type == VALUE_TYPE_CHAR){
            tp_gen_cxx_proto_impl_dump_format("%c");
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%c");
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  fprintf(stdout, \"%s = %%s\\n\", %s.c_str());\n", in->name, in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            fprintf(out, "\n  // Read size firstly\n");
            fprintf(out, "  int %ssize = %s.size();\n", in->name, in->name);
            fprintf(out, "  // Read element iteratively\n");
            fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);
            fprintf(out, "    fprintf(stdout, \"%svec[%%d] = %%s\\n\", i, %s[i].c_str());\n", in->name, in->name);
            fprintf(out, "  }\n\n");
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            tp_gen_cxx_proto_impl_dump_format("%f");
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%f");
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            tp_gen_cxx_proto_impl_dump_format("%f");
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%f");
        } else if (in->val_type == VALUE_TYPE_BOOL){
            tp_gen_cxx_proto_impl_dump_format("%d");
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format("%d");
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  %s.dump();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n  // Read size firstly\n");
            fprintf(out, "  int %ssize = %s.size();\n", in->name, in->name);
            fprintf(out, "  // Read element iteratively\n");
            fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);
            fprintf(out, "    %s[i].dump();\n", in->name);
            fprintf(out, "  }\n\n");
        }
    }
    fprintf(out, "}\n");

    return 0;
}
static int tp_gen_cxx_proto_impl_register_cmd(FILE *out, struct protocol *p)
{
    struct item_node *in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_PROTID_INT
                || in->val_type == VALUE_TYPE_PROTID_HEX){
            if (g_gen_struct){
                fprintf(out, "  REGISTER_COMMAND(%s, %s::NewCommand);\n", in->name, p->name);
            }else{
                fprintf(out, "  REGISTER_COMMAND(%s::%s, %s::NewCommand);\n", p->name, in->name, p->name);
            }
        }
    }
    return 0;
}
static int tp_gen_cxx_proto_impl(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    tp_gen_cxx_proto_impl_ctor(out, p);
    // Generate destructor
    tp_gen_cxx_proto_impl_dtor(out, p);

    // Generate serialize
    tp_gen_cxx_proto_impl_serialize(out, p);
    // Generate deserialize
    tp_gen_cxx_proto_impl_deserialize(out, p);
    // Generate ByteSize
    tp_gen_cxx_proto_impl_bytesize(out, p);

    if (!g_gen_struct){
        tp_gen_cxx_proto_impl_ref(out, p);
    }

    tp_gen_cxx_proto_impl_dump(out, p);


    return 0;
}

static int tp_gen_cxx_inc_file(FILE *out)
{
    struct inc_file *inc, *inc_tab;

    inc = inc_tab = NULL;
    // Generate include files
    fprintf(out, "\n#include <inttypes.h>\n");
    // Other dynamic include
    inc_tab = tpp_get_inc_file();
    for (inc = inc_tab; inc != NULL; inc=inc->next){
        fprintf(out, "#include <%s>\n", inc->filename);
    }

    fprintf(out, "\n#include <tpb_command.h>\n");
    return 0;
}

int tp_gen_cxx_code(const char *save_dir, const char *file)
{
    // Openfile
    FILE *hdrfile, *srcfile;
    struct protocol *proto, *cur_p;
    char *tmp_dir = NULL;
    char *upper_file = NULL;

    char hdrfilename[FILENAME_MAX]={0};
    char srcfilename[FILENAME_MAX]={0};

    if (!file || file[0] == '\0'){
        fprintf(stderr, "Can't parse invalid file name\n");
        return -1;
    }

    hdrfile = srcfile = NULL;
    cur_p = proto = NULL;
    if (tpp_protocol_parse(file) != 0){
        fprintf(stderr, "Parse the protocol failed\n");
        return -1;
    }
    snprintf(hdrfilename, FILENAME_MAX-1, "%s.h", file);
    snprintf(srcfilename, FILENAME_MAX-1, "%s.cpp", file);

    if (!save_dir || save_dir[0] == '\0'){
        tmp_dir = tp_concat_path("./", hdrfilename);
    }else{
        tmp_dir = tp_concat_path(save_dir, hdrfilename);
    }


    // Create file for name.tpp.h
    hdrfile = fopen(tmp_dir, "w+");
    if (!hdrfile){
        fprintf(stderr, "Create the hdr file(%s) failed\n", tmp_dir);
        free(tmp_dir);
        return -1;
    }
    // Create file for name.tpp.cpp
    free(tmp_dir);

    if (!save_dir || save_dir[0] == '\0'){
        tmp_dir = tp_concat_path("./", srcfilename);
    }else{
        tmp_dir = tp_concat_path(save_dir, srcfilename);
    }

    srcfile = fopen(srcfilename, "w+");
    if (!hdrfile){
        fprintf(stderr, "Create the src file(%s) failed\n", srcfilename);
        fclose(hdrfile);
        free(tmp_dir);
        return -1;
    }
    free(tmp_dir);

    // Generate file header
    upper_file = tp_toupper(file);
    fprintf(hdrfile, "/// Generated by tpp compiler. Don't edit!\n");
    fprintf(hdrfile, "#ifndef _TPBUFF_%sH_\n#define _TPBUFF_%sH_\n", upper_file, upper_file);

    // Generate include file
    if (tp_gen_cxx_inc_file(hdrfile) != 0){
        // Generate include file failed
        fclose(hdrfile);
        fclose(hdrfile);
        return -1;
    }

    proto = tpp_protocol_tab_get();
    if (g_gen_struct){
        fprintf(hdrfile, "\n\n//----------------- The command definition bengin.-----------------------\n");
        for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
            tp_gen_cxx_protid(hdrfile, cur_p->head);
        }
        fprintf(hdrfile, "//---------------------- The command definition end.-------------------------\n\n");
    }

    // Namespace for header file
    fprintf(hdrfile, "namespace tpp{\n");

    // Genereate the implementation
    fprintf(srcfile, "/// Generated by tpp compiler. Don't edit!\n");
    fprintf(srcfile, "#include <stdio.h>\n");
    fprintf(srcfile, "#include \"%s\"\n", hdrfilename);
    fprintf(srcfile, "#include \"command_manager.h\"\n");
    fprintf(srcfile, "#include \"tpb_inputarchive.h\"\n");
    fprintf(srcfile, "#include \"tpb_outputarchive.h\"\n\n");

    // Namespace for source file
    //fprintf(srcfile, "namespace tpp{\n");
    //fprintf(srcfile, "using namespace tpp;\n\n");

    // Generate Protocol
    for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
        tp_gen_cxx_proto_decl(hdrfile, cur_p);
        tp_gen_cxx_proto_impl(srcfile, cur_p);
    }

    // Must at the  endline
    fprintf(srcfile, "REGISTER_COMMAND_BEGIN();\n");
    for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
        tp_gen_cxx_proto_impl_register_cmd(srcfile, cur_p);
    }
    fprintf(srcfile, "REGISTER_COMMAND_END();\n");

    // namespace end for header file
    fprintf(hdrfile, "}\n");

    // namespace end for source file
    //fprintf(srcfile, "}\n");

    // over
    fprintf(hdrfile, "#endif//_TPBUFF_%s_H_\nusing namespace tpp;\n", upper_file);

    free(upper_file);

    fflush(hdrfile);
    fclose(hdrfile);

    fflush(srcfile);
    fclose(srcfile);

    tpp_protocol_tab_destroy();
    tpp_destroy_inc_file();


    return 0;
}

