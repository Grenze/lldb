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
  return static_cast<uint64_t>(::std::chrono::duration_cast<::std::chrono::nanoseconds>(
            ::std::chrono::steady_clock::now().time_since_epoch())
            .count());
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


    size_t total_insert = 500000*2*10;

    leveldb::Slice s1;
    leveldb::Slice s2;


    auto start_time = NowNanos();
    int ll = 1;
    //for (ll = 0; ll < 1000; ll++) {
    for(int i = 1; i <= total_insert; i++) {
        s1 = std::to_string(i);
        status = db->Put(leveldb::WriteOptions(), s1, std::to_string(i+ll));
        if (!status.ok()) {
            cout<<"put error"<<endl;
            break;
        }
    }
    //}


    /*
    for(int i = 1; i <= total_insert; i++) {
        s1 = std::to_string(i);
        status = db->Put(leveldb::WriteOptions(), s1, std::to_string(i+1));
        if (!status.ok()) {
            cout<<"put error"<<endl;
            break;
        }
    }
     */

    auto p1_time = NowNanos();
    cout<< "Phase1 nanosecond: " << p1_time - start_time <<endl;


    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    int check = 0;
/*
    it->SeekToFirst();
    leveldb::Slice first(it->key().ToString());
    it->SeekToLast();
    leveldb::Slice last(it->key().ToString());

    for (it->Seek(last.ToString()); it->Valid() && it->key().ToString() >= first.ToString(); it->Prev()) {
        //cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
        check++;
    }
    assert(check == total_insert);

    check = 0;
    for (it->Seek(first.ToString()); it->Valid() && it->key().ToString() <= last.ToString(); it->Next()) {
        //cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
        check++;
    }
    assert(check == total_insert);

    check = 0;
    for (it->SeekToLast(); it->Valid(); it->Prev()) {
        //cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
        check++;
    }
    assert(check == total_insert);

    check = 0;*/
    //it->Seek("0");
    //std::cout<<it->key().ToString()<<std::endl;//1
    for (it->Seek("0"); it->Valid(); it->Next()) {
        //cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
        check++;
    }
    assert(check == total_insert);
    assert(it->status().ok());  // Check for any errors found during the scan


    auto p2_time = NowNanos();
    cout<< "Phase2 nanosecond: " << p2_time - p1_time <<endl;

    check = 0;
    for (it->SeekToLast(); it->Valid(); it->Prev()) {
        //cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
        check++;
    }
    assert(check == total_insert);
    delete it;

    auto p3_time = NowNanos();
    cout<< "Phase3 nanosecond: " << p3_time - p2_time <<endl;

    std::string rep;
    for(int i = 1; i <= total_insert; i++) {
        s1 = std::to_string(i);
        s2 = std::to_string(i+ll);
        status = db->Get(leveldb::ReadOptions(), s1, &rep);
        if (!status.ok() || rep != s2) {
            cout<<"get error"<<endl;
            break;
        }
    }

    auto p4_time = NowNanos();
    cout<< "Phase4 nanosecond: " << p4_time - p3_time <<endl;

    for(int i = 1; i <= total_insert ;i++) {
        s1 = std::to_string(i);
        status = db->Delete(leveldb::WriteOptions(), s1);
        if (!status.ok()) {
            cout<<"delete error"<<endl;
            break;
        }
    }

    auto p5_time = NowNanos();
    cout<< "Phase5 nanosecond: " << p5_time - p4_time <<endl;

    auto end_time = NowNanos();
    cout<< "Total nanosecond: "<< end_time - start_time <<endl;

    delete db;
    //std::cout<<sizeof(void*)<<" "<<sizeof(int)<<" "<<sizeof(size_t); //8 4 8
    return 1;
}
