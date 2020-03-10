#include <node.h>

#include "methods.hpp"

using namespace v8;

#define CALLBACK(name) void name(const FunctionCallbackInfo<Value> &args)
#define ISOLATE v8::Isolate *isolate = v8::Isolate::GetCurrent()
#define THROW_EXCEPTION(msg) isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate, msg) /*.FromMaybe(v8::Local<v8::String>())*/))
#define UTF8_STRING(str) String::NewFromUtf8(isolate, str)
#define S_STR(str) isolate, str->ToString(isolate->GetCurrentContext()).FromMaybe(v8::Local<v8::String>())
//Method declarations
namespace API
{

/**
	 * Returns printer infos with active jobs
	 * @param printer printer name; if it's null it'll be used default printer name
	 * @return object containing infos
	 */
CALLBACK(printerInfo);

/**
	 * Prints file or a plain text passed directly to this method.
	 * If a text is passed to JS function, it will be created a txt file from where to print text.
	 * @param filename
	 */
CALLBACK(print);
} // namespace API

using namespace API;

void init(Local<Object> exports)
{
	NODE_SET_METHOD(exports, "printerInfo", printerInfo);
	NODE_SET_METHOD(exports, "print", print);
}

// NODE_MODULE(NODE_GYP_MODULE_NAME, init)
