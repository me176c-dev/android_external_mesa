/*
 * Copyright (c) 2018 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef GEN_AUX_MAP_H
#define GEN_AUX_MAP_H

#include "gen_buffer_alloc.h"

#include "isl/isl.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Auxiliary surface mapping implementation
 *
 * These functions are implemented in common code shared by drivers.
 */

struct gen_aux_map_context;
struct gen_device_info;

struct gen_aux_map_context *
gen_aux_map_init(void *driver_ctx,
                 struct gen_mapped_pinned_buffer_alloc *buffer_alloc,
                 const struct gen_device_info *devinfo);

void
gen_aux_map_finish(struct gen_aux_map_context *ctx);

uint32_t
gen_aux_map_get_state_num(struct gen_aux_map_context *ctx);

/** Returns the current number of buffers used by the aux-map tables
 *
 * When preparing to execute a new batch, use this function to determine how
 * many buffers will be required. More buffers may be added by concurrent
 * accesses of the aux-map functions, but they won't be required for since
 * they involve surfaces not used by this batch.
 */
uint32_t
gen_aux_map_get_num_buffers(struct gen_aux_map_context *ctx);

/** Fill an array of exec_object2 with aux-map buffer handles
 *
 * The gen_aux_map_get_num_buffers call should be made, then the driver can
 * make sure the `obj` array is large enough before calling this function.
 */
void
gen_aux_map_fill_bos(struct gen_aux_map_context *ctx, void **driver_bos,
                     uint32_t max_bos);

uint64_t
gen_aux_map_get_base(struct gen_aux_map_context *ctx);

void
gen_aux_map_add_image(struct gen_aux_map_context *ctx,
                      const struct isl_surf *isl_surf, uint64_t address,
                      uint64_t aux_address);

void
gen_aux_map_unmap_range(struct gen_aux_map_context *ctx, uint64_t address,
                        uint64_t size);

#ifdef __cplusplus
}
#endif

#endif /* GEN_AUX_MAP_H */
