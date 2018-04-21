#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#include "tp_cxx_generator.h"
#include "tp_symbol_list.h"

extern int g_gen_struct;
extern int g_reg_cmd;
extern int g_gen_redis;

static const char *tp_gen_cxx_get_inttypestr_by_size(int size)
{
    if (size <= 1){
        return "int8_t";
    }else if (size <= 2){
        return "int16_t";
    }else if (size <= 4){
        return "int32_t";
    }else if (size <= 8){
        return "int64_t";
    }
    return "int32_t";
}
static const char *tp_gen_cxx_get_intfunstr_by_size(int size)
{
    if (size <= 1){
        return "Int8";
    }else if (size <= 2){
        return "Int16";
    }else if (size <= 4){
        return "Int32";
    }else if (size <= 8){
        return "Int64";
    }
    return "Int32";
}
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
    fprintf(out, "  void dump(std::ostream &os);\n");
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
    fprintf(out, "  return *this;\n");
    fprintf(out, "}\n");
    // Generate shared ctor
    fprintf(out, "void %s::SharedCtor()\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_PROTID_INT){
            fprintf(out, "  SetCommandID(%d);\n", in->value.int_val);
        }else if (in->val_type == VALUE_TYPE_PROTID_HEX){
            fprintf(out, "  SetCommandID(%s);\n", in->value.str_val);
        }
    }
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
    fprintf(out, "  SetHeader(tpp_from.GetHeader());\n");
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
        fprintf(out, "  %s %ssize = %s.size();\n", tp_gen_cxx_get_inttypestr_by_size(in->val_len), in->name, in->name);\
        fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->write%s(%ssize);\n", tp_gen_cxx_get_intfunstr_by_size(in->val_len), in->name);\
        fprintf(out, "  // Write element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);\
        fprintf(out, "    tpp_rc=!tpp_rc? tpp_rc: oa->write" #type "(%s[i]);\n", in->name);\
        fprintf(out, "  }\n\n");\
    } while(0);

