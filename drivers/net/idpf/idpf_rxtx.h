/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2022 Intel Corporation
 */

#ifndef _IDPF_RXTX_H_
#define _IDPF_RXTX_H_

#include <idpf_common_rxtx.h>
#include "idpf_ethdev.h"

/* MTS */
#define GLTSYN_CMD_SYNC_0_0	(PF_TIMESYNC_BASE + 0x0)
#define PF_GLTSYN_SHTIME_0_0	(PF_TIMESYNC_BASE + 0x4)
#define PF_GLTSYN_SHTIME_L_0	(PF_TIMESYNC_BASE + 0x8)
#define PF_GLTSYN_SHTIME_H_0	(PF_TIMESYNC_BASE + 0xC)
#define GLTSYN_ART_L_0		(PF_TIMESYNC_BASE + 0x10)
#define GLTSYN_ART_H_0		(PF_TIMESYNC_BASE + 0x14)
#define PF_GLTSYN_SHTIME_0_1	(PF_TIMESYNC_BASE + 0x24)
#define PF_GLTSYN_SHTIME_L_1	(PF_TIMESYNC_BASE + 0x28)
#define PF_GLTSYN_SHTIME_H_1	(PF_TIMESYNC_BASE + 0x2C)
#define PF_GLTSYN_SHTIME_0_2	(PF_TIMESYNC_BASE + 0x44)
#define PF_GLTSYN_SHTIME_L_2	(PF_TIMESYNC_BASE + 0x48)
#define PF_GLTSYN_SHTIME_H_2	(PF_TIMESYNC_BASE + 0x4C)
#define PF_GLTSYN_SHTIME_0_3	(PF_TIMESYNC_BASE + 0x64)
#define PF_GLTSYN_SHTIME_L_3	(PF_TIMESYNC_BASE + 0x68)
#define PF_GLTSYN_SHTIME_H_3	(PF_TIMESYNC_BASE + 0x6C)

#define PF_TIMESYNC_BAR4_BASE	0x0E400000
#define GLTSYN_ENA		(PF_TIMESYNC_BAR4_BASE + 0x90)
#define GLTSYN_CMD		(PF_TIMESYNC_BAR4_BASE + 0x94)
#define GLTSYC_TIME_L		(PF_TIMESYNC_BAR4_BASE + 0x104)
#define GLTSYC_TIME_H		(PF_TIMESYNC_BAR4_BASE + 0x108)

#define GLTSYN_CMD_SYNC_0_4	(PF_TIMESYNC_BAR4_BASE + 0x110)
#define PF_GLTSYN_SHTIME_L_4	(PF_TIMESYNC_BAR4_BASE + 0x118)
#define PF_GLTSYN_SHTIME_H_4	(PF_TIMESYNC_BAR4_BASE + 0x11C)
#define GLTSYN_INCVAL_L		(PF_TIMESYNC_BAR4_BASE + 0x150)
#define GLTSYN_INCVAL_H		(PF_TIMESYNC_BAR4_BASE + 0x154)
#define GLTSYN_SHADJ_L		(PF_TIMESYNC_BAR4_BASE + 0x158)
#define GLTSYN_SHADJ_H		(PF_TIMESYNC_BAR4_BASE + 0x15C)

#define GLTSYN_CMD_SYNC_0_5	(PF_TIMESYNC_BAR4_BASE + 0x130)
#define PF_GLTSYN_SHTIME_L_5	(PF_TIMESYNC_BAR4_BASE + 0x138)
#define PF_GLTSYN_SHTIME_H_5	(PF_TIMESYNC_BAR4_BASE + 0x13C)

/* In QLEN must be whole number of 32 descriptors. */
#define IDPF_ALIGN_RING_DESC	32
#define IDPF_MIN_RING_DESC	32
#define IDPF_MAX_RING_DESC	4096
#define IDPF_DMA_MEM_ALIGN	4096
/* Base address of the HW descriptor ring should be 128B aligned. */
#define IDPF_RING_BASE_ALIGN	128

#define IDPF_DEFAULT_RX_FREE_THRESH	32

/* used for Vector PMD */
#define IDPF_VPMD_RX_MAX_BURST	32
#define IDPF_VPMD_TX_MAX_BURST	32
#define IDPF_VPMD_DESCS_PER_LOOP	4
#define IDPF_RXQ_REARM_THRESH	64

#define IDPF_DEFAULT_TX_RS_THRESH	32
#define IDPF_DEFAULT_TX_FREE_THRESH	32

#define IDPF_TX_MAX_MTU_SEG	10

#define IDPF_MIN_TSO_MSS	88
#define IDPF_MAX_TSO_MSS	9728
#define IDPF_MAX_TSO_FRAME_SIZE	262143
#define IDPF_TX_MAX_MTU_SEG     10

#define IDPF_TX_CKSUM_OFFLOAD_MASK (		\
		RTE_MBUF_F_TX_IP_CKSUM |	\
		RTE_MBUF_F_TX_L4_MASK |		\
		RTE_MBUF_F_TX_TCP_SEG)

#define IDPF_TX_OFFLOAD_MASK (			\
		IDPF_TX_CKSUM_OFFLOAD_MASK |	\
		RTE_MBUF_F_TX_IPV4 |		\
		RTE_MBUF_F_TX_IPV6)

#define IDPF_TX_OFFLOAD_NOTSUP_MASK \
		(RTE_MBUF_F_TX_OFFLOAD_MASK ^ IDPF_TX_OFFLOAD_MASK)

extern uint64_t idpf_timestamp_dynflag;

struct idpf_tx_vec_entry {
	struct rte_mbuf *mbuf;
};

