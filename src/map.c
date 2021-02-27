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

#include <stdlib.h>
#include <string.h>
#include "map.h"

void duc_map_delete (duc_map_t *map, const char *key, duc_free_cb free_cb) {
  duc_map_item_t *prev = NULL;

  for (duc_map_item_t *curr = map->items; curr != NULL; curr = curr->next) {
    if (strcmp(curr->key, key) == 0) {
      if (prev == NULL) {
        map->items = curr->next;
      } else {
        prev->next = curr->next;
      }

      free_cb(curr->value);
      free(curr->key);
      free(curr);

      map->size -= 1;
      break;
    }

    prev = curr;
  }
}

bool duc_map_empty (const duc_map_t *map) {
  return map->size == 0;
}

bool duc_map_exists (const duc_map_t *map, const char *key) {
  for (duc_map_item_t *it = map->items; it != NULL; it = it->next) {
    if (strcmp(it->key, key) == 0) {
      return true;
    }
  }

  return false;
}

void duc_map_free (duc_map_t *map, duc_free_cb free_cb) {
  while (map->items != NULL) {
    duc_map_item_t *next = map->items->next;

    free_cb(map->items->value);
    free(map->items->key);
    free(map->items);
    map->items = next;
  }

  free(map);
}

void *duc_map_get (const duc_map_t *map, const char *key) {
  for (duc_map_item_t *it = map->items; it != NULL; it = it->next) {
    if (strcmp(it->key, key) == 0) {
      return it->value;
    }
  }

  return NULL;
}

size_t duc_map_length (const duc_map_t *map) {
  return map->size;
}

duc_map_t *duc_map_new () {
  duc_map_t *map = malloc(sizeof(duc_map_t));

  if (map == NULL) {
    return NULL;
  }

  map->items = NULL;
  map->size = 0;

  return map;
}

void duc_map_set (duc_map_t *map, const char *key, void *value) {
  if (duc_map_exists(map, key)) {
    for (duc_map_item_t *it = map->items; it != NULL; it = it->next) {
      if (strcmp(it->key, key) == 0) {
        it->value = value;
        break;
      }
    }

    return;
  }

  duc_map_item_t *in = malloc(sizeof(duc_map_item_t));

  if (in == NULL) {
    return;
  }

  in->key = malloc(strlen(key) + 1);

  if (in->key == NULL) {
    free(in);
    return;
  }

  strcpy(in->key, key);
  in->next = map->items;
  in->value = value;

  map->items = in;
  map->size += 1;
}
