#include <fat.h>
#include <fs.h>

#include <common.h>
#include <boot_rkimg.h>
#include <bmp_layout.h>
#include <malloc.h>
#include <asm/unaligned.h>
#include <linux/libfdt.h>
#include <linux/list.h>
#include <asm/arch/resource_img.h>
#include <asm/arch/uimage.h>
#include <asm/arch/fit.h>


int radxa_read_bmp_file(void *buf, const char *name) {

	struct blk_desc *desc = rockchip_get_bootdev();
	disk_partition_t part;
	loff_t actread, len;

	if (!desc)
		return -ENODEV;

	// 获取第一个分区的信息
	if (part_get_info_by_name(desc, "config", &part) < 0) {
		printf("***** Failed to get info for first partition *****\n");
		return -ENODEV;
	}
	printf("===== get config partition info =====\n");

	// 设置 FAT 文件系统
	if (fat_set_blk_dev(desc, &part) != 0) {
		printf("===== Failed to set block device for FAT =====\n");
		return -ENODEV;
	}
	printf("===== FAT filesystem set up =====\n");

	// 检查文件是否存在
	if (fat_exists(name) != 1) {
		printf("File %s does not exist\n", name);
		return -ENOENT;
	}
	printf("===== File %s exists =====\n", name);


	// 获取文件大小
	if (fat_size(name, &len) < 0) {
		printf("Failed to get file size for %s\n", name);
		return -ENOENT;
	}
	printf("===== File %s size: %lld bytes =====\n", name, len);

	// 分配内存以读取文件
	// buf = memalign(ARCH_DMA_MINALIGN, len); // 使用 memalign 进行对齐分配
	if (!buf) {
		printf("Failed to allocate memory for file\n");
        free(buf);
		return -ENOMEM;
	}
	printf("===== Memory allocated for file =====\n");

	// 读取文件内容
	actread = file_fat_read(name, buf, len);
	if (actread != len) {
		printf("===== Failed to read file %s: read %lld, expected %lld =====\n", name, actread, len);
		free(buf); // 确保在返回之前释放内存
		return -EIO;
	}
	printf("Successfully read file %s: read %lld, expected %lld\n", name, actread, len);
	printf("function readx_read_bmp_file: %c, %c, %c, %c  =====\n", *(char *)buf, *(char *)buf+1, *(char *)buf+2, *(char *)buf+3);

    return len;
}
