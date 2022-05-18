#include "../include/tinyjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */


/* ws = *(%x20 / %x09 / %x0A / %x0D) */
static void json_parse_whitespace(json_context *c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

/* parse "null" "true" "false" */
static int lept_parse_literal(json_context *c, json_value *v, const char *s, json_type type) {
    const char *p = c->json;
    while (*s != '\0') {
        if (*p == '\0' || *p != *s) {
            return JSON_PARSE_INVALID_VALUE;
        }
        p++;
        s++;
    }
    c->json = p;
    v->type = type;
    return JSON_PARSE_OK;
}


/* value = null / false / true */
/* 提示：下面代码没处理 false / true，将会是练习之一 */
static int json_parse_value(json_context *c, json_value *v) {
    switch (*c->json) {
        case 'n':  return lept_parse_literal(c, v, "null", JSON_NULL);
        case 't':  return lept_parse_literal(c, v, "true", JSON_TRUE);
        case 'f':  return lept_parse_literal(c, v, "false", JSON_FALSE);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        default:   return JSON_PARSE_INVALID_VALUE;
    }
}

int json_parse(json_value *v, const char *json) {
    json_context c;
    int ret;
    assert(v != NULL);
    c.json = json;
    v->type = JSON_NULL;
    json_parse_whitespace(&c);
    if ((ret = json_parse_value(&c, v)) == JSON_PARSE_OK) {
        json_parse_whitespace(&c);
        if (*c.json != '\0')
            ret = JSON_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

json_type json_get_type(const json_value *v) {
    assert(v != NULL);
    return v->type;
}

double json_get_number(const json_value* v) {
    assert(v != NULL && v->type == JSON_NUMBER);
    return v->n;
}



