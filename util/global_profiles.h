//
// Created by lingo on 19-12-24.
//

#ifndef LEVELDB_GLOBAL_PROFILES_H
#define LEVELDB_GLOBAL_PROFILES_H

#include <iostream>
#include <atomic>
namespace cache_profiles {

extern std::atomic<uint64_t> env_file_write_times;
extern std::atomic<uint64_t> env_file_write_len;

extern std::atomic<uint64_t> env_file_read_times;
extern std::atomic<uint64_t> env_file_read_len;
extern std::atomic<uint64_t> ReadBlock_times;
extern std::atomic<uint64_t> ReadBlock_len;
extern std::atomic<uint64_t> read_footer_times;
extern std::atomic<uint64_t> read_footer_len;
extern std::atomic<uint64_t> read_index_meta_block_times;
extern std::atomic<uint64_t> read_index_meta_block_len;
extern std::atomic<uint64_t> get_data_block_times;
extern std::atomic<uint64_t> get_data_block_len;
extern std::atomic<uint64_t> iter_data_block_times;
extern std::atomic<uint64_t> iter_data_block_len;

extern std::atomic<uint64_t> get_data_cache_access_times;
extern std::atomic<uint64_t> get_data_cache_miss;
extern std::atomic<uint64_t> get_data_cache_hit;

extern std::atomic<uint64_t> iter_data_cache_access_times;
extern std::atomic<uint64_t> iter_data_cache_miss;
extern std::atomic<uint64_t> iter_data_cache_hit;

extern std::atomic<uint64_t> data_cache_access_times;
extern std::atomic<uint64_t> data_cache_miss;
extern std::atomic<uint64_t> data_cache_hit;

inline static void Clear() {
    env_file_write_times = 0;
    env_file_write_len = 0;

    env_file_read_times = 0;
    env_file_read_len = 0;
    ReadBlock_times = 0;
    ReadBlock_len = 0;
    read_footer_times = 0;
    read_footer_len = 0;
    read_index_meta_block_times = 0;
    read_index_meta_block_len = 0;
    get_data_block_times = 0;
    get_data_block_len = 0;
    iter_data_block_times = 0;
    iter_data_block_len = 0;

    get_data_cache_access_times = 0;
    get_data_cache_miss = 0;
    get_data_cache_hit = 0;

    iter_data_cache_access_times = 0;
    iter_data_cache_miss = 0;
    iter_data_cache_hit = 0;

    data_cache_access_times = 0;
    data_cache_miss = 0;
    data_cache_hit = 0;
}

inline bool Confirm() {
    return (env_file_read_times == ReadBlock_times + read_footer_times)
           && (env_file_read_len == ReadBlock_len + read_footer_len)
           && (ReadBlock_times == read_index_meta_block_times + get_data_block_times + iter_data_block_times)
           && (ReadBlock_len == read_index_meta_block_len + get_data_block_len + iter_data_block_len)
           && (get_data_block_times == get_data_cache_miss)
           && (iter_data_block_times == iter_data_cache_miss)
           && (data_cache_access_times == get_data_cache_access_times + iter_data_cache_access_times)
           && (data_cache_miss == get_data_cache_miss + iter_data_cache_miss)
           && (data_cache_hit == get_data_cache_hit + iter_data_cache_hit)
           && (get_data_cache_access_times == get_data_cache_hit + get_data_cache_miss)
           && (iter_data_cache_access_times == iter_data_cache_hit + iter_data_cache_miss);
}

inline static void Message(std::ostream& os) {
    os << "confirm: \t" << Confirm() << "\n";
    os << "env_file_write_times: \t" << env_file_write_times << "\n" <<
    "env_file_write_len: \t" << env_file_write_len << "\n" <<
    "env_file_read_times: \t" << env_file_read_times << "\n" <<
    "env_file_read_len: \t" << env_file_read_len << "\n" <<
    "ReadBlock_times: \t" << ReadBlock_times << "\n" <<
    "ReadBlock_len: \t" << ReadBlock_len << "\n" <<
    "read_footer_times: \t" << read_footer_times << "\n" <<
    "read_footer_len: \t" << read_footer_len << "\n" <<
    "read_index_meta_block_times: \t" << read_index_meta_block_times << "\n" <<
    "read_index_meta_block_len: \t" << read_index_meta_block_len << "\n" <<
    "get_data_block_times: \t" << get_data_block_times << "\n" <<
    "get_data_block_len: \t" << get_data_block_len << "\n" <<
    "iter_data_block_times: \t" << iter_data_block_times << "\n" <<
    "iter_data_block_len: \t" << iter_data_block_len << "\n" <<
    "get_data_cache_access_times: \t" << get_data_cache_access_times << "\n" <<
    "get_data_cache_miss: \t" << get_data_cache_miss << "\n" <<
    "get_data_cache_hit: \t" << get_data_cache_hit << "\n" <<
    "iter_data_cache_access_times: \t" << iter_data_cache_access_times << "\n" <<
    "iter_data_cache_miss: \t" << iter_data_cache_miss << "\n" <<
    "iter_data_cache_hit: \t" << iter_data_cache_hit << "\n" <<
    "data_cache_access_times: \t" << data_cache_access_times << "\n" <<
    "data_cache_miss: \t" << data_cache_miss << "\n" <<
    "data_cache_hit: \t" << data_cache_hit << "\n";
}

enum parameter_padding {
    IndexAndMeta = 0,
    InternalGet = 1,
    Table_NewIterator = 2,
    GetFileIterator = 3
};

}


#endif //LEVELDB_GLOBAL_PROFILES_H
