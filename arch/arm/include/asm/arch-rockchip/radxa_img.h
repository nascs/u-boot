/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __RADXA_IMG_H_
#define __RADXA_IMG_H_

#include <linux/list.h>

/*
 * radxa_read_bmp_file() - read file from resource.
 *
 * @buf: destination buf to store file data
 * @name: file name
 * @blk_offset: blocks offset in the file, 1 block = 512 bytes
 * @len: the size(by bytes) of file to read
 *
 * return the length of read data.
 */
int radxa_read_bmp_file(void *buf, const char *name);


#endif
