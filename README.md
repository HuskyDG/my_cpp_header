## Personal header files

### MountInfo

1. Structure of `mount_info`:

```cpp
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
```

2. Parse `/proc/pid/mountinfo` and store to vector:

```cpp
std::vector<mount_info> parse_mount_info(const char *pid);
```
```cpp
// Parse mount info of myself
auto s = parse_mount_info("self");
// Parse mount info of PID 123
auto x = parse_mount_info("123");
```

### Maps Parser

1. Structure of `MapInfo` and `SMapInfo`:

```cpp
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
```

2. Parse `/proc/pid/maps` or `/proc/pid/smaps` and store the list of map info:

```cpp
std::vector<MapInfo> scan_maps(int pid = -1, bool smap = false);
```

```cpp
// Parse maps of myself
auto my_maps = scan_maps();
// Parse smaps of myself, get additional info of size
auto my_smaps = scan_maps(-1, true);
// Parse maps of 123
auto my_maps = scan_maps(123);
// Parse smaps of 393, get additional info of size
auto my_smaps = scan_maps(393, true);
```
3. Parse `/proc/pid/maps` and store the list of map info with matching name:

```cpp

```

4. Remapping all memories with matching name to anonymous memories:

```cpp
void remap_all(const char *name);
```

