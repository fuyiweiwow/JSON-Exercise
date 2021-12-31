#ifndef LFJSON_H__
#define LFJSON_H__

//定义json的6种数据类型
// null false,true,number,string,array,object

typedef enum {
    LFJSON_NULL,
    LFJSON_FALSE,
    LFJSON_TRUE,
    LFJSON_NUMBER,
    LFJSON_STRING,
    LFJSON_ARRAY,
    LFJSON_OBJECT
} lfjson_type;

//返回结果
enum {
    LF_PARSE_OK = 0,
    LF_PARSE_EXPECT_VALUE,
    LF_PARSE_INVALID_VALUE,
    LF_PARSE_ROOT_NOT_SINGULAR,
};

//json 节点结构
typedef struct {
    lfjson_type type;
} lfjson_node;

//参数传递结构
typedef struct lfjson
{
    const char* json;
} lf_context;


//summary：将json文本转换成node 结构
//@param node: 输出node
//@param json: 输入json文本
//@return: 操作结果 
int parse(lfjson_node* node,const char* json);

lfjson_type get_node_type(const lfjson_node* node);

#endif