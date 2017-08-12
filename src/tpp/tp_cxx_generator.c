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
            fprintf(out, "  std::vector<std::string> %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  int %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT_VEC){
            fprintf(out, "  std::vector<int> %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  long %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_LONG_VEC){
            fprintf(out, "  std::vector<long> %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  short %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            fprintf(out, "  std::vector<short> %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  char %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            fprintf(out, "  std::vector<char> %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  double %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            fprintf(out, "  std::vector<double> %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  float %s_;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            fprintf(out, "  std::vector<float> %s_;\n", in->name);
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

static int tp_gen_cxx_proto_impl(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    // Generate constructor
    fprintf(out, "%s::%s()\n{\n", p->name, p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_INT16
                || in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  %s_ = 0;\n", in->name); 
        }
    }
    fprintf(out, "}\n");

    // Generate destructor
    fprintf(out, "%s::~%s()\n{\n", p->name, p->name);
    // delete object type
    fprintf(out, "}\n");

    // Generate serialize
    fprintf(out, "%s::Serialize(OutputArchive *oa)\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  oa->writeShort(%s_);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  oa->writeInt(%s_);\n", in->name);
        }
    }
    fprintf(out, "}\n");
    // Generate deserialize
    fprintf(out, "%s::Deserialize(InputArchive *ia)\n{\n", p->name);
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  %s_ = ia->readShort();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  %s_ = oa->readInt();\n", in->name);
        }
    }
    fprintf(out, "}\n");

    return 0;
}

static int tp_gen_cxx_inc_file(FILE *out)
{
    // Generate include files
    fprintf(out, "\n#include <tpb_command.h>\n");

    // Other dynamic include

    return 0;
}
int tp_gen_cxx_byte();
int tp_gen_cxx_int16();
int tp_gen_cxx_int32();
int tp_gen_cxx_int64();
int tp_gen_cxx_uint16();
int tp_gen_cxx_uint32();
int tp_gen_cxx_uint64();
int tp_gen_cxx_str();
int tp_gen_cxx_double();
int tp_gen_cxx_float();

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

    // Genereate the implementation
    fprintf(srcfile, "/// Generated by tpp compiler. Don't edit!\n");
    fprintf(srcfile, "#include \"%s\"\n", hdrfilename);

    // Generate Protocol
    proto = tpp_protocol_tab_get();
    for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
        tp_gen_cxx_proto_decl(hdrfile, cur_p);
        tp_gen_cxx_proto_impl(srcfile, cur_p);
    }

    // over
    fprintf(hdrfile, "#endif//_TPP_%s_TPP_H_\n\n", file);

    fflush(hdrfile);
    fclose(hdrfile);

    fflush(srcfile);
    fclose(srcfile);
}

