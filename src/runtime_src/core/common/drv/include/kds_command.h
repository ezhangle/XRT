// SPDX-License-Identifier: GPL-2.0
/*
 * Xilinx Kernel Driver Scheduler
 *
 * Copyright (C) 2020 Xilinx, Inc.
 *
 * Authors: min.ma@xilinx.com
 */

#ifndef _KDS_COMMAND_H
#define _KDS_COMMAND_H

/* Userspace command format */
#include "ert.h"

#define REGMAP 0
#define KEY_VAL 1

enum kds_opcode {
	OP_CONFIG = 0,
	OP_START,
};

enum kds_status {
	KDS_COMPLETED	= 0,
	KDS_ERROR	= 1,
	KDS_ABORT,
	KDS_TIMEOUT,
};

struct kds_command;

struct kds_cmd_ops {
	void (*notify_host)(struct kds_command *xcmd, int status);
	void (*free)(struct kds_command *xcmd);
};

/**
 * struct kds_command: KDS command struct
 * @client: the client that the command belongs to
 * @type:   type of the command. Use this to determin controller
 */
struct kds_command {
	struct kds_client	*client;
	u32			 type;
	u32			 opcode;
	struct list_head	 list;
	void			*info;
	size_t			 isize;
	/* TODO: may rethink if we should have cu bit mask here
	 * or move it to info.
	 * Since NO all types of command have cu_mask
	 */
	u32			 cu_mask[4];
	u32			 num_mask;
	u32			 payload_type;
	u64			 start;
	struct kds_cmd_ops	 cb;
	/* execbuf is used to update the header
	 * of execbuf when notifying host
	 */
	u32			*execbuf;
	void			*gem_obj;
};

/* execbuf command related funtions */
void cfg_ecmd2xcmd(struct ert_configure_cmd *ecmd,
		   struct kds_command *xcmd);
void start_krnl_ecmd2xcmd(struct ert_start_kernel_cmd *ecmd,
			  struct kds_command *xcmd);
int cu_mask_to_cu_idx(struct kds_command *xcmd, uint8_t *cus);

#endif
