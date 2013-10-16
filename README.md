#MySQL-udf-microtime

### Microtime in MySQL 5.5.*

A [User-Defined Function][UDF] For Mysql 5.5.* that adds microtime support.

<a href="http://i.imgur.com/GMw5tit.png"><img src="http://i.imgur.com/GMw5tit.png"/></a>

### It is an order of magnitude faster than SYSDATE()

<a href="http://i.imgur.com/tR4hjD3.png"><img src="http://i.imgur.com/tR4hjD3.png"/></a>


## About

**MySQL-udf-microtime** is based on UDFs "[udf_microtime][micro]" by Vincent Sweeney
And "[now_usec][usec]" by Baron Schwartz, With additional thanks to [Justin Swanhart][swanhart].

All Feedback is appreciated - Feel free to contact me on [Twitter].



## Dependencies

1. [Mysql 5.5.*][mysql]
2. g++ compiler (included in xcode via additional 'Command Line Tools' download)


## Installation

1. First you will need the `mysql_udf_microtime.so` file, which you can either **compile** yourself or **download**:

 =================
 ### Compile (on mac, should work on linux as well)

 Downloade the source file `mysql_udf_microtime.c`,  `cd` into its directory and then run:

 <pre>g++ -Wall -bundle -bundle_loader /usr/local/mysql/bin/mysqld -o mysql_udf_microtime.so `/usr/local/mysql/bin/mysql_config --cflags` mysql_udf_microtime.c</pre>

 `mysql_udf_microtime.so` should be created.
 
 If you run into problems mace sure you have g++ and 

 ### Download

 You can download the precompiled `mysql_udf_microtime.so` UDF file [Here][download].
 
 =================

2. Once you have `mysql_udf_microtime.so` you need to find out where your mysql installation's plugin directory is located:
    
   <pre>mysql> SHOW VARIABLES LIKE 'plugin_dir';</pre>
    
    
3. Move `mysql_udf_microtime.so` into the plugin_dir.


4. Create a function named "microtime" pointing to the correct SONAME:

   <pre>mysql> CREATE FUNCTION microtime RETURNS REAL SONAME 'mysql_udf_microtime.so';</pre>


5.  Test that the function is working:

   <pre>mysql> SELECT MICROTIME();
+-------------------+
| microtime()       |
+-------------------+
| 1381691615.417104 |
+-------------------+
1 row in set (0.00 sec)</pre>


## Uninstalling

   <pre>mysql> DROP FUNCTION microtime;</pre>

[UDF]:http://dev.mysql.com/doc/refman/5.5/en/create-function-udf.html
[mysql]:http://dev.mysql.com/downloads/mysql/
[micro]:https://bitbucket.org/vinces/udf-microtime/src/bd48df4d4020/udf_microtime.c
[usec]:http://www.xaprb.com/blog/2007/10/30/how-i-built-the-now_usec-udf-for-mysql/
[swanhart]:http://swanhart.livejournal.com/116981.html
[download]:https://github.com/CarnotInteractive/MySQL-udf-microtime/raw/master/mysql_udf_microtime.so
[twitter]: http://twitter.com/jo_shadow
