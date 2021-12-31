#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lfjson.h"

/*
    单元测试
*/ 

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)\

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")



static void  test_parse_null(){
    lfjson_node node;
    node.type = LFJSON_TRUE;
    EXPECT_EQ_INT(LF_PARSE_OK,parse(&node,"null"));
    EXPECT_EQ_INT(LFJSON_NULL,get_node_type(&node));
}

static void test_parse(){

    test_parse_null();

}

int main(){

    test_parse();
    printf("%d%d (%3.2f%%) passed\n",test_pass,test_count,test_pass * 100.0 / test_count);
    return main_ret;

}

