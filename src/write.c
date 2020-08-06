#define NULL 0

typedef struct file {
    int (*write)(const char *buff, unsigned int size);
    int (*read)(const char *buff, unsigned int size);
    int (*seek)(int seek, int from);
} FILE;

#define ERR_NO_PERMISSION 1

typedef struct {
    KUser *user;
} KProcess;

FILE *syscall_open(int pid, const char *path, int flags) {
    KUser user = k_user_from_pid(pid);
    VsfFile vf = k_vfs_resolve(path);
    VfsStat st = k_vfs_stat(vf);
    if (!k_user_in_group(user, st.owner)) {
        return -ERR_NO_PERMISSION;
    }

    return k_vfs_as_file(vf);
}

unsigned int syscall_write(int fd, const char *buff, unsigned int size) {
    FILE *fl = k_resolve_fd(fd);
    if (fl == NULL) {
        return -1;
    }

    return fl->write(buff, size);
}
