#MySQL-udf-microtime

This is a user defined function (UDF) for MySQL to add a microtime function.

It is based on Vincent Sweeney's "[udf_microtime][micro]" UDF
And Baron Schwartz' "[now_usec][usec]" UDF.

All Feedback is appreciated.


Feel free to contact me on [Twitter]


## Installation

1. First you will need the `mysql_udf_microtime.so` file, which you can either compile yourself or download.

 =================
 ### Compiling

 <pre>g++ -Wall -bundle -bundle_loader /usr/local/mysql/bin/mysqld -o mysql_udf_microtime.so `/usr/local/mysql/bin/mysql_config --cflags` mysql_udf_microtime.c</pre>

 ### Downloading

 You can download the precompiled `mysql_udf_microtime.so` UDF file [Here][download], just click `Raw`.
 
 =================

2. Once you have `mysql_udf_microtime.so` you need to find out where your mysql installation's plugin directory is located:
    
   <pre>mysql> SHOW VARIABLES LIKE 'plugin_dir';</pre>
    
    
3. Move `mysql_udf_microtime.so` into the plugin_dir.


4. Create a function named "microtime" pointing to the correct SONAME:

   <pre>mysql> CREATE FUNCTION microtime RETURNS REAL SONAME 'mysql_udf_microtime.so';</pre>


5.  Test that the function is working:

   <pre>mysql> SELECT microtime();
+-------------------+
| microtime()       |
+-------------------+
| 1381691615.417104 |
+-------------------+
1 row in set (0.00 sec)</pre>


## Uninstalling

The function is located in the default `mysql` database, within the `func` table.
Delete the corresponding entry there named "microtime" and restart your mysql installation.


[micro]:https://bitbucket.org/vinces/udf-microtime/src/bd48df4d4020/udf_microtime.c
[usec]:http://www.xaprb.com/blog/2007/10/30/how-i-built-the-now_usec-udf-for-mysql/
[download]:https://github.com/CarnotInteractive/MySQL-udf-microtime/blob/master/mysql_udf_microtime.so
[twitter]: http://twitter.com/jo_shadow
