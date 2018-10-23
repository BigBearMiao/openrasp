/*
 * Copyright 2017-2018 Baidu Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "openrasp_v8.h"
#include "openrasp_log.h"

namespace openrasp
{
static void url_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    info.GetReturnValue().SetEmptyString();
    TSRMLS_FETCH();
    zval **origin_zv;
    zval *alarm_common_info = LOG_G(alarm_logger).get_common_info(TSRMLS_C);
    if (Z_TYPE_P(alarm_common_info) == IS_ARRAY &&
        zend_hash_find(Z_ARRVAL_P(alarm_common_info), ZEND_STRS("url"), (void **)&origin_zv) == SUCCESS)
    {
        v8::Isolate *isolate = info.GetIsolate();
        info.GetReturnValue().Set(zval_to_v8val(isolate, *origin_zv TSRMLS_CC));
    }
}
static void method_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    info.GetReturnValue().SetEmptyString();
    TSRMLS_FETCH();
    static const char REQUEST_METHOD[] = "REQUEST_METHOD";
    static const ulong REQUEST_METHOD_HASH = zend_get_hash_value(ZEND_STRS(REQUEST_METHOD));
    if (!PG(http_globals)[TRACK_VARS_SERVER] && !zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC))
    {
        return;
    }
    zval **value;
    if (zend_hash_quick_find(Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS(REQUEST_METHOD), REQUEST_METHOD_HASH, (void **)&value) != SUCCESS ||
        Z_TYPE_PP(value) != IS_STRING)
    {
        return;
    }
    v8::Isolate *isolate = info.GetIsolate();
    char *str = estrndup(Z_STRVAL_PP(value), Z_STRLEN_PP(value));
    if (!str)
    {
        return;
    }
    char *p = str;
    while (*p)
    {
        *p = tolower(*p);
        p++;
    }
    info.GetReturnValue().Set(NewV8String(isolate, str));
    efree(str);
}
static void querystring_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    info.GetReturnValue().SetEmptyString();
    TSRMLS_FETCH();
    static const char QUERY_STRING[] = "QUERY_STRING";
    static const ulong QUERY_STRING_HASH = zend_get_hash_value(ZEND_STRS(QUERY_STRING));
    if (!PG(http_globals)[TRACK_VARS_SERVER] && !zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC))
    {
        return;
    }
    zval **value;
    if (zend_hash_quick_find(Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS(QUERY_STRING), QUERY_STRING_HASH, (void **)&value) != SUCCESS ||
        Z_TYPE_PP(value) != IS_STRING)
    {
        return;
    }
    info.GetReturnValue().Set(zval_to_v8val(info.GetIsolate(), *value TSRMLS_CC));
}
static void appBasePath_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    info.GetReturnValue().SetEmptyString();
    TSRMLS_FETCH();
    static const char DOCUMENT_ROOT[] = "DOCUMENT_ROOT";
    static const ulong DOCUMENT_ROOT_HASH = zend_get_hash_value(ZEND_STRS(DOCUMENT_ROOT));
    if (!PG(http_globals)[TRACK_VARS_SERVER] && !zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC))
    {
        return;
    }
    zval **value;
    if (zend_hash_quick_find(Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS(DOCUMENT_ROOT), DOCUMENT_ROOT_HASH, (void **)&value) != SUCCESS ||
        Z_TYPE_PP(value) != IS_STRING)
    {
        return;
    }
    info.GetReturnValue().Set(zval_to_v8val(info.GetIsolate(), *value TSRMLS_CC));
}
static void protocol_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    info.GetReturnValue().SetEmptyString();
    TSRMLS_FETCH();
    static const char REQUEST_SCHEME[] = "REQUEST_SCHEME";
    static const ulong REQUEST_SCHEME_HASH = zend_get_hash_value(ZEND_STRS(REQUEST_SCHEME));
    if (!PG(http_globals)[TRACK_VARS_SERVER] && !zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC))
    {
        return;
    }
    zval **value;
    if (zend_hash_quick_find(Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS(REQUEST_SCHEME), REQUEST_SCHEME_HASH, (void **)&value) != SUCCESS ||
        Z_TYPE_PP(value) != IS_STRING)
    {
        return;
    }
    info.GetReturnValue().Set(zval_to_v8val(info.GetIsolate(), *value TSRMLS_CC));
}
static void remoteAddr_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    info.GetReturnValue().SetEmptyString();
    TSRMLS_FETCH();
    static const char REMOTE_ADDR[] = "REMOTE_ADDR";
    static const ulong REMOTE_ADDR_HASH = zend_get_hash_value(ZEND_STRS(REMOTE_ADDR));
    if (!PG(http_globals)[TRACK_VARS_SERVER] && !zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC))
    {
        return;
    }
    zval **value;
    if (zend_hash_quick_find(Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS(REMOTE_ADDR), REMOTE_ADDR_HASH, (void **)&value) != SUCCESS ||
        Z_TYPE_PP(value) != IS_STRING)
    {
        return;
    }
    info.GetReturnValue().Set(zval_to_v8val(info.GetIsolate(), *value TSRMLS_CC));
}
static void path_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    info.GetReturnValue().SetEmptyString();
    TSRMLS_FETCH();
    static const char REQUEST_URI[] = "REQUEST_URI";
    static const ulong REQUEST_URI_HASH = zend_get_hash_value(ZEND_STRS(REQUEST_URI));
    if (!PG(http_globals)[TRACK_VARS_SERVER] && !zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC))
    {
        return;
    }
    zval **value;
    if (zend_hash_quick_find(Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS(REQUEST_URI), REQUEST_URI_HASH, (void **)&value) != SUCCESS ||
        Z_TYPE_PP(value) != IS_STRING)
    {
        return;
    }
    v8::Isolate *isolate = info.GetIsolate();
    char *str = Z_STRVAL_PP(value);
    char *p = strchr(str, '?');
    int len = p == nullptr ? Z_STRLEN_PP(value) : p - str;
    info.GetReturnValue().Set(NewV8String(isolate, str, len));
}
static void parameter_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    TSRMLS_FETCH();
    if ((!PG(http_globals)[TRACK_VARS_GET] && !zend_is_auto_global(ZEND_STRL("_GET") TSRMLS_CC)) ||
        (!PG(http_globals)[TRACK_VARS_POST] && !zend_is_auto_global(ZEND_STRL("_POST") TSRMLS_CC)))
    {
        return;
    }
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    HashTable *GET = Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_GET]);
    for (zend_hash_internal_pointer_reset(GET); zend_hash_has_more_elements(GET) == SUCCESS; zend_hash_move_forward(GET))
    {
        char *key;
        ulong idx;
        int type;
        zval **value;
        type = zend_hash_get_current_key(GET, &key, &idx, 0);
        if (type == HASH_KEY_NON_EXISTENT ||
            zend_hash_get_current_data(GET, (void **)&value) != SUCCESS)
        {
            continue;
        }
        v8::Local<v8::Value> v8_value = zval_to_v8val(isolate, *value TSRMLS_CC);
        if (!v8_value->IsArray())
        {
            v8::Local<v8::Array> v8_arr = v8::Array::New(isolate);
            v8_arr->Set(0, v8_value);
            v8_value = v8_arr;
        }
        v8::Local<v8::Value> v8_key;
        if (type == HASH_KEY_IS_STRING)
        {
            v8_key = NewV8String(isolate, key);
        }
        else
        {
            v8_key = v8::Uint32::New(isolate, idx);
        }
        obj->Set(v8_key, v8_value);
    }
    HashTable *POST = Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_POST]);
    for (zend_hash_internal_pointer_reset(POST); zend_hash_has_more_elements(POST) == SUCCESS; zend_hash_move_forward(POST))
    {
        char *key;
        ulong idx;
        int type;
        zval **value;
        type = zend_hash_get_current_key(POST, &key, &idx, 0);
        if (type == HASH_KEY_NON_EXISTENT ||
            zend_hash_get_current_data(POST, (void **)&value) != SUCCESS)
        {
            continue;
        }
        v8::Local<v8::Value> v8_value = zval_to_v8val(isolate, *value TSRMLS_CC);
        if (!v8_value->IsArray())
        {
            v8::Local<v8::Array> v8_arr = v8::Array::New(isolate);
            v8_arr->Set(0, v8_value);
            v8_value = v8_arr;
        }
        v8::Local<v8::Value> v8_key;
        if (type == HASH_KEY_IS_STRING)
        {
            v8_key = NewV8String(isolate, key);
        }
        else
        {
            v8_key = v8::Uint32::New(isolate, idx);
        }
        v8::Local<v8::Value> v8_existed_value = obj->Get(v8_key);
        if (!v8_existed_value.IsEmpty() &&
            v8_existed_value->IsArray())
        {
            v8::Local<v8::Array> v8_arr1 = v8_existed_value.As<v8::Array>();
            int v8_arr1_len = v8_arr1->Length();
            v8::Local<v8::Array> v8_arr2 = v8_value.As<v8::Array>();
            int v8_arr2_len = v8_arr2->Length();
            v8::Local<v8::Array> v8_arr = v8::Array::New(isolate, v8_arr1_len + v8_arr2_len);
            for (int i = 0; i < v8_arr1_len; i++)
            {
                v8_arr->Set(i, v8_arr1->Get(i));
            }
            for (int i = 0; i < v8_arr2_len; i++)
            {
                v8_arr->Set(v8_arr1_len + i, v8_arr2->Get(i));
            }
            v8_value = v8_arr;
        }
        obj->Set(v8_key, v8_value);
    }
    info.GetReturnValue().Set(obj);
}
static void header_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    TSRMLS_FETCH();
    if (!PG(http_globals)[TRACK_VARS_SERVER] && !zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC))
    {
        return;
    }
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    HashTable *SERVER = Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]);
    for (zend_hash_internal_pointer_reset(SERVER); zend_hash_has_more_elements(SERVER) == SUCCESS; zend_hash_move_forward(SERVER))
    {
        char *key;
        ulong idx;
        int type;
        zval **value;
        type = zend_hash_get_current_key(SERVER, &key, &idx, 0);
        if (type != HASH_KEY_IS_STRING ||
            strncmp(key, "HTTP_", 5) != 0 ||
            zend_hash_get_current_data(SERVER, (void **)&value) != SUCCESS ||
            Z_TYPE_PP(value) != IS_STRING)
        {
            continue;
        }
        key += 5;
        char *dup_key = nullptr;
        dup_key = estrndup(key, strlen(key));
        if (!dup_key)
        {
            continue;
        }
        char *p = dup_key;
        while (*p)
        {
            if ('_' == *p)
            {
                *p = '-';
            }
            else
            {
                *p = tolower(*p);
            }
            p++;
        }
        obj->Set(NewV8String(isolate, dup_key), zval_to_v8val(isolate, *value TSRMLS_CC));
        efree(dup_key);
    }
    info.GetReturnValue().Set(obj);
}
static void body_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    info.GetReturnValue().Set(v8::ArrayBuffer::New(info.GetIsolate(), nullptr, 0, v8::ArrayBufferCreationMode::kInternalized));
    TSRMLS_FETCH();
    php_stream *stream = php_stream_open_wrapper("php://input", "rb", 0, NULL);
    if (!stream)
    {
        return;
    }
    char *contents = nullptr;
    int len = php_stream_copy_to_mem(stream, &contents, 4 * 1024, 1);
    stream->is_persistent ? php_stream_pclose(stream) : php_stream_close(stream);
    if (len <= 0 || !contents)
    {
        return;
    }
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::ArrayBuffer> arraybuffer = v8::ArrayBuffer::New(isolate, contents, MIN(len, 4 * 1024), v8::ArrayBufferCreationMode::kInternalized);
    info.GetReturnValue().Set(arraybuffer);
}
static void server_getter(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
    TSRMLS_FETCH();
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> server = v8::Object::New(isolate);
    server->Set(NewV8String(isolate, "language"), NewV8String(isolate, "php"));
    server->Set(NewV8String(isolate, "name"), NewV8String(isolate, "PHP"));
    server->Set(NewV8String(isolate, "version"), NewV8String(isolate, OPENRASP_PHP_VERSION));
#ifdef PHP_WIN32
    server->Set(NewV8String(isolate, "os"), NewV8String(isolate, "Windows"));
#else
    if (strstr(PHP_OS, "Darwin"))
    {
        server->Set(NewV8String(isolate, "os"), NewV8String(isolate, "Mac"));
    }
    else if (strstr(PHP_OS, "Linux"))
    {
        server->Set(NewV8String(isolate, "os"), NewV8String(isolate, "Linux"));
    }
    else
    {
        server->Set(NewV8String(isolate, "os"), NewV8String(isolate, PHP_OS));
    }
#endif
    info.GetReturnValue().Set(server);
}
v8::Local<v8::Object> RequestContext::New(v8::Isolate *isolate)
{
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->SetAccessor(context, NewV8String(isolate, "url"), url_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "header"), header_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "parameter"), parameter_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "path"), path_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "querystring"), querystring_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "method"), method_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "protocol"), protocol_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "remoteAddr"), remoteAddr_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "appBasePath"), appBasePath_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "body"), body_getter).IsNothing();
    obj->SetAccessor(context, NewV8String(isolate, "server"), server_getter).IsNothing();
    return obj;
}
} // namespace openrasp