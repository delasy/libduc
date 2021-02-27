/**
 * Copyright (c) Aaron Delasy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef DUC_MAP_H
#define DUC_MAP_H

/* See https://github.com/delasy/libduc for reference. */

#include <duc/common.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct duc_map_s duc_map_t;

/**
 * Remove map element with the specified key
 * @param map Map
 * @param key Key to be deleted
 * @param free_cb Map element free callback
 */
void duc_map_delete (duc_map_t *map, const char *key, duc_free_cb free_cb);

/**
 * Check weather map is empty
 * @param map Map
 * @return `true` if map has elements or `false` otherwise
 */
bool duc_map_empty (const duc_map_t *map);

/**
 * Check whether element with the specified key exists or not
 * @param map Map
 * @param key Key to search for
 * @return `true` if map has such element or `false` otherwise
 */
bool duc_map_exists (const duc_map_t *map, const char *key);

/**
 * Map destructor
 * @param map Map
 * @param free_cb Map element free callback
 */
void duc_map_free (duc_map_t *map, duc_free_cb free_cb);

/**
 * Find an element with the specified key
 * @param map Map
 * @param key Key to search for
 * @return Map element associated with the specified key or NULL if key doesn't
 *  exists
 */
void *duc_map_get (const duc_map_t *map, const char *key);

/**
 * Access number of elements in the map
 * @param map Map
 * @return Number of elements
 */
size_t duc_map_length (const duc_map_t *map);

/**
 * Map constructor
 * @return Map
 */
duc_map_t *duc_map_new ();

/**
 * Add or update an element with specified key and value to the map
 * @param map Map
 * @param key Element key
 * @param value Element value
 */
void duc_map_set (duc_map_t *map, const char *key, void *value);

#endif