#define tp_gen_cxx_proto_impl_deserialize_vec(type, datatype) \
    do{\
        fprintf(out, "\n  // Read size firstly\n");\
        fprintf(out, "  %s %ssize = 0;\n", tp_gen_cxx_get_inttypestr_by_size(in->val_len), in->name);\
        fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->read%s(%ssize);\n", tp_gen_cxx_get_intfunstr_by_size(in->val_len), in->name);\
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
            fprintf(out, "  tpp_rc=!tpp_rc? tpp_rc: oa->writeBool(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Bool);
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
            fprintf(out, "  tpp_rc = !tpp_rc? tpp_rc : ia->readBool(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Bool, bool);
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
        } else if (in->val_type == VALUE_TYPE_BYTE_VEC
                || in->val_type == VALUE_TYPE_INT8_VEC
                || in->val_type == VALUE_TYPE_BOOL_VEC
                || in->val_type == VALUE_TYPE_UINT8_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(uint8_t)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT16_VEC
                || in->val_type == VALUE_TYPE_UINT16_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(uint16_t)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32_VEC
                || in->val_type == VALUE_TYPE_UINT32_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(uint32_t)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT64_VEC
                || in->val_type == VALUE_TYPE_UINT64_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(uint64_t)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(int)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(short)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(long)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(char)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += %s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  for (int i=0; i < (int)%s.size();i++){\n", in->name);
            fprintf(out, "    totalsize += sizeof(uint32_t);\n");
            fprintf(out, "    totalsize += %s[i].size();\n", in->name);
            fprintf(out, "  }\n");
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(double)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  totalsize += sizeof(float)*%s.size();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  totalsize += %s.ByteSize();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  totalsize += sizeof(uint32_t);\n");
            fprintf(out, "  for (int i=0; i < (int)%s.size();i++){\n", in->name);
            fprintf(out, "    totalsize += %s[i].ByteSize();\n", in->name);
            fprintf(out, "  }\n");
        }
    }
    fprintf(out, "  return totalsize;\n");
    fprintf(out, "}\n");

    return 0;
}

#define tp_gen_cxx_proto_impl_dump_format() \
    do{\
        fprintf(out, "  os << \"%s = \" << %s << std::endl;\n", in->name, in->name);\
    }while(0);

#define tp_gen_cxx_proto_impl_dump_vec_format() \
    do{\
        fprintf(out, "  int %ssize = %s.size();\n", in->name, in->name);\
        fprintf(out, "  // Write element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);\
        fprintf(out, "    os << \"%svec[\" << i << \"] = \" << %s[i] << std::endl;\n", in->name, in->name);\
        fprintf(out, "  }\n\n");\
    }while(0);

static int tp_gen_cxx_proto_impl_dump(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "void %s::dump(std::ostream &os)\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE
                || in->val_type == VALUE_TYPE_INT8
                || in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  os << \"%s = \" << (unsigned int)%s << std::endl;\n", in->name, in->name);
        }else if(in->val_type == VALUE_TYPE_INT16
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
                || in->val_type == VALUE_TYPE_STR
                || in->val_type == VALUE_TYPE_BOOL){
            tp_gen_cxx_proto_impl_dump_format();       
        } else if (in->val_type == VALUE_TYPE_BYTE_VEC
                || in->val_type == VALUE_TYPE_INT8_VEC
                || in->val_type == VALUE_TYPE_UINT8_VEC
                || in->val_type == VALUE_TYPE_INT16_VEC
                || in->val_type == VALUE_TYPE_UINT16_VEC
                || in->val_type == VALUE_TYPE_INT32_VEC
                || in->val_type == VALUE_TYPE_UINT32_VEC
                || in->val_type == VALUE_TYPE_INT64_VEC
                || in->val_type == VALUE_TYPE_UINT64_VEC
                || in->val_type == VALUE_TYPE_INT_VEC 
                || in->val_type == VALUE_TYPE_SHORT_VEC
                || in->val_type == VALUE_TYPE_LONG_VEC
                || in->val_type == VALUE_TYPE_DOUBLE_VEC
                || in->val_type == VALUE_TYPE_FLOAT_VEC
                || in->val_type == VALUE_TYPE_BOOL_VEC
                || in->val_type == VALUE_TYPE_CHAR_VEC
                || in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_proto_impl_dump_vec_format();
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  %s.dump(os);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n  // Read size firstly\n");
            fprintf(out, "  int %ssize = %s.size();\n", in->name, in->name);
            fprintf(out, "  // Read element iteratively\n");
            fprintf(out, "  for(int i=0; i < %ssize; i++){\n", in->name);
            fprintf(out, "    %s[i].dump(os);\n", in->name);
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
static int tp_gen_cxx_proto_has_protid(struct protocol *proto)
{
	struct protocol *cur_p = NULL;
	for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next) {
		struct item_node *in = cur_p->head;
		for (; in != NULL; in = in->next) {
			if (in->val_type == VALUE_TYPE_PROTID_INT
				|| in->val_type == VALUE_TYPE_PROTID_HEX) {
				return 1;
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

static int tp_gen_cxx_inc_file(struct generated_file *gfile, FILE *out)
{
    struct inc_file *inc, *inc_tab;

    inc = inc_tab = NULL;
    // Generate include files
    fprintf(out, "\n#include <inttypes.h>\n");
    fprintf(out, "\n#include <iostream>\n");
    // Other dynamic include
    inc_tab = tpp_get_inc_file(gfile);
    for (inc = inc_tab; inc != NULL; inc=inc->next){
        if (inc->is_quote){
            fprintf(out, "#include \"%s.h\"\n", inc->filename);
        }else{
            fprintf(out, "#include <%s>\n", inc->filename);
        }
    }

    fprintf(out, "\n#include <tpb_command.h>\n");
    if (g_reg_cmd) {
        fprintf(out, "#include \"framework_command_manager.h\"\n");
    }

    return 0;
}

/*********************** The functions for redis begin **********************************/
static int tp_gen_cxx_proto_impl_redis_key(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;

    for (in = p->head; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_PREFIX_KEY_STR){
            fprintf(out, "  os << %s;\n", in->name);
        }
    }

    for (in = p->head; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_FOREIGN_KEY_INT
                || in->val_type == VALUE_TYPE_FOREIGN_KEY_STR){
            fprintf(out, "  os << \":\";\n");
            fprintf(out, "  os << %s;\n", in->name);
        }
    }

    for (in = p->head; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_PRIMARY_KEY_STR
                || in->val_type == VALUE_TYPE_PRIMARY_KEY_INT){
            fprintf(out, "  os << \":\";\n");
            fprintf(out, "  os << %s;\n", in->name);
        }
    }

    return 0;
}

static int tp_gen_cxx_proto_decl_redis_streaming_vec(FILE *out, struct protocol *p)
{
    fprintf(out, "  template<class T> void StreamingVector(std::ostream &os, std::vector<T> &vec, const std::string &column_name)\n  {\n");
    //fprintf(out, "  os << \"sadd \";\n");
    tp_gen_cxx_proto_impl_redis_key(out, p);
    fprintf(out, "    os << \":\" << column_name;\n");
    fprintf(out, "\n  // Get size firstly\n");
    fprintf(out, "    int vecsize = vec.size();\n");
    fprintf(out, "    // Add element iteratively\n");
    fprintf(out, "    for(int i=0; i < vecsize; i++){\n");
    fprintf(out, "      os << \" \" << vec[i];\n");
    fprintf(out, "    }\n");
    fprintf(out, "  }\n");
    return 0;
}

static int tp_gen_cxx_proto_decl_redis_vectoring_stream(FILE *out, struct protocol *p)
{
    fprintf(out, "  template<class T> void VectoringStream(void *reply, std::vector<T> &vec)\n  {\n");
    fprintf(out, "    int length = redis_okvm_reply_length(reply);\n");
    fprintf(out, "    for (int i = 0; i < length; i++){\n");
    fprintf(out, "      std::istringstream is(std::string(redis_okvm_reply_idxof_str(reply, i)));\n");
    fprintf(out, "      is >> vec[i];\n");
    fprintf(out, "    }\n");
    fprintf(out, "  }\n");
    return 0;
}

static int tp_gen_cxx_proto_decl_redis_bulk_read(FILE *out, struct protocol *p)
{
    fprintf(out, "  void BulkReadVec(const std::string &key)\n  {\n");
    fprintf(out, "    std::ostringstream os;\n");
    fprintf(out, "    os << \"smembers \";\n");
    tp_gen_cxx_proto_impl_redis_key(out, p);
    fprintf(out, "    os << \":\" << key;\n");
    fprintf(out, "    redis_okvm_bulk_read(os.str().c_str());\n");
    fprintf(out, "  }\n");
    return 0;
}

static int tp_gen_cxx_proto_decl_redis_bulk_write(FILE *out, struct protocol *p)
{
    fprintf(out, "  template<class T> void BulkWriteVec(void *ctx, std::vector<T> &vec, const std::string &key)\n  {\n");
    fprintf(out, "    std::ostringstream os;\n");
    fprintf(out, "    os << \"sadd \";\n");
    fprintf(out, "    StreamingVector(os, vec, key);\n");
    fprintf(out, "    redis_okvm_bulk_write(ctx, os.str().c_str());\n");
    fprintf(out, "  }\n");
    return 0;
}

static int tp_gen_cxx_proto_decl_redis_set(FILE *out, struct protocol *p)
{
    fprintf(out, "  template<class T> void Set(const std::string &key, t &v)\n  {\n");
    fprintf(out, "    std::ostringstream os;\n");
    fprintf(out, "    os << \"hset \";\n");
    tp_gen_cxx_proto_impl_redis_key(out, p);
    fprintf(out, "    os << \" \" << key << \" \" << v;\n");
    fprintf(out, "    return redis_okvm_write(os.str().c_str());");
    fprintf(out, "  }\n");
    return 0;
}

static int tp_gen_cxx_proto_decl_redis_get(FILE *out, struct protocol *p)
{
    fprintf(out, "  template<class T> T Get(const std::string &key)\n  {\n");
    fprintf(out, "    std::ostringstream os;\n");
    fprintf(out, "    os << \"hget \";\n");
    tp_gen_cxx_proto_impl_redis_key(out, p);
    fprintf(out, "    os << \" \" << key;\n");
    fprintf(out, "    void *reply = redis_okvm_read(os.str().c_str());\n");
    fprintf(out, "    std::istringstream is(std::string(redis_okvm_reply_str(reply)));\n");
    fprintf(out, "    T v;\n");
    fprintf(out, "    is >> v;\n");
    fprintf(out, "    redis_okvm_reply_free(reply);\n");
    fprintf(out, "    return v;\n");
    fprintf(out, "  }\n");
    return 0;
}

static int tp_gen_cxx_proto_decl_redis_add_vec(FILE *out, struct protocol *p)
{
    fprintf(out, "  template<class T> void AddVec(const std::string &key, std::vector<T> &vec)\n  {\n");
    fprintf(out, "    std::ostringstream os;\n");
    fprintf(out, "    os << \"sadd \";\n");
    fprintf(out, "    StreamingVector(os, vec, key);\n");
    fprintf(out, "    redis_okvm_write(os.str().c_str());\n");
    fprintf(out, "  }\n");
    return 0;
}

static int tp_gen_cxx_proto_decl_redis_rem_vec(FILE *out, struct protocol *p)
{
    fprintf(out, "  template<class T> void RemVec(const std::string &key, std::vector<T> &vec)\n  {\n");
    fprintf(out, "    std::ostringstream os;\n");
    fprintf(out, "    os << \"srem \";\n");
    fprintf(out, "    StreamingVector(os, vec, key);\n");
    fprintf(out, "    redis_okvm_write(os.str().c_str());\n");
    fprintf(out, "  }\n");
    return 0;
}

static int tp_gen_cxx_proto_decl_redis_get_vec(FILE *out, struct protocol *p)
{
    fprintf(out, "  template<class T> void GetVec(const std::string &key, std::vector<T> &vec)\n  {\n");
    fprintf(out, "    std::ostringstream os;\n");
    fprintf(out, "    os << \"smembers \";\n");
    tp_gen_cxx_proto_impl_redis_key(out, p);
    fprintf(out, "    os << \" \" << key;\n");
    fprintf(out, "    void *reply = redis_okvm_read(os.str().c_str());\n");
    fprintf(out, "    VectoringStream(reply, vec);\n");
    fprintf(out, "    redis_okvm_reply_free(reply);\n");
    fprintf(out, "  }\n");
    return 0;
}

#define tp_gen_cxx_decl_redis_getter_setter_type(type) \
    do {\
        fprintf(out, "  void redis_set_%s(" #type " d, bool to_redis=false)\n  {\n", in->name);\
        fprintf(out, "    %s = d;\n", in->name);\
        fprintf(out, "    if (to_redis){\n");\
        fprintf(out, "      Set(\"%s\", %s);\n",in->name,in->name);\
        fprintf(out, "    }\n");\
        fprintf(out, "  }\n");\
        fprintf(out, "  " #type " redis_get_%s(bool from_redis=false)\n  {\n", in->name);\
        fprintf(out, "    if (from_redis){\n");\
        fprintf(out, "      %s = Get(\"%s\");\n", in->name, in->name);\
        fprintf(out, "    }\n");\
        fprintf(out, "    return %s;\n", in->name);\
        fprintf(out, "  }\n");\
    }while(0);

#define tp_gen_cxx_decl_redis_getter_setter_type_vec(type) \
    do {\
        fprintf(out, "  void redis_add_%s(std::vector<" #type "> &vec, bool to_redis=false)\n  {\n", in->name);\
        fprintf(out, "    %s = vec;\n", in->name);\
        fprintf(out, "    if (to_redis){\n");\
        fprintf(out, "      AddVec(\"%s\", %s);\n",in->name,in->name);\
        fprintf(out, "    }\n");\
        fprintf(out, "  }\n");\
        fprintf(out, "  void redis_rem_%s(std::vector<" #type "> &vec, bool to_redis=false)\n  {\n", in->name);\
        fprintf(out, "    if (to_redis){\n");\
        fprintf(out, "      RemVec(\"%s\", vec);\n",in->name);\
        fprintf(out, "    }\n");\
        fprintf(out, "  }\n");\
        fprintf(out, "  " #type " redis_get_%s()\n  {\n", in->name);\
        fprintf(out, "    if (from_redis){\n");\
        fprintf(out, "      GetVec(\"%s\", %s);\n", in->name, in->name);\
        fprintf(out, "    }\n");\
        fprintf(out, "    return %s;\n", in->name);\
        fprintf(out, "  }\n");\
    }while(0);

static int tp_gen_cxx_proto_decl_redis_getter_setter(FILE *out, struct protocol *p)
{
    struct item_node *in = p->head;

    fprintf(out, "\n  // getter/setter\n");
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE || in->val_type == VALUE_TYPE_UINT8){
            tp_gen_cxx_decl_redis_getter_setter_type(uint8_t);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC ||in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(uint8_t);
        }else if (in->val_type == VALUE_TYPE_INT8){
            tp_gen_cxx_decl_redis_getter_setter_type(int8_t);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(int8_t);
        }else if (in->val_type == VALUE_TYPE_INT16){
            tp_gen_cxx_decl_redis_getter_setter_type(int16_t);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(int16_t);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            tp_gen_cxx_decl_redis_getter_setter_type(uint16_t);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(uint16_t);
        }else if (in->val_type == VALUE_TYPE_INT32){
            tp_gen_cxx_decl_redis_getter_setter_type(int32_t);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(int32_t);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            tp_gen_cxx_decl_redis_getter_setter_type(uint32_t);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(uint32_t);
        }else if (in->val_type == VALUE_TYPE_INT64){
            tp_gen_cxx_decl_redis_getter_setter_type(int64_t);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(int64_t);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            tp_gen_cxx_decl_redis_getter_setter_type(uint64_t);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(uint64_t);
        }else if (in->val_type == VALUE_TYPE_INT
                || in->val_type == VALUE_TYPE_PRIMARY_KEY_INT
                || in->val_type == VALUE_TYPE_FOREIGN_KEY_INT){
            tp_gen_cxx_decl_redis_getter_setter_type(int);
        }else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(int);
        }else if (in->val_type == VALUE_TYPE_LONG){
            tp_gen_cxx_decl_redis_getter_setter_type(long);
        }else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(long);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            tp_gen_cxx_decl_redis_getter_setter_type(short);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(short);
        }else if (in->val_type == VALUE_TYPE_CHAR){
            tp_gen_cxx_decl_redis_getter_setter_type(char);
        }else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(char);
        }else if (in->val_type == VALUE_TYPE_DOUBLE){
            tp_gen_cxx_decl_redis_getter_setter_type(double);
        }else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(double);
        }else if (in->val_type == VALUE_TYPE_FLOAT){
            tp_gen_cxx_decl_redis_getter_setter_type(float);
        }else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(float);
        }else if (in->val_type == VALUE_TYPE_STR
                || in->val_type == VALUE_TYPE_PRIMARY_KEY_STR
                || in->val_type == VALUE_TYPE_FOREIGN_KEY_STR){
            tp_gen_cxx_decl_redis_getter_setter_type(std::string);
        }else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(std::string);
        }else if (in->val_type == VALUE_TYPE_BOOL){
            tp_gen_cxx_decl_redis_getter_setter_type(bool);
        }else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_decl_redis_getter_setter_type_vec(bool);
        }else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  void redis_set_%s(%s d, bool to_redis=false)\n  {\n", in->name, in->ref_type);
            fprintf(out, "    %s = d;\n", in->name);
            fprintf(out, "    if (to_redis){\n");
            fprintf(out, "      Set(\"%s\", %s);\n",in->name,in->name);
            fprintf(out, "    }\n");
            fprintf(out, "  }\n");
            fprintf(out, "  %s redis_get_%s(bool from_redis=false)\n  {\n", in->ref_type, in->name);
            fprintf(out, "    if (from_redis){\n");
            fprintf(out, "      %s = Get(\"%s\");\n", in->name, in->name);
            fprintf(out, "    }\n");
            fprintf(out, "    return %s;\n", in->name);
            fprintf(out, "  }\n");
        }else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  void redis_add_%s(std::vector<%s> &vec, bool to_redis=false)\n  {\n", in->name, in->ref_type);
            fprintf(out, "    %s = vec;\n", in->name);
            fprintf(out, "    if (to_redis){\n");
            fprintf(out, "      AddVec(\"%s\", %s);\n",in->name,in->name);
            fprintf(out, "    }\n");
            fprintf(out, "  }\n");
            fprintf(out, "  void redis_rem_%s(std::vector<%s> &vec, bool to_redis=false)\n  {\n", in->name, in->ref_type);
            fprintf(out, "    if (to_redis){\n");
            fprintf(out, "      RemVec(\"%s\", vec);\n",in->name);
            fprintf(out, "    }\n");
            fprintf(out, "  }\n");
            fprintf(out, "  %s redis_get_%s()\n  {\n", in->ref_type, in->name);
            fprintf(out, "    if (from_redis){\n");
            fprintf(out, "      GetVec(\"%s\", %s);\n", in->name, in->name);
            fprintf(out, "    }\n");
            fprintf(out, "    return %s;\n", in->name);
            fprintf(out, "  }\n");
        }
    }

    return 0;
}

