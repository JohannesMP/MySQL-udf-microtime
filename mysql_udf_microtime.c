/*
	MySQL UDF equivalent of the PHP microtime() function
	----

	Contributor		: Johannes Peter
	Contributor Email	: johannes@carnotinteractive.com
	---
	Original Author		: Vincent Sweeney
	Original Author Email	: vince@quakenet.co.uk
	----

	Compile & Usage:
		1. get your plugin directory via the mysql console:
			mysql>SHOW VARIABLES LIKE 'plugin_dir';
		2. cd into the folder and compile the .so file with
			g++ -Wall -bundle -bundle_loader /usr/local/mysql/bin/mysqld -o mysql_udf_microtime.so `/usr/local/mysql/bin/mysql_config --cflags` mysql_udf_microtime.c
		3. move mysql_udf_microtime.so into the plugin_dir.
		4. create the function in the mysql console:
			mysql>CREATE FUNCTION microtime RETURNS REAL SONAME 'mysql_udf_microtime.so';
		5. test function in mysql console:
			mysql>SELECT MICROTIME();

*/

#include <my_global.h>
#include <my_sys.h>
#if defined(MYSQL_SERVER)
  #include <m_string.h>	/* To get strmov() */
#else
  /* when compiled as standalone */
  #include <string.h>
  #define strmov(a,b) stpcpy(a,b)
  #define bzero(a,b) memset(a,0,b)
  #define memcpy_fixed(a,b,c) memcpy(a,b,c)
#endif

#include <mysql.h>
#include <ctype.h>

#ifdef HAVE_DLOPEN

/*
 * Encapsulating UDF Functions to prevent "Can't find symbol 'microtime' in library" error.
 */

extern "C" {
	my_bool microtime_init (UDF_INIT *initid, UDF_ARGS *args, char *message);
	double microtime(
					 UDF_INIT *initid,
					 UDF_ARGS *args,
					 char *is_null,
					 char *error);
}

my_bool microtime_init (UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	initid->maybe_null = 0;
	initid->decimals = 6;

	return 0;
}

/*
 * UDF Functions
 */

double microtime (UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) < 0)
	{
		*error = 1;
		return 0.0;
	}

	return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
}

#else /* HAVE_DLOPEN */
	#error NO DLOPEN
#endif /* HAVE_DLOPEN */
