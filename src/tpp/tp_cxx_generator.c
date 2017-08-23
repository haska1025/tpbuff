#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tp_cxx_generator.h"
#include "tp_symbol_list.h"

#define tp_gen_cxx_getter_setter_type(type) \
    do {\
        fprintf(out, "  " #type " %s(){return %s_;}\n", in->name, in->name);\
        fprintf(out, "  void %s(" #type " i){%s_=i;}\n\n", in->name, in->name);\
    }while(0);

#define tp_gen_cxx_getter_setter_type_vec(type) \
    do {\
        fprintf(out, "  std::vector<" #type "> &%s_vec(){return %s_vec_;}\n", in->name, in->name);\
        fprintf(out, "  void %s_vec(std::vector<" #type "> &i){%s_vec_=i;}\n", in->name, in->name);\
        fprintf(out, "  void append_to_%s_vec(" #type " i){%s_vec_.push_back(i);}\n\n",in->name, in->name);\
    }while(0);

static char * tp_toupper(const char *s)
{
    char *ns1, *ns2;
    
    ns1 = strdup(s);
    ns2 = ns1;
    while (*ns1){
        if (*ns1 == '.'){
            *ns1='_';
        }else{
            *ns1 = toupper(*ns1);
        }
        ns1++;
    }

    return ns2;
}

static char * tp_concat_path(const char *dir, const char *filename)
{
    char *tmp_dir = NULL;
    int path_len, dir_len, filename_len;
    
    dir_len = strlen(dir);
    filename_len = strlen(filename);

    path_len = dir_len + filename_len + 2;
    tmp_dir = malloc(path_len);
    strncpy(tmp_dir, dir, dir_len);
    if (dir[dir_len-1] != '/'){
        tmp_dir[dir_len] = '/';
        dir_len++;
    }

    strncpy(tmp_dir+dir_len, filename, filename_len);
    tmp_dir[path_len-1] = '\0';
    
    return tmp_dir;
}

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
            fprintf(out, "  std::string &%s(){return %s_;}\n", in->name, in->name);
            fprintf(out, "  void %s(std::string &s){%s_=s;}\n", in->name, in->name);
            fprintf(out, "  void %s(const char *s){%s_ = s;}\n\n", in->name, in->name);
        }else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_getter_setter_type_vec(std::string);
        }else if (in->val_type == VALUE_TYPE_BOOL){
            tp_gen_cxx_getter_setter_type(bool);
        }else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_getter_setter_type_vec(bool);
        }else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  %s *%s(){return %s_;}\n",in->ref_type, in->name, in->name);
            fprintf(out, "  %s *mutable_%s();\n",in->ref_type, in->name);
            fprintf(out, "  void set_allocated_%s(%s *alloc_ptr);\n\n",in->name, in->ref_type);
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
        }else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  bool %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            fprintf(out, "  std::vector<bool> %s_vec_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  %s *%s_;\n", in->ref_type, in->name);
        }else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  std::vector<%s*> %s_vec_;\n", in->ref_type, in->name);
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

static void tp_gen_cxx_proto_impl_ctor(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    fprintf(out, "%s::%s()\n{\n", p->name, p->name);
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

static void tp_gen_cxx_proto_impl_dtor(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    fprintf(out, "%s::~%s()\n{\n", p->name, p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  if (%s_ != NULL){\n", in->name);
            fprintf(out, "    delete %s_;\n", in->name);
            fprintf(out, "    %s_ = NULL;\n", in->name);
            fprintf(out, "  }\n");
        } else if(in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  int %s_size = %s_vec_.size();\n", in->name, in->name);
            fprintf(out, "  // Delete element iteratively\n");
            fprintf(out, "  for(int i=0; i < %s_size; i++){\n", in->name);
            fprintf(out, "    if (%s_vec_[i] != NULL){\n", in->name);
            fprintf(out, "      delete %s_vec_[i];\n", in->name);
            fprintf(out, "    }\n");
            fprintf(out, "  }\n");
            fprintf(out, "  %s_vec_.clear()\n\n", in->name);
        }
    }
    fprintf(out, "}\n");
}

static void tp_gen_cxx_proto_impl_ref(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "\n//Mutable function\n");
            fprintf(out, "%s * %s::mutable_%s()\n{\n", in->ref_type, p->name, in->name);
            fprintf(out, "  if (!%s_){\n", in->name);
            fprintf(out, "    %s_ = new %s();\n", in->name, in->ref_type);
            fprintf(out, "  }\n");
            fprintf(out, "  return %s_;\n", in->name);
            fprintf(out, "}\n");

            fprintf(out, "\n//Alloc set function\n");
            fprintf(out, "void %s::set_allocated_%s(%s *alloc_ptr)\n{\n", p->name, in->name, in->ref_type);
            fprintf(out, "  if (%s_ != NULL){\n", in->name);
            fprintf(out, "    delete %s_;\n", in->name);
            fprintf(out, "  }\n");
            fprintf(out, "  %s_ = alloc_ptr;\n", in->name);
            fprintf(out, "}\n");
        }
    }
}