static int tp_gen_cxx_proto_impl_redis_store(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;

    fprintf(out, "int %s::Store()\n{\n", p->name);
    fprintf(out, "  std::ostringstream os;\n");
    fprintf(out, "  void *ctx = NULL;\n");
    fprintf(out, "\n");

    fprintf(out, "  ctx = redis_okvm_bulk_write_begin();\n");
    fprintf(out, "  if (!ctx) return -1;\n\n"); 
    fprintf(out, "  os << \"hmset \";\n");

    tp_gen_cxx_proto_impl_redis_key(out, p);

    for (in = p->head; in != NULL; in=in->next){
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
                || in->val_type == VALUE_TYPE_STR
                || in->val_type == VALUE_TYPE_BOOL
                || in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  os << \" %s \" << %s;\n", in->name, in->name);
        }
    }
    
    fprintf(out, "  // Store the member\n");
    fprintf(out, "  redis_okvm_bulk_write(ctx, os.str().c_str());\n");

    for (in = p->head; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE_VEC
                || in->val_type == VALUE_TYPE_INT8_VEC
                || in->val_type == VALUE_TYPE_UINT8_VEC
                || in->val_type == VALUE_TYPE_INT16_VEC
                || in->val_type == VALUE_TYPE_UINT16_VEC
                || in->val_type == VALUE_TYPE_INT32_VEC
                || in->val_type == VALUE_TYPE_UINT32_VEC
                || in->val_type == VALUE_TYPE_INT64_VEC
                || in->val_type == VALUE_TYPE_UINT64_VEC
                || in->val_type == VALUE_TYPE_INT_VEC 
                || in->val_type == VALUE_TYPE_SHORT_VEC
                || in->val_type == VALUE_TYPE_LONG_VEC
                || in->val_type == VALUE_TYPE_DOUBLE_VEC
                || in->val_type == VALUE_TYPE_FLOAT_VEC
                || in->val_type == VALUE_TYPE_BOOL_VEC
                || in->val_type == VALUE_TYPE_CHAR_VEC
                || in->val_type == VALUE_TYPE_STR_VEC
                || in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  // Bulk write the vector to redis set\n");
            fprintf(out, "  BulkWriteVec(ctx, %s, \"%s\");\n", in->name, in->name);
        }
    }

    fprintf(out, "  redis_okvm_bulk_write_end(ctx);\n");
    fprintf(out, "}\n");
    return 0;
}
static int tp_gen_cxx_proto_impl_redis_restore(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    int is_first_field = 1;

    fprintf(out, "int %s::Restore()\n{\n", p->name);
    fprintf(out, "  // Restore the member\n");
    fprintf(out, "  std::ostringstream os;\n");
    fprintf(out, "  void *ctx = NULL;\n");
    fprintf(out, "  void *reply = NULL;\n");
    fprintf(out, "  int length = 0;\n");
    fprintf(out, "  char *field = NULL;\n");
    fprintf(out, "\n");

    fprintf(out, "  ctx = redis_okvm_bulk_read_begin();\n");
    fprintf(out, "  if (!ctx) return -1;\n\n"); 
    fprintf(out, "  os << \"hgetall \";\n");
    tp_gen_cxx_proto_impl_redis_key(out, p);
    fprintf(out, " redis_okvm_bulk_read(os.str().c_str());\n");

    // The data memeber for vector get from redis set
    for (in = p->head; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE_VEC
                || in->val_type == VALUE_TYPE_INT8_VEC
                || in->val_type == VALUE_TYPE_UINT8_VEC
                || in->val_type == VALUE_TYPE_INT16_VEC
                || in->val_type == VALUE_TYPE_UINT16_VEC
                || in->val_type == VALUE_TYPE_INT32_VEC
                || in->val_type == VALUE_TYPE_UINT32_VEC
                || in->val_type == VALUE_TYPE_INT64_VEC
                || in->val_type == VALUE_TYPE_UINT64_VEC
                || in->val_type == VALUE_TYPE_INT_VEC 
                || in->val_type == VALUE_TYPE_SHORT_VEC
                || in->val_type == VALUE_TYPE_LONG_VEC
                || in->val_type == VALUE_TYPE_DOUBLE_VEC
                || in->val_type == VALUE_TYPE_FLOAT_VEC
                || in->val_type == VALUE_TYPE_BOOL_VEC
                || in->val_type == VALUE_TYPE_CHAR_VEC
                || in->val_type == VALUE_TYPE_STR_VEC
                || in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  // Get the data from redis set for vector type data memeber.\n");
            fprintf(out, "  BulkReadVec(\"%s\");\n", in->name);
        }
    }

    fprintf(out, "  reply = redis_okvm_bulk_read_reply(ctx);\n");
    fprintf(out, "  length = redis_okvm_reply_length(reply);\n");
    fprintf(out, "  for (int i = 0; i < length;){\n");
    fprintf(out, "    field = redis_okvm_reply_idxof_str(reply, i++);\n"); 
    for (in = p->head; in != NULL; in=in->next){
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
                || in->val_type == VALUE_TYPE_STR
                || in->val_type == VALUE_TYPE_BOOL
                || in->val_type == VALUE_TYPE_REF){
            if (is_first_field){
                fprintf(out, "    if (strcmp(field, \"%s\") == 0){\n", in->name);
                is_first_field = 0;
            }else{
                fprintf(out, "    }else if (strcmp(field, \"%s\") == 0){\n", in->name);
            }
            fprintf(out, "      std::istringstream is(std::string(redis_okvm_reply_idxof_str(reply, i++)));\n");
            fprintf(out, "      is >> %s\n", in->name);
        }
    }
    fprintf(out, "    }else{\n");
    fprintf(out, "      i++;\n");
    fprintf(out, "    }\n");
    fprintf(out, "  }\n");
    fprintf(out, "  redis_okvm_reply_free(reply);\n");

    for (in = p->head; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE_VEC
                || in->val_type == VALUE_TYPE_INT8_VEC
                || in->val_type == VALUE_TYPE_UINT8_VEC
                || in->val_type == VALUE_TYPE_INT16_VEC
                || in->val_type == VALUE_TYPE_UINT16_VEC
                || in->val_type == VALUE_TYPE_INT32_VEC
                || in->val_type == VALUE_TYPE_UINT32_VEC
                || in->val_type == VALUE_TYPE_INT64_VEC
                || in->val_type == VALUE_TYPE_UINT64_VEC
                || in->val_type == VALUE_TYPE_INT_VEC 
                || in->val_type == VALUE_TYPE_SHORT_VEC
                || in->val_type == VALUE_TYPE_LONG_VEC
                || in->val_type == VALUE_TYPE_DOUBLE_VEC
                || in->val_type == VALUE_TYPE_FLOAT_VEC
                || in->val_type == VALUE_TYPE_BOOL_VEC
                || in->val_type == VALUE_TYPE_CHAR_VEC
                || in->val_type == VALUE_TYPE_STR_VEC
                || in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  // Convert the stream to vector\n");
            fprintf(out, "  reply = redis_okvm_bulk_read_reply(ctx);\n");
            fprintf(out, "  VectoringStream(reply, %s);\n", in->name);
            fprintf(out, "  redis_okvm_reply_free(reply);\n");
        }
    }
    fprintf(out, "  return 0;\n");
    fprintf(out, "}\n");

    return 0;
}

