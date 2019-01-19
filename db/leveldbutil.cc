// Copyright (c) 2012 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include <stdio.h>
#include "leveldb/dumpfile.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

namespace leveldb {
namespace {

class StdoutPrinter : public WritableFile {
 public:
  virtual Status Append(const Slice& data) {
    fwrite(data.data(), 1, data.size(), stdout);
    return Status::OK();
  }
  virtual Status Close() { return Status::OK(); }
  virtual Status Flush() { return Status::OK(); }
  virtual Status Sync() { return Status::OK(); }
};

bool HandleDumpCommand(Env* env, char** files, int num) {
  StdoutPrinter printer;
  bool ok = true;
  for (int i = 0; i < num; i++) {
    Status s = DumpFile(env, files[i], &printer);
    if (!s.ok()) {
      fprintf(stderr, "%s\n", s.ToString().c_str());
      ok = false;
    }
  }
  return ok;
}

}  // namespace
}  // namespace leveldb

static void Usage() {
  fprintf(
      stderr,
      "Usage: leveldbutil command...\n"
      "   dump files...         -- dump contents of specified files\n"
      );
}


#include <cassert>
#include <iostream>
#include <cstdint>
#include <chrono>

#include "leveldb/db.h"

using namespace std;

::std::uint64_t NowNanos() {
  return ::std::chrono::duration_cast<::std::chrono::nanoseconds>(
          ::std::chrono::steady_clock::now().time_since_epoch())
          .count();
}
int main(int argc, char** argv) {
  leveldb::Env* env = leveldb::Env::Default();
  bool ok = true;
  if (argc < 2) {
    Usage();
    ok = false;
  } else {
    std::string command = argv[1];
    if (command == "dump") {
      ok = leveldb::HandleDumpCommand(env, argv+2, argc-2);
    } else {
      Usage();
      ok = false;
    }
  }

  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  //leveldb::Status status = leveldb::DB::Open(options, "/dev/shm/testdb", &db);
  assert(status.ok());

  size_t total_insert = 1000000;

  leveldb::Slice s1;
  auto start_time = NowNanos();


  for(int i=0; i<total_insert; i++) {
    s1 = std::to_string(i);
    status = db->Put(leveldb::WriteOptions(), s1, std::to_string(i));
    if (!status.ok()) {
      cout<<"put error"<<endl;
      break;
    }
  }

  std::string rep;
  for(int i=0; i<total_insert; i++) {
    s1 = std::to_string(i);
    status = db->Get(leveldb::ReadOptions(), s1, &rep);
    if (!status.ok() || rep != s1) {
      cout<<"get error"<<endl;
      break;
    }
  }

  for(int i=0; i<total_insert ;i++) {
    s1 = std::to_string(i);
    status = db->Delete(leveldb::WriteOptions(), s1);
    if (!status.ok()) {
      cout<<"delete error"<<endl;
      break;
    }
  }
  auto end_time = NowNanos();
  cout<< end_time - start_time <<endl;

  /*
  std::string property;
  db->GetProperty("leveldb.sstables", &property);
  cout<<property.c_str()<<endl;
   */


  delete db;
  return (ok ? 0 : 1);
}
