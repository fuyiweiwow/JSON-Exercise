#include "lfjson.h"
#include <assert.h>
#include <stddef.h>

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)


//跳过空白
static void parse_ws(lf_context* ctx){
    const char* p = ctx->json;
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    ctx->json = p;
}

static int after_check(lf_context* ctx,lfjson_node* node,int val)
{
    const char* p = ctx->json;
    if(*p == '\0')
    {
        node->type = val;
        return LF_PARSE_OK;
    }

    if(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
    {
        parse_ws(ctx);
        if(*ctx->json != '\0')
            return LF_PARSE_ROOT_NOT_SINGULAR;
    }

     return LF_PARSE_INVALID_VALUE;
}


//处理空值
static int parse_null(lf_context* ctx,lfjson_node* node){
    EXPECT(ctx,'n');
    if(ctx->json[0] != 'u' || ctx->json[1] != 'l' || ctx->json[2] != 'l')
        return LF_PARSE_INVALID_VALUE;
    ctx->json += 3;

    return after_check(ctx,node,LFJSON_NULL);
}

static int parse_false(lf_context* ctx,lfjson_node* node){
    EXPECT(ctx,'f');
    if(ctx->json[0] != 'a' || ctx->json[1] != 'l' || ctx->json[2] != 's' || ctx->json[3] != 'e')
        return LF_PARSE_INVALID_VALUE;
    ctx->json += 4;

    return after_check(ctx,node,LFJSON_FALSE);
}

static int parse_true(lf_context* ctx,lfjson_node* node){
    EXPECT(ctx,'t');
    if(ctx->json[0] != 'r' || ctx->json[1] != 'u' || ctx->json[2] != 'e')
        return LF_PARSE_INVALID_VALUE;
    ctx->json += 3;

    return after_check(ctx,node,LFJSON_TRUE);
}


//处理json中的值类型 value = null/false/true,返回识别的类型
static int parse_value(lf_context* ctx,lfjson_node* node){
    switch(*ctx->json){
        case 'n':return parse_null(ctx,node); 
        case 'f':return parse_false(ctx,node);
        case 't':return parse_true(ctx,node);
        case '\0':return LF_PARSE_EXPECT_VALUE;
        default: return LF_PARSE_INVALID_VALUE;
    }
}


/*
    json text 格式  ws value ws
*/
int parse(lfjson_node* node,const char* json){
    lf_context ctx;
    assert(node != NULL);//断言,不满足要求会直接退出程序
    ctx.json = json;
    node->type = LFJSON_NULL;
    parse_ws(&ctx);
    return parse_value(&ctx,node);
}

lfjson_type get_node_type(const lfjson_node* node){
    assert(node != NULL);
    return node->type;
}