static int tp_gen_cxx_proto_decl_redis(FILE *out, struct protocol *p)
{
    //Generate class header
    fprintf(out, "class %s {\npublic:\n ", p->name);

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
    fprintf(out, "  // Restore data from redis.\n");
    fprintf(out, "  int Restore();\n");
    fprintf(out, "  // Store data to redis\n");
    fprintf(out, "  int Store();\n");
    fprintf(out, "  void dump(std::ostream &os);\n");

    fprintf(out, "\n//The redis aux functions.\n");

    tp_gen_cxx_proto_decl_redis_streaming_vec(out, p);
    tp_gen_cxx_proto_decl_redis_vectoring_stream(out, p);
    tp_gen_cxx_proto_decl_redis_bulk_read(out, p);
    tp_gen_cxx_proto_decl_redis_bulk_write(out, p);
    tp_gen_cxx_proto_decl_redis_set(out, p);
    tp_gen_cxx_proto_decl_redis_get(out, p);
    tp_gen_cxx_proto_decl_redis_add_vec(out, p);
    tp_gen_cxx_proto_decl_redis_rem_vec(out, p);
    tp_gen_cxx_proto_decl_redis_get_vec(out, p);
    tp_gen_cxx_proto_decl_redis_getter_setter(out, p);

    fprintf(out, "private:\n");
    fprintf(out, "  void SharedCtor();\n");
    fprintf(out, "  void SharedDtor();\n");
    fprintf(out, "\nprivate:\n");

    tp_gen_cxx_data_member(out, p->head);
    fprintf(out, "};\n\n");

    return 0;
}

