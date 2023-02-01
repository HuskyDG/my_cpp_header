#pragma once
#include <iostream>
#include <vector>

struct SMapInfo {
    size_t mem = 0;
    size_t kernel_page = 0;
    size_t mmu_page = 0;
    size_t rss = 0;
    size_t pss = 0;
    size_t shared_clean = 0;
    size_t shared_dirty = 0;
    size_t private_clean = 0;
    size_t private_dirty = 0;
    size_t referenced = 0;
    size_t anonymous = 0;
    size_t anonhugepages = 0;
    size_t shared_hugetlb = 0;
    size_t private_hugetlb = 0;
    size_t swap = 0;
    size_t swappss = 0;
    size_t locked = 0;
};

struct MapInfo {
    uintptr_t start;
    uintptr_t end;
    uint8_t perms;
    bool is_private;
    dev_t dev;
    ino_t inode;
    std::string path;
    uintptr_t offset;
    SMapInfo smap;
};

struct mount_info {
    unsigned int id;
    unsigned int parent;
    dev_t device;
    std::string root;
    std::string target;
    std::string vfs_option;
    struct {
        unsigned int shared;
        unsigned int master;
        unsigned int propagate_from;
    } optional;
    std::string type;
    std::string source;
    std::string fs_option;
};

std::vector<mount_info> parse_mount_info(const char *pid);
std::vector<MapInfo> scan_maps(int pid = -1, bool smap = false);
std::vector<MapInfo> find_maps(const char *name);
void remap_all(const char *name);
void set_nice_name(int argc, char **argv, const char *name);
int setcurrent(const char *con);
std::string getcurrent();
