
/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2015-2017 Ansyun <anssupport@163.com>. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Ansyun <anssupport@163.com> nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ANS_INIT_H__
#define __ANS_INIT_H__

/**
 * @file
 *
 * ANS initialization API defines.
 *
 */

#define ANS_MAX_NB_SOCKETS 8    /**< max number of sockets */


/**
 * ANS configuration
 */
struct ans_init_config 
{
    uint64_t lcore_mask;                                                                   /**< lcore which used to run ans */
    uint32_t max_sock_conn;                                                            /**< support max sock connection */
    cpu_set_t cpu_set;                                                                       /**< system default cpu set */
    struct rte_mempool *pktmbuf_pool[ANS_MAX_NB_SOCKETS];     /**< mbuf pools for each sockets */
} __rte_cache_aligned;


typedef int (*ans_send_packet_cb)(struct rte_mbuf *m, uint8_t port);

/**
 * Init ans stack.
 * @param user_conf   
 *   user config.
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_initialize(struct ans_init_config *user_conf);

/**
 * Register packet send callback to ans stack.
 * @param send_cb     
 *   callback function.
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_register(ans_send_packet_cb send_cb);

/**
 * Handle the received packets by ans stack
 *
 * @param m 
 *    packet buffer. 
 * @param portid  
 *    port id.
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
 int ans_packet_handle(struct rte_mbuf *m, uint8_t portid);

/**
 * Handle the received packets by ans stack
 *
 * @param portid  
 *    port id.
 * @param packets_nb 
 *    droped packets number. 
 *
 * @return  
 *
 */
void ans_packet_stats(uint8_t portid, uint16_t packets_nb);

/**
 * Handle ans internal message.
 *
 * @param lcore_id
 *   current lcore id.
 *
 * @return  
 *
 */
void ans_message_handle(unsigned lcore_id);


#endif /* __ANS_INIT_H__ */
