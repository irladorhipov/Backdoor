#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>

static int __init set_file_permissions_init(void) {
    struct file *file;
    char *filename = "/path/to/your/file"; 
    int err;

    file = filp_open(filename, O_RDWR, 0);
    if (IS_ERR(file)) {
        pr_err("Failed to open file\n");
        return PTR_ERR(file);
    }

    err = vfs_chmod(&file->f_path, 0777);
    if (err) {
        pr_err("Failed to change file permissions\n");
        filp_close(file, NULL);
        return err;
    }

    filp_close(file, NULL);
    pr_info("File permissions set to 777\n");

    return 0;
}

static void __exit set_file_permissions_exit(void) {
    pr_info("Module unloaded\n");
}

module_init(set_file_permissions_init);
module_exit(set_file_permissions_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Linux module to set file permissions to 777");