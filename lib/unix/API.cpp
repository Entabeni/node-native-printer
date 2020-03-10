#include "API.hpp"

using namespace methods;

namespace API
{
CALLBACK(printerInfo)
{

	ISOLATE;

	if (args.Length() < 1)
	{
		THROW_EXCEPTION("Too few arguments");
		return;
	}

	String::Utf8Value printer(args[0]->ToString());

	cups_dest_t *dest = getPrinter(*printer);

	if (dest == NULL)
	{
		THROW_EXCEPTION("Printer not found or error retrieving printer");
		return;
	}

	cups_job_t *printerJobs;
	int num_jobs = cupsGetJobs(&printerJobs, dest->name, 0, CUPS_WHICHJOBS_ALL);

	Local<Object> result = Object::New(isolate);
	Local<Object> jobs = Array::New(isolate);
	Local<Object> CUPSOptions = Object::New(isolate);

	for (int i = 0; i < dest->num_options; i++)
	{
		CUPSOptions->Set(UTF8_STRING(dest->options[i].name), UTF8_STRING(dest->options[i].value));
	}

	char id[5], priority[5], size[5];

	for (int i = 0; i < num_jobs; i++)
	{
		Local<Object> job = Object::New(isolate);

		sprintf(id, "%d", printerJobs[i].id);
		sprintf(priority, "%d", printerJobs[i].priority);
		sprintf(size, "%d", printerJobs[i].size);

		job->Set(UTF8_STRING("completed_time"), UTF8_STRING(httpGetDateString(printerJobs[i].completed_time)));
		job->Set(UTF8_STRING("creation_time"), UTF8_STRING(httpGetDateString(printerJobs[i].creation_time)));
		job->Set(UTF8_STRING("format"), UTF8_STRING(printerJobs[i].format));
		job->Set(UTF8_STRING("id"), UTF8_STRING(id));
		job->Set(UTF8_STRING("priority"), UTF8_STRING(priority));
		job->Set(UTF8_STRING("processing_time"), UTF8_STRING(httpGetDateString(printerJobs[i].processing_time)));
		job->Set(UTF8_STRING("size"), UTF8_STRING(size));
		job->Set(UTF8_STRING("status"), UTF8_STRING(getJobStatusString(printerJobs[i].state)));
		job->Set(UTF8_STRING("title"), UTF8_STRING(printerJobs[i].title));
		job->Set(UTF8_STRING("user"), UTF8_STRING(printerJobs[i].user));

		jobs->Set(i, job);
	}

	cupsFreeJobs(num_jobs, printerJobs);
	free(dest);
	// result->Set(UTF8_STRING("infos"), infos);
	result->Set(UTF8_STRING("jobs"), jobs);
	result->Set(UTF8_STRING("CUPSOptions"), CUPSOptions);

	args.GetReturnValue().Set(result);
}

CALLBACK(print)
{
	using namespace std;

	ISOLATE;
	if (args.Length() < 3)
	{
		THROW_EXCEPTION("Too few arguments");
		return;
	}

	string printer(*(String::Utf8Value(args[0]->ToString())));
	string file(*(String::Utf8Value(args[1]->ToString())));
	string options(*(String::Utf8Value(args[2]->ToString())));

	cups_dest_t *dest = getPrinter(printer.c_str());
	printer = string(dest->name);

	string cmd = "lp -d " + printer + " " + file + " " + options;

	string result = exec(cmd.c_str());

	args.GetReturnValue().Set(UTF8_STRING(result.c_str()));
	free(dest);
}
} // namespace API