#define tp_gen_cxx_proto_impl_serialize_vec(type) \
    do{\
        fprintf(out, "\n  // Write size firstly\n");\
        fprintf(out, "  int %s_size = %s_vec_.size();\n", in->name, in->name);\
        fprintf(out, "  oa->writeInt32(%s_size);\n", in->name);\
        fprintf(out, "  // Write element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %s_size; i++){\n", in->name);\
        fprintf(out, "    oa->write" #type "(%s_vec_[i]);\n", in->name);\
        fprintf(out, "  }\n\n");\
    } while(0);

#define tp_gen_cxx_proto_impl_deserialize_vec(type) \
    do{\
        fprintf(out, "\n  // Read size firstly\n");\
        fprintf(out, "  int %s_size = ia->readInt32();\n", in->name);\
        fprintf(out, "  // Read element iteratively\n");\
        fprintf(out, "  for(int i=0; i < %s_size; i++){\n", in->name);\
        fprintf(out, "    %s_vec_[i] = ia->read" #type "();\n", in->name);\
        fprintf(out, "  }\n\n");\
    } while(0);


     
static int tp_gen_cxx_proto_impl_serialize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "bool %s::Serialize(OutputArchive *oa)\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  oa->writeUInt8(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt8);
        }else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  oa->writeInt8(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int8);
        }else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  oa->writeUInt8(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt8);
        }else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  oa->writeInt16(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int16);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  oa->writeUInt16(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt16);
        }else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  oa->writeInt32(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int32);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  oa->writeUInt32(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt32);
        }else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  oa->writeInt64(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int64);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  oa->writeUInt64(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(UInt64);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  oa->writeShort(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Short);
        } else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  oa->writeInt(%s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int);
        } else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  oa->writeLong(%s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Long);
        } else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  oa->writeChar(%s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Char);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  oa->writeStr(%s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Str);
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  oa->writeDouble(%s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Double);
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  oa->writeFloat(%s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Float);
        } else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  oa->writeInt8(%s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_proto_impl_serialize_vec(Int8);
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  if (%s_ != NULL){\n", in->name);
            fprintf(out, "    %s_->Serialize(oa);\n", in->name);
            fprintf(out, "  }\n");
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n  // Write size firstly\n");
            fprintf(out, "  int %s_size = %s_vec_.size();\n", in->name, in->name);
            fprintf(out, "  oa->writeInt32(%s_size);\n", in->name);
            fprintf(out, "  // Write element iteratively\n");
            fprintf(out, "  for(int i=0; i < %s_size; i++){\n", in->name);
            fprintf(out, "    %s()->Serialize(oa);\n", in->name);
            fprintf(out, "  }\n\n");
        }
    }
    fprintf(out, "}\n");
 
}
static int tp_gen_cxx_proto_impl_deserialize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "bool %s::Deserialize(InputArchive *ia)\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  %s_ = ia->readUInt8();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt8);
        } else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  %s_ = ia->readInt8();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int8);
        } else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  %s_ = ia->readUInt8();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt8);
        } else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  %s_ = ia->readInt16();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int16);
        } else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  %s_ = ia->readUInt16();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt16);
        } else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  %s_ = ia->readInt32();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int32);
        } else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  %s_ = ia->readUInt32();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt32);
        } else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  %s_ = ia->readInt64();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int64);
        } else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  %s_ = ia->readUInt64();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(UInt64);
        } else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  %s_ = ia->readInt();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int);
        } else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  %s_ = ia->readShort();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Short);
        } else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  %s_ = ia->readLong();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Long);
        } else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  %s_ = ia->readChar();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Char);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  %s_ = ia->readStr();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Str);
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  %s_ = ia->readDouble();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Double);
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  %s_ = ia->readFloat();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Float);
        } else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  %s_ = ia->readInt8();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_cxx_proto_impl_deserialize_vec(Int8);
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  mutable_%s()->Deserialize(ia);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n  // Read size firstly\n");
            fprintf(out, "  int %s_size = ia->readInt();\n", in->name);
            fprintf(out, "  // Read element iteratively\n");
            fprintf(out, "  for(int i=0; i < %s_size; i++){\n", in->name);
            fprintf(out, "    %s_vec_[i] = mutable_%s();\n", in->name, in->name);
            fprintf(out, "    %s_vec_[i]->Deserialize(ia);\n", in->name);
            fprintf(out, "  }\n\n");
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
                || in->val_type == VALUE_TYPE_FLOAT
                || in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  totalsize += sizeof(%s_);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC
                || in->val_type == VALUE_TYPE_INT8_VEC
                || in->val_type == VALUE_TYPE_BOOL_VEC
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
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  totalsize += %s()->ByteSize();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  for (int i=0; i < %s_vec_.size();i++){\n", in->name);
            fprintf(out, "    totalsize += %s_vec_[i]->ByteSize();\n", in->name);
            fprintf(out, "  }\n");
        }
    }
    fprintf(out, "  return totalsize;\n");
    fprintf(out, "}\n");

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

    tp_gen_cxx_proto_impl_ref(out, p);

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
    fprintf(hdrfile, "#ifndef _TPBUFF_%s_H_\n#define _TPBUFF_%s_H_\n", upper_file, upper_file);

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
    fprintf(srcfile, "#include \"tpb_inputarchive.h\"\n");
    fprintf(srcfile, "#include \"tpb_outputarchive.h\"\n\n");

    // Namespace for source file
    //fprintf(srcfile, "namespace tpp{\n");
    fprintf(srcfile, "using namespace tpp;\n\n");

    // Generate Protocol
    proto = tpp_protocol_tab_get();
    for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
        tp_gen_cxx_proto_decl(hdrfile, cur_p);
        tp_gen_cxx_proto_impl(srcfile, cur_p);
    }

    // namespace end for header file
    fprintf(hdrfile, "}\n");

    // namespace end for source file
    //fprintf(srcfile, "}\n");

    // over
    fprintf(hdrfile, "#endif//_TPBUFF_%s_H_\n\n", upper_file);

    free(upper_file);

    fflush(hdrfile);
    fclose(hdrfile);

    fflush(srcfile);
    fclose(srcfile);

    tpp_protocol_tab_destroy();
    tpp_destroy_inc_file();


    return 0;
}