/* Offload features */
union idpf_tx_offload {
	uint64_t data;
	struct {
		uint64_t l2_len:7; /* L2 (MAC) Header Length. */
		uint64_t l3_len:9; /* L3 (IP) Header Length. */
		uint64_t l4_len:8; /* L4 Header Length. */
		uint64_t tso_segsz:16; /* TCP TSO segment size */
		/* uint64_t unused : 24; */
	};
};

int idpf_rx_queue_setup(struct rte_eth_dev *dev, uint16_t queue_idx,
			uint16_t nb_desc, unsigned int socket_id,
			const struct rte_eth_rxconf *rx_conf,
			struct rte_mempool *mp);
int idpf_singleq_tx_vec_setup_avx512(struct idpf_tx_queue *txq);
int idpf_rx_queue_init(struct rte_eth_dev *dev, uint16_t rx_queue_id);
int idpf_rx_queue_start(struct rte_eth_dev *dev, uint16_t rx_queue_id);
int idpf_rx_queue_stop(struct rte_eth_dev *dev, uint16_t rx_queue_id);
void idpf_dev_rx_queue_release(struct rte_eth_dev *dev, uint16_t qid);

int idpf_tx_queue_setup(struct rte_eth_dev *dev, uint16_t queue_idx,
			uint16_t nb_desc, unsigned int socket_id,
			const struct rte_eth_txconf *tx_conf);
int idpf_singleq_rx_vec_setup(struct idpf_rx_queue *rxq);
int idpf_tx_queue_init(struct rte_eth_dev *dev, uint16_t tx_queue_id);
int idpf_tx_queue_start(struct rte_eth_dev *dev, uint16_t tx_queue_id);
int idpf_tx_queue_stop(struct rte_eth_dev *dev, uint16_t tx_queue_id);
void idpf_dev_tx_queue_release(struct rte_eth_dev *dev, uint16_t qid);
uint16_t idpf_singleq_recv_pkts(void *rx_queue, struct rte_mbuf **rx_pkts,
				uint16_t nb_pkts);
uint16_t idpf_singleq_recv_pkts_avx512(void *rx_queue, struct rte_mbuf **rx_pkts,
				       uint16_t nb_pkts);
uint16_t idpf_splitq_recv_pkts(void *rx_queue, struct rte_mbuf **rx_pkts,
			       uint16_t nb_pkts);
uint16_t idpf_singleq_xmit_pkts(void *tx_queue, struct rte_mbuf **tx_pkts,
				uint16_t nb_pkts);
uint16_t idpf_singleq_xmit_pkts_avx512(void *tx_queue, struct rte_mbuf **tx_pkts,
				       uint16_t nb_pkts);
uint16_t idpf_splitq_xmit_pkts(void *tx_queue, struct rte_mbuf **tx_pkts,
			       uint16_t nb_pkts);
uint16_t idpf_prep_pkts(void *tx_queue, struct rte_mbuf **tx_pkts,
			uint16_t nb_pkts);

void idpf_stop_queues(struct rte_eth_dev *dev);

void idpf_set_rx_function(struct rte_eth_dev *dev);
void idpf_set_tx_function(struct rte_eth_dev *dev);

#define IDPF_TIMESYNC_REG_WRAP_GUARD_BAND  10000
/* Helper function to convert a 32b nanoseconds timestamp to 64b. */
static inline uint64_t

idpf_tstamp_convert_32b_64b(struct idpf_adapter_ext *ad, uint32_t flag,
			    uint32_t in_timestamp)
{
#ifdef RTE_ARCH_X86_64
	struct idpf_hw *hw = &ad->base.hw;
	const uint64_t mask = 0xFFFFFFFF;
	uint32_t hi, lo, lo2, delta;
	uint64_t ns;

	if (flag != 0) {
		IDPF_WRITE_REG(hw, GLTSYN_CMD_SYNC_0_0, PF_GLTSYN_CMD_SYNC_SHTIME_EN_M);
		IDPF_WRITE_REG(hw, GLTSYN_CMD_SYNC_0_0, PF_GLTSYN_CMD_SYNC_EXEC_CMD_M |
			       PF_GLTSYN_CMD_SYNC_SHTIME_EN_M);
		lo = IDPF_READ_REG(hw, PF_GLTSYN_SHTIME_L_0);
		hi = IDPF_READ_REG(hw, PF_GLTSYN_SHTIME_H_0);
		/*
		 * On typical system, the delta between lo and lo2 is ~1000ns,
		 * so 10000 seems a large-enough but not overly-big guard band.
		 */
		if (lo > (UINT32_MAX - IDPF_TIMESYNC_REG_WRAP_GUARD_BAND))
			lo2 = IDPF_READ_REG(hw, PF_GLTSYN_SHTIME_L_0);
		else
			lo2 = lo;

		if (lo2 < lo) {
			lo = IDPF_READ_REG(hw, PF_GLTSYN_SHTIME_L_0);
			hi = IDPF_READ_REG(hw, PF_GLTSYN_SHTIME_H_0);
		}

		ad->time_hw = ((uint64_t)hi << 32) | lo;
	}

	delta = (in_timestamp - (uint32_t)(ad->time_hw & mask));
	if (delta > (mask / 2)) {
		delta = ((uint32_t)(ad->time_hw & mask) - in_timestamp);
		ns = ad->time_hw - delta;
	} else {
		ns = ad->time_hw + delta;
	}

	return ns;
#else /* !RTE_ARCH_X86_64 */
	RTE_SET_USED(ad);
	RTE_SET_USED(flag);
	RTE_SET_USED(in_timestamp);
	return 0;
#endif /* RTE_ARCH_X86_64 */
}

#endif /* _IDPF_RXTX_H_ */
