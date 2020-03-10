#if defined(__GNUC__) && __GNUC__ >= 8
#define DISABLE_WCAST_FUNCTION_TYPE _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wcast-function-type\"")
#define DISABLE_WCAST_FUNCTION_TYPE_END _Pragma("GCC diagnostic pop")
#else
#define DISABLE_WCAST_FUNCTION_TYPE
#define DISABLE_WCAST_FUNCTION_TYPE_END
#endif
#include <cups/cups.h>
#include <cups/ppd.h>
#include <cups/ipp.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <stdio.h>

using namespace std;

namespace methods{
	//methods

	/**
	 * Return printer infos. If passed name is invalid, this method will return default printer infos
	 * @param printer printer name
	 */
	cups_dest_t* getPrinter(const char*);


	/**
	 * Return job status from job status string
	 * @param status IPP_JOB status constant
	 * @return status string
	 */
	const char* getJobStatusString(int);

	/**
	 * It has the same behaviour of system() but returns command's output string
	 * @pararm cmd command to execute
	 * @return output string
	 */
	string exec(const char*);

	/**
	 * Transform a string to lowercase
	 * @param data string to transform
	 * @return string lowercased
	 */
	string strtolower(string);

	/**
	 * Transform a char* to lowercase
	 * @param data char* to transform
	 * @return char* string lowercased
	 */
	const char* strtolower(char*);
}

