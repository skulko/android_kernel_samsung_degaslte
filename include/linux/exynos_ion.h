/*
 * include/linux/exynos_ion.h
 *
 * Copyright (C) 2011 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _LINUX_EXYNOS_ION_H
#define _LINUX_EXYNOS_ION_H

#include <linux/ion.h>
#include <linux/device.h>
#include <linux/dma-buf.h>
#include <linux/dma-direction.h>

enum {
	ION_HEAP_TYPE_EXYNOS_CONTIG = ION_HEAP_TYPE_CUSTOM + 1,
	ION_HEAP_TYPE_EXYNOS,
	ION_HEAP_TYPE_EXYNOS_USER,
};

#define EXYNOS_ION_HEAP_SYSTEM_ID 0
#define EXYNOS_ION_HEAP_EXYNOS_CONTIG_ID 4
#define EXYNOS_ION_HEAP_EXYNOS_ID 5
#define EXYNOS_ION_HEAP_CHUNK_ID 6

#define EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK	(1 << EXYNOS_ION_HEAP_EXYNOS_CONTIG_ID)
#define EXYNOS_ION_HEAP_EXYNOS_MASK		(1 << EXYNOS_ION_HEAP_EXYNOS_ID)

enum {
	ION_EXYNOS_ID_COMMON		= 0,
	ION_EXYNOS_ID_MFC_SH		= 2,
	ION_EXYNOS_ID_MSGBOX_SH		= 3,
	ION_EXYNOS_ID_FIMD_VIDEO	= 4,
	ION_EXYNOS_ID_GSC		= 5,
	ION_EXYNOS_ID_MFC_OUTPUT	= 6,
	ION_EXYNOS_ID_MFC_INPUT		= 7,
	ION_EXYNOS_ID_MFC_FW		= 8,
	ION_EXYNOS_ID_SECTBL		= 9,
	ION_EXYNOS_ID_G2D_WFD		= 10,
	ION_EXYNOS_ID_VIDEO		= 11,
	ION_EXYNOS_ID_WFD_MFC = 12,
	ION_EXYNOS_MAX_CONTIG_ID
};

/* reserved 2 bits between contig heap masks and write mask */
/*
 * flag bits for exynos_ion
 * 31~30: reserved
 * 29~21: mfc_sh ~ g2d_wfd
 * 20: reserved
 * 19: write mask
 */
#define ION_EXYNOS_WRITE_MASK		\
	(1 << (BITS_PER_LONG - ION_EXYNOS_MAX_CONTIG_ID - 2))

#define EXYNOS_ION_CONTIG_MAX_ID      16
#define EXYNOS_ION_CONTIG_ID_MASK	\
	~((1 << (BITS_PER_LONG - ION_EXYNOS_MAX_CONTIG_ID)) - 1)

#define MAKE_CONTIG_ID(flag)	\
	((flag & EXYNOS_ION_CONTIG_ID_MASK) ? \
	((BITS_PER_LONG - fls(flag & EXYNOS_ION_CONTIG_ID_MASK)) + 1) : 0)
#define MAKE_CONTIG_MASK(id)	(1 << (BITS_PER_LONG - id))

#define ION_EXYNOS_MFC_SH_MASK		MAKE_CONTIG_MASK(ION_EXYNOS_ID_MFC_SH)
#define ION_EXYNOS_MSGBOX_SH_MASK	MAKE_CONTIG_MASK(ION_EXYNOS_ID_MSGBOX_SH)
#define ION_EXYNOS_FIMD_VIDEO_MASK    MAKE_CONTIG_MASK(ION_EXYNOS_ID_FIMD_VIDEO)
#define ION_EXYNOS_GSC_MASK		MAKE_CONTIG_MASK(ION_EXYNOS_ID_GSC)
#define ION_EXYNOS_MFC_OUTPUT_MASK    MAKE_CONTIG_MASK(ION_EXYNOS_ID_MFC_OUTPUT)
#define ION_EXYNOS_MFC_INPUT_MASK     MAKE_CONTIG_MASK(ION_EXYNOS_ID_MFC_INPUT)
#define ION_EXYNOS_MFC_FW_MASK		MAKE_CONTIG_MASK(ION_EXYNOS_ID_MFC_FW)
#define ION_EXYNOS_SECTBL_MASK		MAKE_CONTIG_MASK(ION_EXYNOS_ID_SECTBL)
#define ION_EXYNOS_G2D_WFD_MASK		MAKE_CONTIG_MASK(ION_EXYNOS_ID_G2D_WFD)

#define ION_HEAP_EXYNOS_MFC_SH_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_MFC_SH_MASK)
#define ION_HEAP_EXYNOS_MFC_FW_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_MFC_FW_MASK)
#define ION_HEAP_EXYNOS_SECTBL_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_SECTBL_MASK)
#define ION_HEAP_EXYNOS_FIMD_VIDEO_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_FIMD_VIDEO_MASK)
#define ION_HEAP_EXYNOS_GSC_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_GSC_MASK)
#define ION_HEAP_EXYNOS_MFC_OUTPUT_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_MFC_OUTPUT_MASK)
#define ION_HEAP_EXYNOS_MFC_INPUT_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_MFC_INPUT_MASK)
#define ION_HEAP_EXYNOS_MSGBOX_SH_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_MSGBOX_SH_MASK)
#define ION_HEAP_EXYNOS_G2D_WFD_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_G2D_WFD_MASK)
#define ION_HEAP_EXYNOS_VIDEO_MASK					\
		(EXYNOS_ION_HEAP_EXYNOS_CONTIG_MASK|ION_EXYNOS_VIDEO_MASK)

#ifdef __KERNEL__

void exynos_ion_sync_dmabuf_for_device(struct device *dev,
					struct dma_buf *dmabuf,
					size_t size,
					enum dma_data_direction dir);
void exynos_ion_sync_vaddr_for_device(struct device *dev,
					void *vaddr,
					size_t size,
					off_t offset,
					enum dma_data_direction dir);
void exynos_ion_sync_sg_for_device(struct device *dev,
					struct sg_table *sgt,
					enum dma_data_direction dir);
void exynos_ion_sync_dmabuf_for_cpu(struct device *dev,
					struct dma_buf *dmabuf,
					size_t size,
					enum dma_data_direction dir);
void exynos_ion_sync_vaddr_for_cpu(struct device *dev,
					void *vaddr,
					size_t size,
					off_t offset,
					enum dma_data_direction dir);
void exynos_ion_sync_sg_for_cpu(struct device *dev,
					struct sg_table *sgt,
					enum dma_data_direction dir);
int ion_exynos_contig_heap_info(int region_id, phys_addr_t *phys, size_t *size);
#endif /* __KERNEL */

#endif /* _LINUX_ION_H */
