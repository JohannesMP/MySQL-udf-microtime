#MySQL-udf-microtime

This is a user defined function (UDF) for MySQL to add a microtime function.

It is based on Vincent Sweeney's "[udf_microtime][micro]" UDF
And Baron Schwartz' "[now_usec][usec]" UDF.

## Installation

1. First you will need the mysql_udf_microtime.so file, which you can either compile yourself or download.

### Compiling

    g++ -Wall -bundle -bundle_loader /usr/local/mysql/bin/mysqld -o mysql_udf_microtime.so `/usr/local/mysql/bin/mysql_config --cflags` mysql_udf_microtime.c

### Downloading

You can download the precompiled UDF .so file [Here][download]!

=================

2. Once you have mysql_udf_microtime.so you need to find out where your mysql installation's plugin directory is located:
    
    mysql>SHOW VARIABLES LIKE 'plugin_dir';
    
    
3. Move mysql_udf_microtime.so into the plugin_dir.


4. create a function named "microtime" pointing to the correct SONAME:

    mysql>CREATE FUNCTION microtime RETURNS REAL SONAME 'mysql_udf_microtime.so';


5.  test that the function is working:

    mysql>SELECT microtime();


## uninstalling the function

the function is located in the mysql database in the func table. Delete the corresponding entry there named "microtime" and restart your mysql installation.


[micro]:https://bitbucket.org/vinces/udf-microtime/src/bd48df4d4020/udf_microtime.c
[usec]:http://www.xaprb.com/blog/2007/10/30/how-i-built-the-now_usec-udf-for-mysql/
[download]:https://github.com/CarnotInteractive/MySQL-udf-microtime/raw/master/mysql_udf_microtime.so
