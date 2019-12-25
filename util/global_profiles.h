//
// Created by lingo on 19-12-24.
//

#ifndef LEVELDB_GLOBAL_PROFILES_H
#define LEVELDB_GLOBAL_PROFILES_H

#include <iostream>

namespace cache_profiles {

extern uint64_t env_file_write_times;
extern uint64_t env_file_write_len;

extern uint64_t env_file_read_times;
extern uint64_t env_file_read_len;
extern uint64_t ReadBlock_times;
extern uint64_t ReadBlock_len;
extern uint64_t read_index_meta_times;
extern uint64_t read_index_meta_len;
extern uint64_t get_data_block_times;
extern uint64_t get_data_block_len;
extern uint64_t iter_data_block_times;
extern uint64_t iter_data_block_len;

extern uint64_t get_data_cache_access_times;
extern uint64_t get_data_cache_miss;

extern uint64_t iter_data_cache_access_times;
extern uint64_t iter_data_cache_miss;

extern uint64_t data_cache_times;
extern uint64_t data_cache_miss;

inline static void Clear() {
    env_file_write_times = 0;
    env_file_write_len = 0;

    env_file_read_times = 0;
    env_file_read_len = 0;
    ReadBlock_times = 0;
    ReadBlock_len = 0;
    read_index_meta_times = 0;
    read_index_meta_len = 0;
    get_data_block_times = 0;
    get_data_block_len = 0;
    iter_data_block_times = 0;
    iter_data_block_len = 0;

    get_data_cache_access_times = 0;
    get_data_cache_miss = 0;

    iter_data_cache_access_times = 0;
    iter_data_cache_miss = 0;

    data_cache_times = 0;
    data_cache_miss = 0;
}

inline static void Message(std::ostream& os) {
    os << "env_file_write_times: \t" << env_file_write_times << "\n" <<
    "env_file_write_len: \t" << env_file_write_len << "\n" <<
    "env_file_read_times: \t" << env_file_read_times << "\n" <<
    "env_file_read_len: \t" << env_file_read_len << "\n" <<
    "ReadBlock_times: \t" << ReadBlock_times << "\n" <<
    "ReadBlock_len: \t" << ReadBlock_len << "\n" <<
    "read_index_meta_times: \t" << read_index_meta_times << "\n" <<
    "read_index_meta_len: \t" << read_index_meta_len << "\n" <<
    "get_data_block_times: \t" << get_data_block_times << "\n" <<
    "get_data_block_len: \t" << get_data_block_len << "\n" <<
    "iter_data_block_times: \t" << iter_data_block_times << "\n" <<
    "iter_data_block_len: \t" << iter_data_block_len << "\n" <<
    "get_data_cache_access_times: \t" << get_data_cache_access_times << "\n" <<
    "get_data_cache_miss: \t" << get_data_cache_miss << "\n" <<
    "iter_data_cache_access_times: \t" << iter_data_cache_access_times << "\n" <<
    "iter_data_cache_miss: \t" << iter_data_cache_miss << "\n" <<
    "data_cache_times: \t" << data_cache_times << "\n" <<
    "data_cache_miss: \t" << data_cache_miss << "\n";
}

enum parameter_padding {
    IndexAndMeta,
    InternalGet,
    Table_NewIterator,
    GetFileIterator
};

}


#endif //LEVELDB_GLOBAL_PROFILES_H