static int tp_gen_cxx_proto_impl_redis(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    tp_gen_cxx_proto_impl_ctor(out, p);
    // Generate destructor
    tp_gen_cxx_proto_impl_dtor(out, p);

    // Generate store for redis 
    tp_gen_cxx_proto_impl_redis_store(out, p);
    // Generate restore for redis 
    tp_gen_cxx_proto_impl_redis_restore(out, p);

    tp_gen_cxx_proto_impl_dump(out, p);

    return 0;
}
/*********************** The functions for redis end **********************************/

int tp_gen_cxx_code(const char *save_dir, const char *file)
{
    // Openfile
    FILE *hdrfile, *srcfile;
    struct protocol *proto, *cur_p;
    char *tmp_dir = NULL;
    char *upper_file = NULL;
    struct generated_file *gfile, *cur_gfile;

    char hdrfilename[FILENAME_MAX]={0};
    char srcfilename[FILENAME_MAX]={0};

    if (!file || file[0] == '\0'){
        fprintf(stderr, "Can't parse invalid file name\n");
        return -1;
    }

    gfile = cur_gfile = NULL;
    hdrfile = srcfile = NULL;
    cur_p = proto = NULL;
    if (tpp_protocol_parse(file) != 0){
        fprintf(stderr, "Parse the protocol failed\n");
        return -1;
    }

    gfile = tpp_gfile_get_list();
    for (cur_gfile = gfile; cur_gfile != NULL;cur_gfile = cur_gfile->next){
        snprintf(hdrfilename, FILENAME_MAX-1, "%s.h", cur_gfile->filename);
        snprintf(srcfilename, FILENAME_MAX-1, "%s.cpp", cur_gfile->filename);

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
        upper_file = strdup(cur_gfile->filename);
        upper_file = tp_toupper(upper_file);
        upper_file = tp_replace_x_with_y(upper_file, '.', '_');
        fprintf(hdrfile, "/// Generated by tpp compiler. Don't edit!\n");
        fprintf(hdrfile, "#ifndef _TPBUFF_%sH_\n#define _TPBUFF_%sH_\n", upper_file, upper_file);

        // Generate include file
        if (tp_gen_cxx_inc_file(cur_gfile, hdrfile) != 0){
            // Generate include file failed
            fclose(hdrfile);
            fclose(hdrfile);
            return -1;
        }

        proto = tpp_protocol_tab_get(cur_gfile);
        if (g_gen_struct){
			fprintf(hdrfile, "\n\n//----------------- The command definition bengin.-----------------------\n");
            for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
                tp_gen_cxx_protid(hdrfile, cur_p->head);
            }
            fprintf(hdrfile, "//---------------------- The command definition end.-------------------------\n\n");
        }

        // Namespace for header file
        char *pkgname = tpp_get_package_name(cur_gfile);
        if (pkgname){
            pkgname = strdup(pkgname);
            pkgname = tp_replace_x_with_y(pkgname, '.', '_');
        }
        fprintf(hdrfile, "namespace %s{\n", pkgname?pkgname:"tpp");

        // Genereate the implementation
        fprintf(srcfile, "/// Generated by tpp compiler. Don't edit!\n");
        fprintf(srcfile, "#include <stdio.h>\n");
        fprintf(srcfile, "#include \"%s\"\n", hdrfilename);
        fprintf(srcfile, "#include \"tpb_inputarchive.h\"\n");
        fprintf(srcfile, "#include \"tpb_outputarchive.h\"\n\n");

        // Generate Protocol
        for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
            if (g_gen_redis){
                tp_gen_cxx_proto_decl_redis(hdrfile, cur_p);
                tp_gen_cxx_proto_impl_redis(srcfile, cur_p);
            }else{
                tp_gen_cxx_proto_decl(hdrfile, cur_p);
                tp_gen_cxx_proto_impl(srcfile, cur_p);
            }
        }

        int has_protid = 0;
        if (proto) {
            has_protid = tp_gen_cxx_proto_has_protid(proto);
        }
        if (g_reg_cmd && has_protid) {
            char *ptr = strchr(cur_gfile->filename, '.');
            char *protocol_name = strndup(cur_gfile->filename, ptr - cur_gfile->filename);

            // Must at the  endline
            fprintf(hdrfile, "REGISTER_COMMAND_BEGIN(%s);\n", protocol_name);
            for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next) {
                tp_gen_cxx_proto_impl_register_cmd(hdrfile, cur_p);
            }
            fprintf(hdrfile, "REGISTER_COMMAND_END(%s);\n", protocol_name);

            free(protocol_name);
        }

        // namespace end for header file
        fprintf(hdrfile, "}\n");

        // over
        fprintf(hdrfile, "#endif//_TPBUFF_%s_H_\nusing namespace %s;\n", upper_file, pkgname?pkgname:"tpp");

        free(pkgname);
        free(upper_file);

        fflush(hdrfile);
        fclose(hdrfile);

        fflush(srcfile);
        fclose(srcfile);
    }

    tpp_gfile_destroy_list();

    return 0;
}

