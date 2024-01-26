#!/bin/bash

export CPLUS_INCLUDE_PATH=./:../SciFi/rocksdb/include/:../SciFi/duckdb/src/include:../SciFi/
#export LIBRARY_PATH=./:../SciFi/rocksdb/:../SciFi/duckdb/staticlibs/
#g++ -std=c++17 $(pkg-config --cflags gtkmm-3.0) ../SciFi/framework/src/assetstore.cpp mainwindow.cpp main.cpp ../SciFi/backend/src/duckstore.cpp ../SciFi/framework/src/metadata.cpp ../SciFi/backend/src/rocksstore.cpp ../SciFi/framework/src/storage.cpp  -L. -o SciFi  -lduckdb_static -lduckdb_re2 -lduckdb_fmt -lduckdb_hyperloglog -limdb -lduckdb_miniz -lduckdb_pg_query -lduckdb_sqlite3 -lsqlite3_api_wrapper_static -ltest_helpers -lduckdb_utf8proc -lparquet_extension -lduckdb_fastpforlib -lduckdb_mbedtls -lduckdb_fsst -ljemalloc_extension -lrocksdb -lpthread -ldl -lz -lcurl -lcurlpp -lsnappy $(pkg-config --libs gtkmm-3.0)

export LIBRARY_PATH=./:../SciFi/
g++ -std=c++17 -g $(pkg-config --cflags gtkmm-3.0) codewindow.cpp filterwindow.cpp assistants.cpp mainwindow.cpp main.cpp -L. -o SciFi  -lscifi -ltinyxml2 $(pkg-config --libs gtkmm-3.0)
