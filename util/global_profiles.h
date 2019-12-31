//
// Created by lingo on 19-12-24.
//

#ifndef LEVELDB_GLOBAL_PROFILES_H
#define LEVELDB_GLOBAL_PROFILES_H

#include <iostream>
#include <atomic>
#include <chrono>

namespace profiles {

extern std::atomic<uint64_t> DBImpl_Get;

extern std::atomic<uint64_t> lock_wait;
extern std::atomic<uint64_t> compact;
extern std::atomic<uint64_t> mems_Get;
extern std::atomic<uint64_t> Version_Get;

extern std::atomic<uint64_t> mis_file_search;

extern std::atomic<uint64_t> table_cache_Get;
extern std::atomic<uint64_t> table_cache_Get_times;

extern std::atomic<uint64_t> find_table;    // table cache 990 default
extern std::atomic<uint64_t> Internal_Get;

extern std::atomic<uint64_t> index_block_iter;
extern std::atomic<uint64_t> filter_KeyMayMatch;
extern std::atomic<uint64_t> data_block_iter;
extern std::atomic<uint64_t> save_value;
extern std::atomic<uint64_t> value_copy;

extern std::atomic<uint64_t> write_len;

inline static void Clear() {
    DBImpl_Get = 0;
    lock_wait = 0;
    compact = 0;
    mems_Get = 0;
    Version_Get = 0;
    mis_file_search = 0;
    table_cache_Get = 0;
    table_cache_Get_times = 0;
    find_table = 0;
    Internal_Get = 0;
    index_block_iter = 0;
    filter_KeyMayMatch = 0;
    data_block_iter = 0;
    save_value = 0;
    value_copy = 0;
    write_len = 0;
}

inline static bool Confirm() {
    return true;
}

inline static void Message(std::ostream& os) {
    os << "confirm: \t" << Confirm() << "\n";
    os << "DBImpl_Get: \t" << DBImpl_Get << "\n";
    os << "lock_wait: \t" << lock_wait << "\n";
    os << "compact: \t" << compact << "\n";
    os << "mems_Get: \t" << mems_Get << "\n";
    os << "Version_Get: \t" << Version_Get << "\n";
    os << "mis_file_search: \t" << mis_file_search << "\n";
    os << "table_cache_Get: \t" << table_cache_Get << "\n";
    os << "table_cache_Get_times: \t" << table_cache_Get_times << "\n";
    os << "find_table: \t" << find_table << "\n";
    os << "Internal_Get: \t" << Internal_Get << "\n";
    os << "index_block_iter: \t" << index_block_iter << "\n";
    os << "filter_KeyMayMatch: \t" << filter_KeyMayMatch << "\n";
    os << "data_block_iter: \t" << data_block_iter << "\n";
    os << "save_value: \t" << save_value << "\n";
    os << "value_copy: \t" << value_copy << "\n";
    os << "write_len: \t" << write_len << "\n";
}

inline static uint64_t NowNanos() {
    return static_cast<uint64_t>(::std::chrono::duration_cast<::std::chrono::nanoseconds>(
            ::std::chrono::steady_clock::now().time_since_epoch())
            .count());
}
}



#endif //LEVELDB_GLOBAL_PROFILES_H
