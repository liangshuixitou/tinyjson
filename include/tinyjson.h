#ifndef TINYJSON_H__
#define TINYJSON_H__

typedef enum { JSON_NULL, JSON_FALSE, JSON_TRUE, JSON_NUMBER, JSON_STRING, JSON_ARRAY, JSON_OBJECT } json_type;
typedef struct {
    double n;
    json_type type;
} json_value;


enum {
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGULAR
};

typedef struct {
    const char *json;
} json_context;

// parse json-string
int json_parse(json_value *v, const char *json);

// get the type from node
json_type json_get_type(const json_value *v);


// get the number from node
double json_get_number(const json_value* v);


#endif /* TINYJSON_H__ */