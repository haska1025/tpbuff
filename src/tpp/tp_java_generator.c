#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tp_java_generator.h"
#include "tp_symbol_list.h"

#define tp_gen_java_getter_setter_type(type) \
    do {\
        fprintf(out, "  public " #type " get%c%s(){return %s;}\n", toupper(in->name[0]), (in->name+1), in->name);\
        fprintf(out, "  public void set%c%s(" #type " param){%s=param;}\n\n", toupper(in->name[0]), (in->name+1), in->name);\
    }while(0);

#define tp_gen_java_getter_setter_type_vec(type) \
    do {\
        fprintf(out, "  public " #type "[] get%c%s(){return %s;}\n", toupper(in->name[0]), (in->name+1), in->name);\
        fprintf(out, "  public void set%c%s(" #type "[] param){%s=param;}\n", toupper(in->name[0]), (in->name+1), in->name);\
    }while(0);

static int tp_gen_java_getter_setter(FILE *out, struct item_node *n)
{
    struct item_node *in = n;

    fprintf(out, "\n  // getter/setter\n");
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE || in->val_type == VALUE_TYPE_UINT8){
            tp_gen_java_getter_setter_type(byte);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC ||in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_java_getter_setter_type(byte[]);
        }else if (in->val_type == VALUE_TYPE_INT8){
            tp_gen_java_getter_setter_type(byte);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_java_getter_setter_type(byte[]);
        }else if (in->val_type == VALUE_TYPE_INT16){
            tp_gen_java_getter_setter_type(short);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_java_getter_setter_type_vec(short);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            tp_gen_java_getter_setter_type(int);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_java_getter_setter_type_vec(int);
        }else if (in->val_type == VALUE_TYPE_INT32){
            tp_gen_java_getter_setter_type(int);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_java_getter_setter_type_vec(int);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            tp_gen_java_getter_setter_type(long);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_java_getter_setter_type_vec(long);
        }else if (in->val_type == VALUE_TYPE_INT64){
            tp_gen_java_getter_setter_type(long);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_java_getter_setter_type_vec(long);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            tp_gen_java_getter_setter_type(long);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_java_getter_setter_type_vec(long);
        }else if (in->val_type == VALUE_TYPE_INT){
            tp_gen_java_getter_setter_type(int);
        }else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_java_getter_setter_type_vec(int);
        }else if (in->val_type == VALUE_TYPE_LONG){
            tp_gen_java_getter_setter_type(long);
        }else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_java_getter_setter_type_vec(long);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            tp_gen_java_getter_setter_type(short);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_java_getter_setter_type_vec(short);
        }else if (in->val_type == VALUE_TYPE_CHAR){
            tp_gen_java_getter_setter_type(char);
        }else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_java_getter_setter_type_vec(char);
        }else if (in->val_type == VALUE_TYPE_DOUBLE){
            tp_gen_java_getter_setter_type(double);
        }else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_java_getter_setter_type_vec(double);
        }else if (in->val_type == VALUE_TYPE_FLOAT){
            tp_gen_java_getter_setter_type(float);
        }else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_java_getter_setter_type_vec(float);
        }else if (in->val_type == VALUE_TYPE_STR){
            tp_gen_java_getter_setter_type(String);
        }else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_java_getter_setter_type_vec(String);
        }else if (in->val_type == VALUE_TYPE_BOOL){
            tp_gen_java_getter_setter_type(boolean);
        }else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_java_getter_setter_type_vec(boolean);
        }else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  public %s get%c%s(){return %s;}\n",in->ref_type, toupper(in->name[0]), (in->name+1), in->name);
            fprintf(out, "  public void set%c%s(%s param){%s = param;}\n",toupper(in->name[0]), (in->name+1), in->ref_type, in->name);
        }else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  public List<%s> get%c%s(){return %s;}\n",in->ref_type, toupper(in->name[0]), (in->name+1), in->name);
            fprintf(out, "  public void set%c%s(List<%s> param){%s = param;}\n",toupper(in->name[0]), (in->name+1), in->ref_type, in->name);
        }
    }

    return 0;
}
static int tp_gen_java_data_member(FILE *out, struct item_node *n)
{
    struct item_node *in = n;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "  private byte %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            fprintf(out, "  private byte[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "  private byte %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            fprintf(out, "  private byte[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "  private byte %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            fprintf(out, "  private byte[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "  private short %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            fprintf(out, "  private short[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "  //The length of the field is 2 bytes\n");
            fprintf(out, "  private int %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            fprintf(out, "  //The length of every element is 2 bytes\n");
            fprintf(out, "  private int[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "  private int %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            fprintf(out, "  private int[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "  //The length of the field is 4 bytes\n");
            fprintf(out, "  private long %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            fprintf(out, "  //The length of every element is 4 bytes\n");
            fprintf(out, "  private long[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "  private long %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            fprintf(out, "  private long[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "  private long %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            fprintf(out, "  private long[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "  private String %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_STR_VEC){
            fprintf(out, "  private String[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "  private int %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT_VEC){
            fprintf(out, "  private int[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "  private long %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_LONG_VEC){
            fprintf(out, "  private long[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "  private short %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            fprintf(out, "  private short[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "  private char %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            fprintf(out, "  private char[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "  private double %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            fprintf(out, "  private double[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "  private float %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            fprintf(out, "  private float[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "  private boolean %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            fprintf(out, "  private boolean[] %s;\n", in->name);
        }else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "  private %s %s;\n", in->ref_type, in->name);
        }else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "  private List<%s> %s;\n", in->ref_type, in->name);
        }
    }
}
#define tp_gen_java_proto_impl_serialize_vec(type) \
    do{\
        fprintf(out, "\n    // Write size firstly\n");\
        fprintf(out, "    int %s_size = %s.length;\n", in->name, in->name);\
        fprintf(out, "    oa.writeInt(%s_size);\n", in->name);\
        fprintf(out, "    // Write element iteratively\n");\
        fprintf(out, "    for(int i=0; i < %s_size; i++){\n", in->name);\
        fprintf(out, "      oa.write" #type "(%s[i]);\n", in->name);\
        fprintf(out, "    }\n\n");\
    } while(0);

#define tp_gen_java_proto_impl_deserialize_vec(type, datatype) \
    do{\
        fprintf(out, "\n    // Read size firstly\n");\
        fprintf(out, "    int %s_size = ia.readInt();\n", in->name);\
        fprintf(out, "    %s = new " #datatype "[%s_size];\n", in->name, in->name);\
        fprintf(out, "    // Read element iteratively\n");\
        fprintf(out, "    for(int i=0; i < %s_size; i++){\n", in->name);\
        fprintf(out, "      %s[i] = ia.read" #type "();\n", in->name);\
        fprintf(out, "    }\n\n");\
    } while(0);

static int tp_gen_java_proto_impl_serialize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "  public void serialize(OutputArchive oa)throws IOException{\n");
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "    oa.writeByte(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_java_proto_impl_serialize_vec(Byte);
        }else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "    oa.writeByte(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_java_proto_impl_serialize_vec(Byte);
        }else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "    oa.writeByte(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_java_proto_impl_serialize_vec(Byte);
        }else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "    oa.writeShort(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_java_proto_impl_serialize_vec(Short);
        }else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "    oa.writeShort(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_java_proto_impl_serialize_vec(Short);
        }else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "    oa.writeInt(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_java_proto_impl_serialize_vec(Int);
        }else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "    oa.writeUInt(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_java_proto_impl_serialize_vec(UInt);
        }else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "    oa.writeLong(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_java_proto_impl_serialize_vec(Long);
        }else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "    oa.writeLong(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_java_proto_impl_serialize_vec(Long);
        }else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "    oa.writeShort(%s);\n", in->name);
        }else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_java_proto_impl_serialize_vec(Short);
        } else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "    oa.writeInt(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_java_proto_impl_serialize_vec(Int);
        } else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "    oa.writeLong(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_java_proto_impl_serialize_vec(Long);
        } else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "    oa.writeChar(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_java_proto_impl_serialize_vec(Char);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "    oa.writeString(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_java_proto_impl_serialize_vec(String);
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "    oa.writeDouble(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_java_proto_impl_serialize_vec(Double);
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "    oa.writeFloat(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_java_proto_impl_serialize_vec(Float);
        } else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "    oa.writeBool(%s);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_java_proto_impl_serialize_vec(Bool);
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "    %s.serialize(oa);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n    // Write size firstly\n");
            fprintf(out, "    int %s_size = %s.size();\n", in->name, in->name);
            fprintf(out, "    oa.writeInt(%s_size);\n", in->name);
            fprintf(out, "    // Write element iteratively\n");
            fprintf(out, "    for(int i=0; i < %s_size; i++){\n", in->name);
            fprintf(out, "      %s.get(i).serialize(oa);\n", in->name);
            fprintf(out, "    }\n\n");
        }
    }
    fprintf(out, "  }\n");
 
}
static int tp_gen_java_proto_impl_deserialize(FILE *out, struct protocol *p)
{
    struct item_node *in = NULL;
    fprintf(out, "  public void deserialize(InputArchive ia)throws IOException{\n");
    in = p->head;
    for (; in != NULL; in=in->next){
        if (in->val_type == VALUE_TYPE_BYTE){
            fprintf(out, "    %s = ia.readByte();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BYTE_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Byte, byte);
        } else if (in->val_type == VALUE_TYPE_INT8){
            fprintf(out, "    %s = ia.readByte();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT8_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Byte, byte);
        } else if (in->val_type == VALUE_TYPE_UINT8){
            fprintf(out, "    %s = ia.readByte();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT8_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Byte, byte);
        } else if (in->val_type == VALUE_TYPE_INT16){
            fprintf(out, "    %s = ia.readShort();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT16_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Short, short);
        } else if (in->val_type == VALUE_TYPE_UINT16){
            fprintf(out, "    %s = ia.readShort();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT16_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Short, int);
        } else if (in->val_type == VALUE_TYPE_INT32){
            fprintf(out, "    %s = ia.readInt();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT32_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Int, int);
        } else if (in->val_type == VALUE_TYPE_UINT32){
            fprintf(out, "    %s = ia.readInt();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT32_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Int, long);
        } else if (in->val_type == VALUE_TYPE_INT64){
            fprintf(out, "    %s = ia.readLong();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT64_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Long, long);
        } else if (in->val_type == VALUE_TYPE_UINT64){
            fprintf(out, "    %s = ia.readLong();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_UINT64_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Long, long);
        } else if (in->val_type == VALUE_TYPE_INT){
            fprintf(out, "    %s = ia.readInt();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_INT_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Int, int);
        } else if (in->val_type == VALUE_TYPE_SHORT){
            fprintf(out, "    %s = ia.readShort();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_SHORT_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Short, short);
        } else if (in->val_type == VALUE_TYPE_LONG){
            fprintf(out, "    %s = ia.readLong();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_LONG_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Long, long);
        } else if (in->val_type == VALUE_TYPE_CHAR){
            fprintf(out, "    %s = ia.readChar();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_CHAR_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Char, char);
        } else if (in->val_type == VALUE_TYPE_STR){
            fprintf(out, "    %s = ia.readString();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_STR_VEC){
            tp_gen_java_proto_impl_deserialize_vec(String, String);
        } else if (in->val_type == VALUE_TYPE_DOUBLE){
            fprintf(out, "    %s = ia.readDouble();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_DOUBLE_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Double, double);
        } else if (in->val_type == VALUE_TYPE_FLOAT){
            fprintf(out, "    %s = ia.readFloat();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_FLOAT_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Float, float);
        } else if (in->val_type == VALUE_TYPE_BOOL){
            fprintf(out, "    %s = ia.readBool();\n", in->name);
        } else if (in->val_type == VALUE_TYPE_BOOL_VEC){
            tp_gen_java_proto_impl_deserialize_vec(Bool, bool);
        } else if (in->val_type == VALUE_TYPE_REF){
            fprintf(out, "    %s.deserialize(ia);\n", in->name);
        } else if (in->val_type == VALUE_TYPE_REF_VEC){
            fprintf(out, "\n    // Read size firstly\n");
            fprintf(out, "    int %s_size = ia.readInt();\n", in->name);
            fprintf(out, "    %s = new ArrayList<%s>();\n", in->name, in->ref_type);
            fprintf(out, "    // Read element iteratively\n");
            fprintf(out, "    for(int i=0; i < %s_size; i++){\n", in->name);
            fprintf(out, "      %s refobj = new %s();\n", in->ref_type, in->ref_type);
            fprintf(out, "      refobj.deserialize(ia);\n");
            fprintf(out, "      %s.add(refobj);\n", in->name);
            fprintf(out, "    }\n\n");
        }
    }
    fprintf(out, "  }\n");
}

static int tp_gen_java_import_path(FILE *out)
{
    // Generate include files
    fprintf(out, "\nimport java.util.List;\n");
    fprintf(out, "import java.util.ArrayList;\n");
    fprintf(out, "import com.haska.tpbuff.*;\n");
    fprintf(out, "import java.io.IOException;\n");

    return 0;
}

static int tp_gen_java_proto_decl(const char *save_dir, struct protocol *p)
{
    char *tmp_dir = NULL;
    char *old_dir = NULL;
    FILE *javafile = NULL;

    // concat path
    if (!save_dir || save_dir[0] == '\0'){
        tmp_dir = tp_concat_path("./", p->name);
    }else{
        tmp_dir = tp_concat_path(save_dir, p->name);
    }

    old_dir = tmp_dir;
    tmp_dir = tp_concat_path(old_dir, "java");
    free(old_dir);
    old_dir = NULL;

    char *last_seperator = strrchr(tmp_dir, '/');
    if (last_seperator){
        *last_seperator = '.';
    }

    // Create file for name.java
    javafile = fopen(tmp_dir, "w+");
    if (!javafile){
        fprintf(stderr, "Create the hdr file(%s) failed\n", tmp_dir);
        free(tmp_dir);
        return -1;
    }
    // Create file for name.tpp.cpp
    free(tmp_dir);

    // Generate file header
    fprintf(javafile, "/// Generated by tpp compiler. Don't edit!\n");
    fprintf(javafile, "package com.haska.tpbuff.generated;\n");

    // Generate import file
    if (tp_gen_java_import_path(javafile) != 0){
        // Generate include file failed
        fclose(javafile);
        return -1;
    }

    //Generate class header
    fprintf(javafile, "public class %s implements Command {\n", p->name);
    tp_gen_java_data_member(javafile, p->head);
    tp_gen_java_getter_setter(javafile, p->head);
    fprintf(javafile, "\n  // constructor\n");
    fprintf(javafile, "  public %s(){\n  }\n", p->name);
    tp_gen_java_proto_impl_serialize(javafile, p);
    tp_gen_java_proto_impl_deserialize(javafile, p);
    fprintf(javafile, "}\n\n");

    return 0;
}

int tp_gen_java_code(const char *save_dir, const char *file)
{
    struct protocol *proto, *cur_p;

    if (!file || file[0] == '\0'){
        fprintf(stderr, "Can't parse invalid file name\n");
        return -1;
    }

    cur_p = proto = NULL;
    if (tpp_protocol_parse(file) != 0){
        fprintf(stderr, "Parse the protocol failed\n");
        return -1;
    }
    // Generate Protocol
    proto = tpp_protocol_tab_get();
    for (cur_p = proto; cur_p != NULL; cur_p = cur_p->next){
        tp_gen_java_proto_decl(save_dir, cur_p);
    }

    tpp_protocol_tab_destroy();
    tpp_destroy_inc_file();

    return 0;
}

