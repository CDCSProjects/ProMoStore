#/bin/bash
LD_LIBRARY_PATH=/lib/x86_64-linux-gnu/debug
#This uses the static duckdb libraries, you may also link with the shared library instead.
#Change the include and library paths to wherever duckdb is stored on your system 
#Build with debug symbols
g++ -std=c++17 -g -O2 -I./ -I../SciFi/duckdb/src/include parser.cpp -L. -o 3didParser -L../SciFi/duckdb/staticlibs -lduckdb_static -lduckdb_re2 -lduckdb_fmt -lduckdb_hyperloglog -limdb -lduckdb_miniz -lduckdb_pg_query -lduckdb_sqlite3 -lsqlite3_api_wrapper_static -ltest_helpers -lduckdb_utf8proc -lparquet_extension -lduckdb_fastpforlib -lduckdb_mbedtls -lduckdb_fsst -ljemalloc_extension -lpthread -ldl -lz -lcurl -lcurlpp -lsnappy

