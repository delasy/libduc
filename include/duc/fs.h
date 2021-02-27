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

#ifndef DUC_FS_H
#define DUC_FS_H

/* See https://github.com/delasy/libduc for reference. */

#include <stdbool.h>
#include <stddef.h>

typedef struct duc_file_s duc_file_t;

typedef enum {
  DUC_FILE_APPEND,
  DUC_FILE_READ,
  DUC_FILE_WRITE
} duc_file_mode;

/**
 * Check weather end-of-file is reached
 * @param file File
 * @return `true` if end-of-file is reached or `false` otherwise
 */
bool duc_file_eof (const duc_file_t *file);

/**
 * Check weather file exists
 * @param filepath File path
 * @return `true` if file exists or `false` otherwise
 */
bool duc_file_exists (const char *filepath);

/**
 * File destructor
 * @param file File
 */
void duc_file_free (duc_file_t *file);

/**
 * File constructor
 * @param filepath File path
 * @param mode File open mode
 * @return File
 */
duc_file_t *duc_file_new (const char *filepath, duc_file_mode mode);

/**
 * Access current file position
 * @param file File
 * @return File position
 */
size_t duc_file_position (const duc_file_t *file);

/**
 * Read next character from the file
 * @param file File
 * @return Character or '\0' if end-of-file reached
 */
unsigned char duc_file_readchar (duc_file_t *file);

/**
 * Read next line from the file
 * @param file File
 * @return Line or NULL if end-of-file reached
 */
char *duc_file_readline (duc_file_t *file);

/**
 * Delete given file
 * @param filepath File path
 */
void duc_file_remove (const char *filepath);

/**
 * Set file position
 * @param file File
 * @param pos Position
 */
void duc_file_seek (duc_file_t *file, size_t pos);

/**
 * Write a character to the file
 * @param file File
 * @param ch Character to be written
 */
void duc_file_writechar (duc_file_t *file, unsigned char ch);

/**
 * Write a line to the file
 * @param file File
 * @param line Line to be written
 */
void duc_file_writeline (duc_file_t *file, const char *line);

/**
 * Read entire file content in one operation
 * @param filepath File path
 * @return Content
 */
char *duc_readfile (const char *filepath);

/**
 * Write content to the file in one operation
 * @param filepath File path
 * @param content Content to be written
 */
void duc_writefile (const char *filepath, const char *content);

/**
 * Access absolute file name representing the current working directory
 * @return Current working directory
 */
char *duc_path_cwd ();

/**
 * Access canonized absolute pathname
 * @param path Path
 * @return Canonized absolute pathname
 */
char *duc_path_real (const char *path);

#endif
