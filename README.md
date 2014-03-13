#MySQL-udf-microtime

### Microtime in MySQL 5.5.*

A [User-Defined Function][UDF] For Mysql 5.5.* that adds microtime support.

<a href="http://i.imgur.com/GMw5tit.png"><img src="http://i.imgur.com/GMw5tit.png"/></a>

### How does it scale up to other MySQL time functions?

100,000,000 executions with `BENCHMARK()` on 2.7GHz Intel Core i5 with Local MySQL 5.5.29:

	SELECT BENCHMARK(100000000,NOW()); -- 1.64s
	SELECT BENCHMARK(100000000,UNIX_TIMESTAMP()); -- 1.81s
	SELECT BENCHMARK(100000000,MICROTIME()); -- 30.1s
	SELECT BENCHMARK(100000000,SYSDATE()); -- 148s


## About

**MySQL-udf-microtime** is based on UDFs "[udf_microtime][micro]" by Vincent Sweeney
And "[now_usec][usec]" by Baron Schwartz, With additional thanks to [Justin Swanhart][swanhart].

All Feedback is appreciated - Feel free to contact me on [Twitter].




## Download

 You can download the precompiled `mysql_udf_microtime.so` UDF file:
 
 * [Download For Mac][download-mac]
 * [Download For Linux][download-lin]
 
 
## Install

1. Once you have `mysql_udf_microtime.so` you need to find out where your mysql installation's plugin directory is located:
    
   <pre>mysql> SHOW VARIABLES LIKE 'plugin_dir';</pre>
    
    
2. Move `mysql_udf_microtime.so` into the plugin_dir.


3. Create a function named "microtime" pointing to the correct SONAME:

   <pre>mysql> CREATE FUNCTION microtime RETURNS REAL SONAME 'mysql_udf_microtime.so';</pre>


4.  Test that the function is working:

   <pre>mysql> SELECT MICROTIME();
+-------------------+
| microtime()       |
+-------------------+
| 1381691615.417104 |
+-------------------+
1 row in set (0.00 sec)</pre>
 


## Compile From Source

 You can Downloade the source file `mysql_udf_microtime.c` and compile it yourself:

#### Mac Dependencies
 1. [Mysql 5.5.*][mysql]
 2. g++ compiler (included in xcode via additional 'Command Line Tools' download)

#### Compiling on Mac

 Download the source file `mysql_udf_microtime.c`,  `cd` into its directory and then run:

<pre>g++ -Wall -bundle -bundle_loader /usr/local/mysql/bin/mysqld -o mysql_udf_microtime.so `/usr/local/mysql/bin/mysql_config --cflags` mysql_udf_microtime.c</pre>

 `mysql_udf_microtime.so` should be created in your current directory.

========= 

#### Linux Dependencies 
 1. [Mysql 5.5.*][mysql]
 2. gcc compiler

#### Compiling on Linux

 Download the source file `mysql_udf_microtime.c`,  `cd` into its directory and then run:
 
 <pre>gcc -fPIC -Wall -I/usr/include/mysql -shared -o mysql_udf_microtime.so mysql_udf_microtime.c</pre>
 
 `mysql_udf_microtime.so` should be created in your current directory.



========= 

## Uninstalling

 1. In Mysql run: <pre>mysql> DROP FUNCTION microtime;</pre>
 2. delete the `mysql_udf_microtime.so` from the plugin_dir (the one from the installation)

[UDF]:http://dev.mysql.com/doc/refman/5.5/en/create-function-udf.html
[mysql]:http://dev.mysql.com/downloads/mysql/
[micro]:https://bitbucket.org/vinces/udf-microtime/src/bd48df4d4020/udf_microtime.c
[usec]:http://www.xaprb.com/blog/2007/10/30/how-i-built-the-now_usec-udf-for-mysql/
[swanhart]:http://swanhart.livejournal.com/116981.html
[download-mac]:https://github.com/CarnotInteractive/MySQL-udf-microtime/raw/master/compiled_mac/mysql_udf_microtime.so
[download-lin]:https://github.com/CarnotInteractive/MySQL-udf-microtime/raw/master/compiled_linux/mysql_udf_microtime.so
[twitter]: http://twitter.com/jo_shadow


========= 

## License

This UDF is open source and free to use for anyone under the MIT license.
